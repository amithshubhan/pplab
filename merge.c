#include <stdlib.h>
#include <stdio.h>
#include <omp.h>


void merge(int a[],int l,int mid,int r,int n){
	int low = l,high = mid+1,c[n];
	int k = l;
	while(low <= mid && high <= r){
		if(a[low] <= a[high]){
			c[k++] = a[low++];
		}
		else{
			c[k++] = a[high++];
		}
	}
	while(low <= mid){
		c[k++] = a[low++];
	}
	while(high <= r){
		c[k++] = a[high++];
	}
	for(int i=l;i<=r;i++){
		a[i] = c[i];
	}
}

void merge_sort(int a[],int l, int r,int n){
	if(l >= r) return;
	int mid = (l+r)/2;
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			merge_sort(a,l,mid,n);
		}
		#pragma omp section
		{
			merge_sort(a,mid+1,r,n);
		}
		

	}
	merge(a,l,mid,r,n);
}

int main(int argc,char * argv[]){
	// int * arr = malloc(sizeof(int)*10);
	int n;
	scanf("%d",&n);
	double start,end,val=0;
	int arr[n];
	for(int i=0;i<n;i++){
		arr[i] = rand()%1000;
		printf("%d ",arr[i]);
		printf("\n");
	}

	double start1,end1,val1;
	 start1 = omp_get_wtime();
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			if(arr[i] < arr[j]){
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
	 end1 = omp_get_wtime();
	 val1 = end1 - start1;

	start = omp_get_wtime();
	merge_sort(arr,0,n-1,n);
	end = omp_get_wtime();
	val = end - start;
	for(int i=0;i<n;i++){
		printf("%d ",arr[i]);
	}
	printf("\ntime taken is %f\n",val1);
	printf("time taken is %f",val);
}