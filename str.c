#include<stdio.h>
#include<stdlib.h>

#define bufsize 100

char *copy(char *strdest, char *strsrc)
{
	if( strdest == NULL || strsrc == NULL)
		return NULL;
	if(strdest == strsrc)
		return strdest;
	char *tempptr = strdest;
	while(*strdest++ = *strsrc++);
	return tempptr;
}

char *str_link(char *strdest, char *strsrc)
{
	if(strdest == NULL || strsrc == NULL)
		return NULL;
	char *temp = strdest;
	while(*strdest != '\0')
		strdest++;/*  * prior to ++   so it cannot write in while */
	
	while((*strdest++ = *strsrc++) != '\0');


	*strdest = '\0';
	
	return temp;
}

int str_cmp(char *s, char *t)
{
	int i = 0;
	for(; *s == *t; s++, t++)
		if(*s == '\0')
			return 0;
	return *s - *t;
}
int main(void)
{
	char *copy_str;
	char *link_str;
	int cmp_str;

	char s1[bufsize] = "hello";
	char s2[bufsize] = "dci";

/*	copy_str = copy(s1, s2);*/
	
/*	printf("after copy the string is %s\n", copy_str);*/
	
/*	link_str = str_link(s1, s2);
	printf("after link the string is %s\n", link_str);
*/
	cmp_str = str_cmp(s1, s2);
	printf("after strcmp the result is %d\n", cmp_str);

	return 0;
}
