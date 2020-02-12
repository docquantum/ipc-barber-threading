/**
 * monitor.c
 * =============
 * condition variable implementation for sleeping
 * stylist problem with helper functions
 * 
 * (c) 2019 -- Daniel Shchur
 * 
 * Licensed under GPLv3
 */

#include <stdio.h>
#include "monitor.h"

cond stylistAvailable, customerAvailable;
sem_t mutex;
unsigned short debug = 0;
int customerCount = 0;
int stylistCount = 0;
int givenHaircuts = 0;
int salonFull = 0;
int salonEmpty = 0;

void setDebug(){
    debug = 1;
}

void init_cond(cond* cv){
    cv->num_blocked_threads=0;
    sem_init(&(cv->sem), 0, 0); //Counting
    sem_init(&(cv->lock), 0, 1);//Mutex
}

void init_all(){
    sem_init(&mutex, 0, 1);
    init_cond(&stylistAvailable);
    init_cond(&customerAvailable);
}

unsigned int count(cond* cv){
    return cv->num_blocked_threads;
}

void wait(cond* cv, sem_t* m){

    // Lock
    sem_wait(&(cv->lock));
    // Increment num of blocked threads
    cv->num_blocked_threads++;
    // Relinquish access to other threads (assumes mutex is locked)
    sem_post(m);
    // Unlock
    sem_post(&(cv->lock));

    // Put thread to sleep
    sem_wait(&(cv->sem));

    // Regain access after thread is woken
    sem_wait(m);
}

void signal(cond* cv){
    // Lock
    sem_wait(&(cv->lock));
    // Only wake thread if there are threads
    if(count(cv) > 0){
        // Wake a thread
        cv->num_blocked_threads--;
        sem_post(&(cv->sem));
    }
    // Unlock
    sem_post(&(cv->lock));
}

void mon_checkCustomer(){
    // Lock
    sem_wait(&mutex);

    // Stylist is ready
    stylistCount++;

    // Stylist is ready to cut hair
    signal(&stylistAvailable);
    
    // No customers, stylist sleeping.
    if (customerCount == 0){
        if(debug){
            printf("\n\tNo customers, stylist sleeping...\n\n");
        }
        
        salonEmpty++;
        wait(&customerAvailable, &mutex);
        if(debug){
            printf("\n\tStylist woken...\n\n");
        }
    }

    // Remove customer
    customerCount--;
    // Haircut will be given...
    givenHaircuts++;
    // Unlock
    sem_post(&mutex);
}

int mon_checkStylist() {
    // Lock
    sem_wait(&mutex);

    int status = 0;

    // Only wait if there are chairs
    if(customerCount < CHAIRS){
        customerCount++;
        if(customerCount == 7){
            salonFull++;
        }

        // Signal that customer is available
        if(debug){
            printf("\n\tCustomer arrived...\n\n");
        }
        signal(&customerAvailable);

        if(stylistCount == 0){
            if(debug){
                printf("\n\tStylist busy, customer waiting for stylist\n\n");
            } 
            wait(&stylistAvailable, &mutex);
            if(debug){
                printf("\n\tCustomer getting haircut...\n\n");
            }
        }
        
        // "busy" the stylist
        stylistCount--;

        status = 1;
    }
    // Unlock
    sem_post(&mutex);
    return status;
}

/**
 * Print how many customers are waiting
*/
void mon_debugPrint(void){
    // Lock
    sem_wait(&mutex);
    printf("\n");
    printChairs(customerCount);
    printf("Given haircuts = %d\n", givenHaircuts);
    printf("Salon full = %d times\n", salonFull);
    printf("Salon empty = %d times\n", salonEmpty);
    // Unlock
    sem_post(&mutex);
}

int getGivenHaircuts(){
    return givenHaircuts;
}

void printChairs(int chairs){
    switch (chairs) {
    case 0:
        printf("|0|0|0|0|0|0|0| => %d\n", customerCount);
        break;
    case 1:
        printf("|1|0|0|0|0|0|0| => %d\n", customerCount);
        break;
    case 2:
        printf("|1|1|0|0|0|0|0| => %d\n", customerCount);
        break;
    case 3:
        printf("|1|1|1|0|0|0|0| => %d\n", customerCount);
        break;
    case 4:
        printf("|1|1|1|1|0|0|0| => %d\n", customerCount);
        break;
    case 5:
        printf("|1|1|1|1|1|0|0| => %d\n", customerCount);
        break;
    case 6:
        printf("|1|1|1|1|1|1|0| => %d\n", customerCount);
        break;
    case 7:
        printf("|1|1|1|1|1|1|1| => %d\n", customerCount);
        break;
    default:
        printf("|-|-|-|-|-|-|-| => %d -- wait, what?\n", customerCount);
        break;
    }
}