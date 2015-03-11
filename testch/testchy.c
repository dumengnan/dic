#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int main(void)
{
	FILE *fp;
	unsigned char c1 = 0,  c2 = 0;
	unsigned char s[2000][4] = {{0},{0}};
	unsigned int ncnt = 0, ntot = 0, i = 0, n[2000] = {0};

	if((fp = fopen("1.txt", "r")) == NULL)
	{
		perror("open failed");
		return 1;
	}

	while((c1 = fgetc(fp)) != (unsigned char )EOF)
	{
		if(c1 >= 0xb0 && c1 <= 0xf7)
		{
			c2 = fgetc(fp);
			if(c2 >= 0xa1 && c2 <= 0xfe)
			{
				printf("%c%c", c1, c2);
				for(i = 0; i<ncnt; ++i)
					if(s[i][0] == c1 && s[i][1] == c2)
						break;
				s[i][0] = c1;
				s[i][1] = c2;
				++n[i];

				if(i == ncnt)
					++ncnt;
				++ntot;
			}
		}
	}
	printf("\n\ntotal:%u\n", ntot);
	for(i = 0; i< ncnt; ++i)
		printf("%s:%u\n", s[i], n[i]);
	fclose(fp);

	return 0;
}
