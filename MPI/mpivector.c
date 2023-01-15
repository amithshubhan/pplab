#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <string.h>

int main(int argc,char ** argv){

	int rank,size;
	int n = 12;
	// printf("The number of threads in use are %d\n")
	// printf("Enter the size of the array\n");
	// scanf("%d",&n);
	int a[100],b[100],c[100];
	int root = 0;
	for(int i=0;i<n;i++){
		a[i] = rand()%10;
		b[i] = rand()%10;
	}
	// printf("The array a is\n");
	// for(int i=0;i<n;i++) printf("%d ",a[i]);
	// 	printf("\nThe array b is \n");
	// for(int i=0;i<n;i++) printf("%d ",b[i]);

	// 	printf("\n");
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	int subsize = (n/size);
	int * ap = malloc(sizeof(int)*subsize);
	int * bp = malloc(sizeof(int)*subsize);
	int * cp = malloc(sizeof(int)*subsize);
	MPI_Scatter(a,subsize,MPI_INT,ap,subsize,MPI_INT,root,MPI_COMM_WORLD);
	MPI_Scatter(b,subsize,MPI_INT,bp,subsize,MPI_INT,root,MPI_COMM_WORLD);


	for(int i=0;i<subsize;i++){
		cp[i] = ap[i]+bp[i];
	}


	MPI_Gather(cp,subsize,MPI_INT,c,subsize,MPI_INT,root,MPI_COMM_WORLD);

	if(rank == root){
		printf("The array a is\n");
	for(int i=0;i<n;i++) printf("%d ",a[i]);
		printf("\nThe array b is \n");
	for(int i=0;i<n;i++) printf("%d ",b[i]);

		printf("\n");
		printf("The resultant array is :\n");
		for(int i=0;i<n;i++){
			printf("%d ",c[i]);
		}
		printf("\n");
	}


	MPI_Finalize();
	return 0;
}
