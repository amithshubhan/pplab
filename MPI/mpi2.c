#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <string.h>

int main(int argc,char ** argv){

	int size,rank;
	char outmsg[100] = "here amith itself!";
	char outmsg2[100] = "here anith itself!";
	char inmsg[100];
	int tag1 = 1,tag2 = 2;
	MPI_Status stat;
	int msgsize = strlen(outmsg);
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	if(rank == 0){
		MPI_Send(&outmsg,msgsize,MPI_CHAR,1,tag1,MPI_COMM_WORLD);
		MPI_Recv(&inmsg,msgsize,MPI_CHAR,1,tag2,MPI_COMM_WORLD,&stat);
		printf("The msg recieved from 1 to 0 is %s\n",inmsg);
	}
	else if(rank == 1){
		MPI_Send(&outmsg2,msgsize,MPI_CHAR,0,tag2,MPI_COMM_WORLD);
		MPI_Recv(&inmsg,msgsize,MPI_CHAR,0,tag1,MPI_COMM_WORLD,&stat);
		printf("The msg recieved from 0 to 1 is %s\n",inmsg);
	}
	MPI_Finalize();
}
