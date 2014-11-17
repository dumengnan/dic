#include<stdio.h>
#include<string.h>


#define bufsize 128

int str_end(char *dest, char *src)
{
	int len_dest = strlen(dest);
	int len_src = strlen(src);
	while(*(dest+len_dest - 1) == *(src+len_src - 1) && len_src != 0)
	{
		len_dest--;
		len_src--;
	}
	if(len_src == 0)
		return 1;
	else
		return 0;
}
int main(void)
{
	char strdest[bufsize] = "hellodci";
	char strsrc[bufsize] = "dci";
	int end_str;

	end_str = str_end(strdest, strsrc);

	if(end_str == 1)
		printf("the strsrc in strdest\n");
	else
		printf("the strsrc not in strdest\n");

	return 0;
}
