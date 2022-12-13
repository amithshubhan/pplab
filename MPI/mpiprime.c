#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int isprime(int n){
	if(n==1) return 0;
	if(n == 2) return 1;
	for(int i=2;i*i<=n;i++){
		if(n%i == 0) return 0;
	}
	return 1;
}

int main(int argc,char * argv[]){

	int *a;
	int *b;
	int ele = 12;
	int subsize;
	int size,rank;
	MPI_Init(&argc,&argv);
	
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	int * ap;
	int * bp;
	// printf("rank is %d\n",rank);
	if(rank == 0){
		a = (int *)malloc(sizeof(int)*ele);
		b = (int *)malloc(sizeof(int)*ele);
		for(int i=0;i<ele;i++)
		{
			a[i] = i+1;
		}
	}
	
	

	 subsize = ele/size;
	ap = (int *)malloc(sizeof(int)*subsize);
	bp = (int *)malloc(sizeof(int)*subsize);

	
	MPI_Scatter(a,subsize,MPI_INT,ap,subsize,MPI_INT,0,MPI_COMM_WORLD);

	for(int i=0;i<subsize;i++){
		if(isprime(ap[i])){
			bp[i] = 1;
		}else{
			bp[i] = 0;
		}
	}

	MPI_Gather(bp,subsize,MPI_INT,b,subsize,MPI_INT,0,MPI_COMM_WORLD);

	if(rank == 0){
		for(int i=0;i<ele;i++){
			if(b[i] == 1)
				printf("%d is prime\n",a[i]);
			else
				printf("%d is not prime\n",a[i]);

		}printf("\n");
	}

	MPI_Finalize();


	return 0;
}


