#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(){
	int n;
	printf("Enter the size of array\n");
	scanf("%d",&n);
	int a[n],b[n],c[n];
	printf("a's array elements are:\n");
	for(int i=0;i<n;i++){
		a[i] = rand()%10;
		printf("%d ",a[i]);
	}
	printf("b's array elements are:\n");
	for(int i=0;i<n;i++){
		b[i] = rand()%10;
		printf("%d ",b[i]);
	}
	double start = omp_get_wtime();
	#pragma omp parallel for 
	for(int i=0;i<n;i++){
		// printf("%d\n",omp_get_thread_num());
		c[i] = a[i] + b[i];
	}
	double end = omp_get_wtime();
	for(int i=0;i<n;i++){
		printf("%d ",c[i]);
	}
	printf("\n the time taken for parallel is %f\n",end - start);
	start = omp_get_wtime();
	for(int i=0;i<n;i++){
		c[i] = a[i]+b[i];
	}
	end = omp_get_wtime();
	printf("\n the time taken for series is %f\n",end - start);

	return 0;
}
