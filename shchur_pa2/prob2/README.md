Daniel Shchur

In the directory, simply running `make` will both compile and run the code. The code will output to `output.txt`.

If you would like to run it without redirection, that can be done by calling the program: `./stylistMon` after having run `make`

It prints out the required waiting chairs, Given haircuts = X, Salon full = Y times, Salon empty = Z times. Salon full is only how many times it's full and not incrementing 7 times every time it happens.

This problem took me around 7 hours more or less to complete, there was an odd bug where thread's could "signal" when there was none waiting on a CV, took me too long to figure it out, wasting a few hours.

I would rate it at a 5 for difficulty. Implementing cv's using semaphores proves difficult given there is no atomic operations that can be done.