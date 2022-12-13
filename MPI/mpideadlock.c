#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]){
	int rank,size;
	int tag = 1;
	char data[10] = "Amith";
	char datar[10];
	char datas[10];
	int dest,src;
	int count;
	int tag1 = 0;
	int siz = (sizeof(data)/sizeof(char)); 
	MPI_Init(&argc,&argv);
	MPI_Status status;
	MPI_Request req;
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	if(rank == 0){
		 dest = 1;
		 src = 1;
		
		MPI_Isend(&data,siz,MPI_CHAR,dest,tag1,MPI_COMM_WORLD,&req);
		MPI_Irecv(&datar,siz,MPI_CHAR,src,tag1,MPI_COMM_WORLD);
	}
	if(rank == 1){
		 dest = 0;
		 src = 0;
		MPI_Irecv(&datas,siz,MPI_CHAR,src,tag,MPI_COMM_WORLD);
		MPI_Isend(&data,siz,MPI_CHAR,dest,tag,MPI_COMM_WORLD,&req);
		
	}
	int rc = MPI_Get_count(&status,MPI_CHAR,&count);
	printf("The message received from proc %d from tag %d into the proc %d\n",status.MPI_SOURCE,status.MPI_TAG,rank);
	MPI_Finalize();
	return 0;
}