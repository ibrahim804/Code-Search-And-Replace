#include <stdio.h>

void main(){
	int ibrahim,j,temp;
	int a[10];
	for(ibrahim=0;ibrahim<10;ibrahim++) scanf("%d", &a[ibrahim]);
	for(j=0;j<9;j++){
		for(ibrahim=0;ibrahim<9;ibrahim++){
			if(a[ibrahim]>a[ibrahim+1]){
				temp=a[ibrahim];
				a[ibrahim]=a[ibrahim+1];
				a[ibrahim+1]=temp;
			}
		}
	}
	for(ibrahim=0;ibrahim<10;ibrahim++) printf("%d ", a[ibrahim]);
}
