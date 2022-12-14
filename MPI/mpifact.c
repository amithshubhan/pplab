#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc,char * argv[]){

	int rank,size;
	int n;
	scanf("%d",&n);
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
	int siz = (n/size) + 1;
	int st = (rank*size);
	int en = ((rank+1)*size);
	int loc = 1;
	int * ap = malloc(sizeof(int)*siz);
	for(int i=st;i<en && i<=n;i++){
		loc *= i+1;
	}
	int glb = 1;
	MPI_Reduce(&loc,&glb,1,MPI_INT,MPI_PROD,0,MPI_COMM_WORLD);
	if(rank == 0){
		printf("fact is %d \n",glb);
	}
	MPI_Finalize();
	return 0;
}