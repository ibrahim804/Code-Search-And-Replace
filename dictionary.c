#include <stdio.h>
main(){
	int x,y,z,k;
	char w[5][10]={"mad","mango","ibrahim","moon","yaap"};
	char m[5][10]={"senseless","a fruit","mad","phoebe","yes"};
	char g[20];
	
	scanf("%s", g);


	for(x=0;x<5;x++){
		z=strcmp(g,w[x]);
		if(z==0)break;
	}
	if(x==5)printf("not found\n");
	else printf("%s\n", m[x]);
	return 0;
}
