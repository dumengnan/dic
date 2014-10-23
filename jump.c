#include<stdio.h>
#include<stdlib.h>
#include<setjmp.h>

static jmp_buf buf;


void second(void)
{
	printf("this is second\n");
	longjmp(buf, 1);
}

void first(void)
{
	second();
	printf("this is first\n");
}
int main(void)
{
	if(!setjmp(buf))
	{
		first();
	}
	else
	{
		printf("main\n");
	}
	
	return 0;
}
