#include <stdio.h>
#include <pthread.h>
#include "monitor.h"

#define DELAY       1000000
#define CUSTOMERS   120
#define STYLISTS    1

int main(void){

    printf("Starting main thread...\n");

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
    // add more variables as needed
    int j;
    while(1){
        mon_debugPrint();
        mon_checkCustomer();
        for(j=0; j<DELAY; j++);
            // cut hair
    }
}

void customer(void){
    // add more variables as needed
    int j;
    while(1){
        mon_debugPrint();
        if(mon_checkStylist())
            break;
        for(j=0; j<DELAY; j++);
            // go shopping
    }
}