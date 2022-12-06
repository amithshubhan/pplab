#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int main(){
	int N = 10;
	int a[10],b[10];
	for(int i=0;i<N;i++){
		a[i] = rand()%100;
		b[i] = rand()%100;
	}
	int c[10];
	printf("\nA array is :\n");
	for(int i=0;i<N;i++){
		printf("%d ",a[i]);
	}
	printf("\nB array is :\n");
	for(int i=0;i<N;i++){
		printf("%d ",b[i]);
	}
	printf("\nC array is :\n");
	#pragma omp parallel for 
		for(int i=0;i<N;i++){
			c[i] = a[i] + b[i];
			printf("%d:%d is %d\n",omp_get_thread_num(),i,c[i]);
		}
	return 0;
}
