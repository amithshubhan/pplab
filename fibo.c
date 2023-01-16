#include <stdlib.h>
#include <omp.h>
#include <stdio.h>

int fibo(int n){
	if(n < 2) 
		return n;
	else{
		int i,j;
		#pragma omp task shared(i) firstprivate(n)
		i = fibo(n-1);
		#pragma omp task shared(j) firstprivate(n)
		j = fibo(n-2);
		#pragma omp taskwait
		return i+j;
	}
}

int main(){

	int n;
	printf("Enter the number\n");
	scanf("%d",&n);
	#pragma omp parallel shared(n)
	{
	#pragma omp single
	printf("The fibonnaci of %d is %d\n",n,fibo(n));
	}
	
	return 0;
}
