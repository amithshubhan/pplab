#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <stdbool.h>
bool ifprime(int n){
	if(n == 1) return false;
	if(n == 2) return true;
	for(int i=2;i*i <= n;i++){
		if(n%i == 0) return false;
	}
	return true;
}

int main(){

	int n;
	scanf("%d",&n);
	#pragma omp parallel for
		

		for(int i=1;i<=n;i++){
			char done[] = "not prime\0";
			char notdone[] = "prime\0";
			if(ifprime(i)){
				// char s[] = "prime\0";
				printf("%d: %d is %s\n",omp_get_thread_num(),i,notdone);
			}
			else
			printf("%d: %d is %s\n",omp_get_thread_num(),i,done);
		}
	
	return 0;
}