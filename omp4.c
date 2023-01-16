#include <stdlib.h>
#include <omp.h>
#include <stdio.h>

int fib(int n){
	if(n < 2) 
		return n;
	else{
		int i,j;
		#pragma omp task shared(i) firstprivate(n)
		i = fib(n-1);
		#pragma omp task shared(j) firstprivate(n)
		j = fib(n-2);
		#pragma omp taskwait
		return i+j;
	}
}

int main(){

	// int n;
	// printf("Enter the number\n");
	// scanf("%d",&n);
	// #pragma omp parallel for shared(n)
	
	// for(int i=1;i<=n;i++){
	// #pragma omp single
	// printf("The fibonnaci of %d is %d\n",n,fibo(i));
// }
	int n = 20;
    double start = omp_get_wtime();
    #pragma omp parallel for
    for(int i=0;i<n;i++){
        int t = omp_get_thread_num();
        printf("thread: %d fib(%d) = %d\n",t,i,fib(i));
    }
    double end = omp_get_wtime();
    printf("using schedule time is : %f\n",end-start);

	
	
	return 0;
}
