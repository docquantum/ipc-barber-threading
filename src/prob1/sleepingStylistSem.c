/**
 * sleeypingStylistSem.c
 * =============
 * Using semaphores to solve the sleeping
 * stylist barber in which there is inter
 * process (threaded) communication.
 * 
 * (c) 2019 -- Daniel Shchur
 * 
 * Licensed under GPLv3
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define CHAIRS      7
#define DELAY       1000
#define CUSTOMERS   120
#define STYLISTS    1

void customer(void);
void stylist(void);

/**
 * Randomize how long it takes for the customers to go
 * shopping to make it more spread out.
 */ 
int randomNum(){
    return (rand() % (50 - 5 + 1)) + 5;
}

sem_t mutex, stylist_sem, customers_sem;
int waiting = 0;
int served = 0;
int timesFull = 0;
int timesEmpty = 0;

int main(void){
    srand(time(0));

    printf("Starting main thread...\n");
    sem_init(&mutex,0,1);
    sem_init(&customers_sem,0,0);
    sem_init(&stylist_sem,0,1);

    pthread_t customer_thread[CUSTOMERS], stylist_thread;
    int thread_status;
    printf("Starting stylist thread...\n");
    thread_status = pthread_create(&stylist_thread, NULL, (void *)stylist, NULL);
    if(thread_status != 0){
        fprintf(stderr, "Failed to create stylist thread!\n");
        return 1;
    }

    // Give stylist enough time to start
    sleep(1);
    printf("Starting customer threads...\n\n");
    for(int i=0; i<CUSTOMERS; i++){
        thread_status = pthread_create(&customer_thread[i], NULL, (void *)customer, NULL);
        if(thread_status != 0){
            fprintf(stderr, "Failed to create customer thread!\n");
            return 1;
        }
    }
    
    for(int i=0; i<CUSTOMERS; i++)
        pthread_join(customer_thread[i], NULL);

    pthread_join(stylist_thread, NULL);

    return 0;
}
    
void stylist(void){
    while(1) {
        if(served == CUSTOMERS){
            printf("Finished all customers\n");
            printf("Time full = %d\n", timesFull);
            printf("Times empty = %d\n\n", timesEmpty);
            break;
        }
        // Lock
        sem_wait(&mutex);
        if(waiting == 0){
            printf("Stylist waiting for customers\n");
            timesEmpty++;
        }
        // Unlock
        sem_post(&mutex);

        // Checking customers
        sem_wait(&customers_sem);
        // Lock
        sem_wait(&mutex);
        // Remove customer from queue
        waiting--;
        printf("Stylist getting customer from seat (now %d left)\n", waiting);
        sem_post(&stylist_sem);
        // Unlock
        sem_post(&mutex);
        printf("Stylist cutting hair...\n");
        for(int j = 0; j<DELAY*100; j++);
            //cut hair
        served++;
        printf("\nStylist finished %d customers...\n\n", served);
    }
}

void customer(void){
    while(1) {
        // Lock
        sem_wait(&mutex);
        if(waiting < CHAIRS) {
            waiting++;
            if(waiting == 7){
                timesFull++;
            }
            printf("\tNew customer waiting in seat %d\n", waiting);
            // Notify stylist (anyone waiting on customers)
            sem_post(&customers_sem);
            // Unlock
            sem_post(&mutex);
            // Wait on stylist
            sem_wait(&stylist_sem);
            break;
        }
        else {
            printf("No room left, customer going shopping (id %lu)\n", pthread_self());
            sem_post(&mutex);
            for(int j=0; j < DELAY*randomNum(); j++);
                //go  shopping
        }
    }
}
