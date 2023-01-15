#include <stdio.h>
#include <mpi.h>
#include <string.h>

int main(int argc,char ** argv){

	char outmsg[100] = "Hello Amith!";
	char inmsg[100];
	int rank,size;
	int msgsize = strlen(outmsg);
	MPI_Status stat;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	if(rank == 0)
	MPI_Send(&outmsg,msgsize,MPI_CHAR,1,1,MPI_COMM_WORLD);
	if(rank == 1){
		MPI_Recv(&inmsg,msgsize,MPI_CHAR,0,1,MPI_COMM_WORLD,&stat);
		printf("The recieved msg is %s\n",inmsg);
	}
	MPI_Finalize();
	return 0;
}
