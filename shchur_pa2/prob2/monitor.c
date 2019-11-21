/**
 * monitor.c
 * =============
 * condition variable implementation for sleeping
 * stylist problem with helper functions
 * 
 * (c) 2019 -- Daniel Shchur
 * 
 * Licenced under GPLv3
 */

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include "monitor.h"

cond stylistAvailable, customerAvailable;
sem_t mutex;
int customerCount = 0;
int stylistCount = 0;
int givenHaircuts = 0;
int salonFull = 0;
int salonEmpty = 0;

void init_cond(cond* cv){
    cv->num_blocked_threads=0;
    sem_init(&(cv->sem), 0, 0);
    sem_init(&(cv->lock), 0, 1);
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
    sem_wait(&(cv->lock));
    cv->num_blocked_threads++;
    sem_post(m);
    sem_post(&(cv->lock));

    sem_wait(&(cv->sem));
    sem_wait(m);
}

void signal(cond* cv){
    sem_wait(&(cv->lock));
    if(count(cv) > 0){
        cv->num_blocked_threads--;
        sem_post(&(cv->sem));
    }
    sem_post(&(cv->lock));
}

void mon_checkCustomer(){
    sem_wait(&mutex);

    stylistCount++;

    signal(&stylistAvailable); // stylist's ready to cut hair
    
    // No customers, stylist sleeping.
    if (customerCount == 0){
        salonEmpty++;
        wait(&customerAvailable, &mutex);
    }

    customerCount--;
    givenHaircuts++;
    sem_post(&mutex);
}

int mon_checkStylist() {

    sem_wait(&mutex);
    int status = 0;

    if(customerCount < CHAIRS){
        customerCount++;
        if(customerCount == 7){
            salonFull++;
        }
        signal(&customerAvailable);

        if(stylistCount == 0){
            wait(&stylistAvailable, &mutex);
        }
            
        stylistCount--;

        status = 1;
    }
    sem_post(&mutex);
    return status;
}

/**
 * Print how many customers are waiting
*/
void mon_debugPrint(void){
    sem_wait(&mutex);
    printf("\n");
    printChairs(customerCount);
    printf("Given haircuts = %d\n", givenHaircuts);
    printf("Salon full = %d times\n", salonFull);
    printf("Salon empty = %d times\n", salonEmpty);

    sem_post(&mutex);
    /** print the state of the waiting char using the following format
     * (the following four lines are the sample output):
     * |1|1|1|0|0|0|0| => 3
     * Given haircuts = X
     * Salon full = Y times
     * Salon empty = Z times
     * 
     * Below is the explanation of each line.
     * 
     * Line 1: For each slot, - indicates that the chair is available
     * and 1 indicates that the chair is occupied.
     * 
     * The value after => indicates the number of occupied chairs.
     * 
     * Line 2: X = number of completed haircuts.
     * 
     * Line 3: Y = number of times that all waiting chairs are full.
     * That is, each time the number of occupied chairs increases to 7,
     * this counter should go up by 7.
     * 
     * Line 4: Z = the number of times that the stylist goes to sleep.
     * That is, each time the stylist goes to sleep, this counter should
     * go up by 1.
    */
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
        break;
    }
}