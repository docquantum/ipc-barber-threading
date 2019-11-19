#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define CHAIRS      7
#define DELAY       10000 //adjust this value
#define CUSTOMERS   120
#define STYLISTS    1

void customer(void);
void stylist(void);

sem_t mutex, stylist_sem, customers_sem;
int waiting = 0;
int served = 0;

int main(void){

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
    printf("Starting customer threads...\n\n");
    for(int i=0; i<CUSTOMERS; i++){
        thread_status = pthread_create(&customer_thread[i], NULL, (void *)customer, NULL);
        if(thread_status != 0){
            fprintf(stderr, "Failed to create customer thread!\n");
            return 1;
        }
    }
    
    //printf("Joining customer threads...\n");
    for(int i=0; i<CUSTOMERS; i++){
        pthread_join(customer_thread[i], NULL);
        //printf("Joined customer %lu-%d...\n", customer_thread[i],i+1);
    }
    printf("\nClosed all customer threads\n");
    //printf("Joining stylist thread...\n");
    pthread_join(stylist_thread, NULL);
    printf("Closed stylist thread\n");

    return 0;
}
    
void stylist(void){
    while(1) {
        if(served == CUSTOMERS){
            printf("Finished all customers\n");
            break;
        }
        printf("Stylist waiting for customers\n");
        sem_wait(&customers_sem);
        printf("Stylist checking for customers...\n");
        sem_wait(&mutex);
        printf("Stylist getting customer from seat %d\n", waiting);
        waiting--;
        sem_post(&stylist_sem);
        sem_post(&mutex);
        printf("Stylist cutting hair...\n");
        for(int j = 0; j<DELAY; j++);
            //cut hair
        served++;
        printf("Stylist finished %d customers...\n", served);
    }
}

void customer(void){
    while(1) {
        sem_wait(&mutex);
        if(waiting < CHAIRS) {
            waiting++;
            printf("New customer waiting in seat %d (id %lu)\n", waiting, pthread_self());
            sem_post(&customers_sem);
            sem_post(&mutex);
            sem_wait(&stylist_sem);
            break;
        }
        else {
            printf("No room left, customer going shopping (id %lu)\n", pthread_self());
            sem_post(&mutex);
            for(int j=0; j < DELAY; j++);
                //go  shopping
        }
    }
}
