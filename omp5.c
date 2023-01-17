#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int isprime(int n){
	if(n == 1) return 0;
	if(n == 2) return 1;
	for(int i=2;i*i<=n;i++){
		if(n%i == 0) return 0;
	}
	return 1;
}

int main(){

	int n;
	printf("Enter the number\n");
	scanf("%d",&n);
		double start1 = omp_get_wtime();
	#pragma omp parallel for
	
		for(int i=1;i<=n;i++){
			if(isprime(i)){
				printf("%d ",i);
			}
		}
		printf("\n");
	
	double end1 = omp_get_wtime();
	printf("\n%f is the time for parallel \n ",end1-start1);
	start1 = omp_get_wtime();
		for(int i=1;i<=n;i++){
			if(isprime(i)){
				printf("%d ",i);
			}
	}
	printf("\n");
	end1 = omp_get_wtime();


	printf("\n%f is the time for series \n ",end1-start1);
	return 0;
}



