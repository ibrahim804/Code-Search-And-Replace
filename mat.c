#include <stdio.h>

int a[5][5],b[5][5],mul[5][5];

void main(){
	int i,j,k,c1,r1,c2,r2;
	printf("Enter 1st matrx dim\n");
	scanf("%d%d", &r1,&c1);
	printf("Enter 2nd matrx dim\n");
	scanf("%d%d", &r2,&c2);
	if(c1==r2){
		printf("Enter the 1st matrx:\n");
		for(i=0;i<r1;i++){
			for(j=0;j<c1;j++){
				scanf("%d", &a[i][j]);
			}
		}
		printf("Enter the 2nd matrx:\n");
		for(i=0;i<r1;i++){
			for(j=0;j<c1;j++){
				scanf("%d", &b[i][j]);
			}
		}

		for(i=0;i<r1;i++){
			for(j=0;j<c2;j++){
				for(k=0;k<c1;k++){
					mul[i][j]=mul[i][j]+a[i][k]*b[k][j];
				}
			}
		}
		for(i=0;i<r1;i++){
			for(j=0;j<c2;j++){
				printf("%d\t", mul[i][j]);
			}
			printf("\n");
		}
	}
	else printf("something error\n");
	return 0;
}
		

