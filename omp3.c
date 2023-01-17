#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(){
	int thread[8];
	for(int i=0;i<8;i++) thread[i] = 0;
	int iter;
	printf("Enter the iteration\n");
	scanf("%d",&iter);
	#pragma omp parallel for schedule(static,3)
	for(int i=0;i<iter;i++){
		int th = omp_get_thread_num();
		thread[th]++;
		printf("thread: %d --> %d\n",th,thread[th]);
	}
	return 0;
}
