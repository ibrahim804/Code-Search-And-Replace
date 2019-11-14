#include <stdio.h>
#include <string.h>
main(){
	int i,j,k;
	char *p[3]={"one","two","three"};
	for(i=1;i<=3;i++){
		for(j=1;j<=3;j++){
			for(k=1;k<=3;k++){
				if( j!=i && k!=j && k!=i){
					printf("%s %s %s\n", p[i-1],p[j-1],p[k-1]);
				}
			}
		}
	}
}
