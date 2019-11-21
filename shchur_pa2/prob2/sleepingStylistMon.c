#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "monitor.h"

#define DELAY       1000
#define CUSTOMERS   120
#define STYLISTS    1

int randomNum(){
    return (rand() % (50 - 5 + 1)) + 5;
}

void stylist(void){
    int j;
    while(1){
        mon_debugPrint();
        mon_checkCustomer();
        for(j=0; j<DELAY*100; j++);
            // cut hair
        if(getGivenHaircuts() == CUSTOMERS){
            printf("\nStylist finished 120 Customers...\n");
            mon_debugPrint();
            break;
        }
    }
}

void customer(void){
    // add more variables as needed
    int j;
    while(1){
        mon_debugPrint();
        if(mon_checkStylist())
            break;
        for(j=0; j<DELAY*randomNum(); j++);
            // go shopping
    }
}

int main(void){
    srand(time(0));

    printf("Starting main thread...\n");
    init_all();

    pthread_t customer_thread[CUSTOMERS], stylist_thread[STYLISTS];
    int thread_status;

    printf("Starting stylist threads...\n");
    for (int i = 0; i < STYLISTS; i++){
        thread_status = pthread_create(&stylist_thread[i], NULL, (void *)stylist, NULL);
        if(thread_status != 0){
            fprintf(stderr, "Failed to create stylist thread!\n");
            return 1;
        }
    }

    //Make sure stylist is first to run...
    sleep(1);
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
    for (int i = 0; i < STYLISTS; i++)
    {
        pthread_join(stylist_thread[i], NULL);
    }

    printf("Closed stylist thread\n");

    return 0;
}