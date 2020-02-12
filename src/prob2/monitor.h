/**
 * monitor.h
 * =============
 * condition variable declarations for sleeping
 * stylist problem with helper functions
 * 
 * (c) 2019 -- Daniel Shchur
 * 
 * Licensed under GPLv3
 */

#include <semaphore.h>

/**
 * Number of chairs in the waiting room 
 */
#define CHAIRS 7

/**
 * Sets debug printing on
 */
void setDebug();

/**
 * CV implementation structure that keeps track of the
 * number of blocked threads and a semaphore to suspend
 * threads. Also has an internal mutex to block incrementing
 * or decrementing the count to one thread at a time.
 */
typedef struct {
    unsigned int num_blocked_threads;
    sem_t sem;
    sem_t lock;
} cond;

/**
 * Initializes all cv's and semaphores.
 */ 
void init_all();

/**
 * Initializes the cv with memory and initial values. 
 */
void init_cond(cond* cv);

/**
 * returns the number of threads blocked on the cv.
 */
unsigned int count(cond* cv);

/**
 * Relinquishes exclusive access to the monitor 
 * and then suspends the executing threads.
 */
void wait(cond* cv, sem_t* m);

/**
 * Unblocks one thread suspended at the head of the
 * cv blocking queue. The signaled thread resumes
 * execution where it was last suspended. The signaler
 * exits the monitor and suspends itself at the entry queue.
 */
void signal(cond* cv);

/**
 * Manages the waiting list and takes a customer to
 * the styling chair. Invokes stylistAvailable to indicate
 * that the stylist is not busy. If the solon is empty,
 * invokes wait on the cv customerAvailable to put the
 * stylist to sleep.
 */
void mon_checkCustomer();


/**
 * Puts a customer on the 7 waiting chairs if the solon
 * is not full. If the stylist is busy or sleeping, it first
 * invokes a wait on the cv stylistAvailable. If also invokes
 * signal on cv customerAvailable to indicate a customer is
 * waiting.
 */
int mon_checkStylist();

/**
 * Print how many customers are waiting
*/
void mon_debugPrint(void);

/**
 * Gets the current number of customers served.
 */
int getGivenHaircuts();

/**
 * Print the state of the waiting char using
 * the following format:
 * 
 * |1|1|1|0|0|0|0| => 3
 * Given haircuts = X
 * Salon full = Y times
 * Salon empty = Z times
 * 
 */ 
void printChairs(int chairs);