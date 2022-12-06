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
	int arr[10];
	for(int i=0;i<10;i++){
		arr[i] = rand()%1000;
		printf("%d ",arr[i]);
		printf("\n");
	}
	merge_sort(arr,0,9,10);
	for(int i=0;i<10;i++){
		printf("%d ",arr[i]);
	}
}