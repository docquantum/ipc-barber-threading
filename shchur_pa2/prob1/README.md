
Daniel Shchur

In the directory, simply running `make` will both compile and run the code. The code will output to `output.txt`.

If you would like to run it without redirection, that can be done by calling the program: `./stylistSem` after having run `make`

It prints to stdout every time the stylist goes back to check on the queue and when he grabs a customer, as well as when a customer goes shopping.
The stylist will print out the seat from which the customer is being taken and then after finishing with the customer, will also print how many customers have been completed.

This problem took me around 3 hours more or less to complete, aside from printing tweaks here and there and delays to get the right response with waiting.

I would rate it at a 3 for difficulty. It was a 2 after brushing up on documentation, examples, and notes and deciding to use the semaphore library instead of making my own semaphores and P(), V() functions.