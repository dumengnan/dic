#include<stdio.h>

#define bufsize 100

void fun(char *s)
{
	char *p = s;
	int count = 0;
	int i = 0;
	char *a = s;

	while(*p != '\0' )
	{
		
		if(*p == '*')
			count++;
		else
			a[i++] = *p;
		p++;
	}
	printf("the count is %d\n", count);
	while(count > 0)
	{
		a[i++] = '*';
		count--;
	}


}

int main(void)
{
	char p[bufsize] = "\0";
	printf("please input a string include the *\n");
	scanf("%s", p);

	printf("before del the string is\n------- %s------\n", p);
	fun(p);

	printf("after del the string is \n--------%s------\n", p);


	return 0;
}
