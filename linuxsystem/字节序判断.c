#include <stdio.h>
#include <stdlib.h>


int main()
{
	int i=0x12345678;
	if (*(char *)&i==0x12) 
		printf("大端");

	else 
		printf("小端");
	return 0;
}
