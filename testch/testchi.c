#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main(void)
{
	int  ch2;
	int i = 0, j = 0;
	int x = 0;
	int str[1000][3] = {{0},{0}};
	FILE *fstream;
	if((fstream = fopen("a.txt", "r")) == NULL)
	{
		printf("file open error\n");
		return 1;
	}
	while(!feof(fstream))
	{
		int ch1 = getc(fstream);
		if(ch1 == -1)
			break;
		
		if( ch1 > 0x80)
		{		
				for(j=0 ; j < i; j++)
				{							
					if(ch1 == str[j][0]&&(ch2 = fgetc(fstream)) == str[j][1])
					{
						str[j][2]  = str[j][2]+ 1;
						break;
					}
				}
				if(j == i)
				{
					str[i][0] = ch1;
					str[i][1] = getc(fstream);
					str[i][2] = 1;
					i++;
				}
		
		}
	}
	for(x =0 ; x < i; x++)
		printf("%c%c%d\n", str[x][0], str[x][1], str[x][2]);
	fclose(fstream);
	return 0;

}
