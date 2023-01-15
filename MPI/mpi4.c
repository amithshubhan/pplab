#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


int mini(int a,int b){
	if(a<=b) return a;
	return b;
}

int main(int argc,char ** argv){
	int rank,size;
	int root = 0;
	MPI_Init(&argc,&argv);

	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status stat;
	int n;
	double ans;
	if(rank == 0){
		printf("Enter the factorial number\n");
		scanf("%d",&n);
	}
	MPI_Bcast(&n,1,MPI_INT,root,MPI_COMM_WORLD);
	
	int subsize = n/size;
	int low = (rank*subsize) + 1;
	int high = (rank+1)*subsize;
	if(rank == size-1) high = n;
	int arr[high-low+1]; 
	int nowsiz = high - low +1;
	int k = 0;
	double locprod = 1;
	printf("Rank : %d, low %d, high %d\n",rank,low,high);
	for(int i=low;i<=high;i++){
		locprod = locprod *(double)i;
	}
	MPI_Reduce(&locprod,&ans,1,MPI_DOUBLE,MPI_PROD,root,MPI_COMM_WORLD);
	if(rank == root){
		printf("The factorial of %d is %f\n",n,ans);
	}
	MPI_Finalize();
	return 0;
}
