#include <stdio.h>
#include <omp.h>

long long fib(long long n) 
{
        if (n < 2) {
                return 1;
        }
        return fib(n - 2) + fib(n - 1);
}

int main(int argc, char ** argv) 
{
        long long n = 0;

        #pragma omp parallel for schedule(dynamic, 3)
        for (n = 0; n <= 25; n++) {
                printf("Fib(%lld): %lld\n", n, fib(n));
        }

        return 0;
}