#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]){
	int rank,size;
	int tag = 1;
	char data[10] = "Amith";
	char datar[10];
	int dest,src;
	int count;
	int siz = (sizeof(data)/sizeof(char)); 
	MPI_Init(&argc,&argv);
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	if(rank == 0){
		 dest = 1;
		MPI_Send(&data,siz,MPI_CHAR,dest,tag,MPI_COMM_WORLD);
	}
	if(rank == 1){
		 src = 0;
		MPI_Recv(&datar,siz,MPI_CHAR,src,tag,MPI_COMM_WORLD,&status);
		printf("%s\n",datar);
	}
	int rc = MPI_Get_count(&status,MPI_CHAR,&count);
	printf("The message received from proc %d from tag %d into the proc %d\n",status.MPI_SOURCE,status.MPI_TAG,rank);
	MPI_Finalize();
	return 0;
}