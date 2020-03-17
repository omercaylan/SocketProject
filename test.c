/* Program to demonstrate time taken by function fun() */
#include <stdio.h>
#include <time.h>

// The main program calls fun() and measures time taken by fun()
int main()
{
    // Calculate the time taken by fun()
    clock_t t;
    t = clock();
    double time_taken;
    while (1)
    {
        t = clock();
        time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
        printf("time =  %f \n", time_taken);
        if (time_taken > 5)
        {
            break;
        }
    }

    printf("fun() took %f seconds to execute \n", time_taken);
    return 0;
}
