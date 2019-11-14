#include <stdio.h>

int sum(int a, int b)
{
	return a+b;
}

void main()
{

	int result,wide,length;
	scanf("%d%d",&wide,&length);
	result=sum(wide,length);
	printf("%d\n",result);
	
}







