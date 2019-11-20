/**
 * monitor.h
 * =============
 * condition variable declarations for sleeping
 * stylist problem with helper functions
 * 
 * (c) 2019 -- Daniel Shchur
 * 
 * Licenced under GPLv3
 */

#include <semaphore.h>

/**
 * Number of chairs in the waiting room 
 */
#define CHAIRS 7

/**
 * CV implementation structure that keeps track of the
 * number of blocked threads and a semaphore to suspend
 * threads.
 */
typedef struct {
    unsigned int num_of_threads;
    sem_t lock;
} cond;

/**
 * Initializes the cv with memory and initial values. 
 */
void init_cond(cond* cv);

/**
 * returns the number of threads blocked on the cv.
 */
unsigned int count(cond* cv);

/**
 * relinquishes exclusive access to the monitor 
 * and then suspends the executing threads.
 */
void wait(cond* cv);

/**
 * unblocks one thread suspended at the head of the
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