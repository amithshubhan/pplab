#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <math.h>

//pi = (-1^k) / 2k +1

int main(){
	int steps = 1000000;
	double pi = 0;
	double start = omp_get_wtime();
	for(int i=0;i<steps;i++){
		pi = pi + (pow(-1,i)/((2*i)+1));
	}
	pi *= 4;
	double end = omp_get_wtime();
	printf("pi value at series is %f\n and time taken = %f\n",pi,end-start);
	int size=omp_get_num_threads();
	printf("Size is %d\n",size);
	double thread[8];
	pi = 0;
	for(int i=0;i<8;i++) thread[i] = 0;

	start = omp_get_wtime();

	#pragma omp parallel for num_threads(8)
	for(int i=0;i<steps;i++){
		int th = omp_get_thread_num();
		// printf("th : %d\n",th);
		thread[th] += pow(-1,i)/((2*i)+1);

	}
	for(int i=0;i<size;i++){
		pi += thread[i];
	}
	pi*=4;
	end = omp_get_wtime();
	printf("pi value at parallel is %f\n and time taken = %f\n",pi,end-start);
	return 0;
}
