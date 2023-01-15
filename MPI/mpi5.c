#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int isprime(int n){
	if(n == 1) return 0;
	if(n == 2) return 1;
	for(int i=2;i*i<=n;i++){
		if(n%i == 0) return 0;
	}
	return 1;
}

int main(int argc,char ** argv){
	int rank,size;
	int root = 0;
	MPI_Init(&argc,&argv);

	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status stat;
	int n;

	if(rank == 0){
		printf("Enter the number\n");
		scanf("%d",&n);
	}
	MPI_Bcast(&n,1,MPI_INT,root,MPI_COMM_WORLD);
	int subsize = (n/size);
	int ll = (rank*subsize) + 1;
	int ul = (rank+1)*subsize;
	if(rank == size-1) ul = n;
	for(int i=ll;i<=ul;i++){
		if(isprime(i))
			printf("Rank %d , number %d is prime\n",rank,i);
		else
			printf("Rank %d , number %d is not prime\n",rank,i);
	}


	MPI_Finalize();
	return 0;
}
