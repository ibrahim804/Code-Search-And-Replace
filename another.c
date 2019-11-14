#include <stdio.h>
#include <string.h>
int main(void){
	int d;
	char str[1],ami;
	printf("Enter the day of this month's:\t");
	scanf("%d", &d);
	for(ami=0;ami<1;ami++){

		printf("Enter the current month name:\t");
		scanf("%s", &str[ami]);
	}

	if(d==29 && str[ami]=="February"){
		printf("\nHello people!!\n");
	}
	else printf("\nHello other people\n");
	return 0;
}


