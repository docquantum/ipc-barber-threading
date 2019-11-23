
Daniel Shchur

In the directory, simply running `make` will both compile and run the code.
The code will output to `output.txt`.

If you would like to run it without redirection, that can be done by calling
the program: `./stylistSem` after having run `make`

The customer's shopping times vary since their delay is multiplied by a random
number. This allows for varied full/empty times. This means every run has
a different result and running the program a few times to get a better overall
sample is recommended.

The stylist prints to stdout when there are no customers, if there are none,
that he goes to sleep, and when he grabs a customer with how many are left.
The customer prints when they go shopping (with thread ID) and when they
arrive with what seat they take. The stylist will also print how many customers
have been served and how many times the shop was full and empty.

This problem took me around 3 hours more or less to complete, aside from
printing tweaks here and there and delays to get the right response with
waiting.

I would rate it at a 3 for difficulty. It was a 2 after brushing up on
documentation, examples, and notes and deciding to use the semaphore
library instead of making my own semaphores and P(), V() functions.