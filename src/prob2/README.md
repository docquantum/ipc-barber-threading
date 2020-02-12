Daniel Shchur

In the directory, simply running `make` will both compile and run the code.
The code will output to `output.txt`.

If you would like to run it without redirection, that can be done by calling
the program: `./stylistMon` after having run `make`

The customer's shopping times vary since their delay is multiplied by a random
number. This allows for varied full/empty times. This means every run has
a different result and running the program a few times to get a better overall
sample is recommended.

It prints out the required waiting chairs, Given haircuts = X, Salon full = Y
times, Salon empty = Z times. Salon full is only how many times it's full
(every time it goes from 6 to 7) and not incrementing 7 times every time that
happens since that didn't make logical sense.

There is also additional debug prints to show when the stylist goes to sleep,
when customers arrive, and when either is woken up after being blocked on a CV.
This can be triggered by adding the `-v` flag after invoking the program
(e.g. `./stylistMon -v`)

This problem took me around 7 hours more or less to complete, there was an odd
bug where thread's could "signal" when there was none waiting on a CV, took me
too long to figure it out, wasting a few hours.

I would rate it at a 5 for difficulty. Implementing CV's using semaphores
proves difficult given there is no atomic operations that can be done so there
are times threads try to signal a CV in the middle of it trying to put a
thread to sleep.