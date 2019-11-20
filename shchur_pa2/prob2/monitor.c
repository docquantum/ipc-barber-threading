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

#include "monitor.h"

cond stylistAvailable,  customerAvailable;
int customer = 0;
int stylist = 0;

void init_cond(cond* cv){
    cv->num_of_threads=0;
    sem_init(&(cv->lock), 0, 1);
}

unsigned int count(cond* cv){
    return cv->num_of_threads;
}

void wait(cond* cv){
    //block
}

void signal(cond* cv){
    //signal
}

//add more variables as necessary (e.g. a semaphore for entry queue)

void mon_checkCustomer(){
    stylist++;
    
    signal(&stylistAvailable); // stylist's ready to cut hair
    
    //do not use while here
    if (customer == 0)
        wait(&customerAvailable);
    
    customer--;
}

int mon_checkStylist() {
    // This function may have faults.
    // If you think it does, you'll need to fix it

    int status = 0;

    if(customer < CHAIRS){
        customer++;

        signal(&customerAvailable);

        if(stylist == 0) // do not use while here
            wait(&stylistAvailable);
        
        stylist--;

        status = 1;
    }
    return status;
}

/**
 * Print how many customers are waiting
*/
void mon_debugPrint(void){
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