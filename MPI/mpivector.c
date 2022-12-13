#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc,char * argv[]){

	int *a;
	int *b;
	int *c;
	int ele = 12;
	int subsize;
	int size,rank;
	MPI_Init(&argc,&argv);
	
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	int * ap;
	int * bp;
	int * cp;
	printf("rank is %d\n",rank);
	if(rank == 0){
		a = (int *)malloc(sizeof(int)*ele);
		b = (int *)malloc(sizeof(int)*ele);
		c = (int *)malloc(sizeof(int)*ele);
		for(int i=0;i<ele;i++)
		{
			a[i] = i;
		}
		for(int i=0;i<ele;i++)
		{
			b[i] = i;
		}
		for(int i=0;i<ele;i++){
			printf("%d ",a[i]);
		}printf("\n");
	}
	
	

	 subsize = ele/size;
	ap = (int *)malloc(sizeof(int)*subsize);
	bp = (int *)malloc(sizeof(int)*subsize);
	cp = (int *)malloc(sizeof(int)*subsize);

	
	MPI_Scatter(a,subsize,MPI_INT,ap,subsize,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(b,subsize,MPI_INT,bp,subsize,MPI_INT,0,MPI_COMM_WORLD);

	for(int i=0;i<subsize;i++){
		cp[i] = ap[i] + bp[i];
	}

	MPI_Gather(cp,subsize,MPI_INT,c,subsize,MPI_INT,0,MPI_COMM_WORLD);

	if(rank == 0){
		for(int i=0;i<ele;i++){
			printf("%d ",c[i]);
		}printf("\n");
	}

	MPI_Finalize();


	return 0;
}