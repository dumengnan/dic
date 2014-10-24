#include<stdio.h>
#include<dirent.h>
#include<string.h>

#define bufsize 1024


void list(char *path, int level)
{
	struct dirent *ent = NULL;
	DIR *pdir;
	char buf[bufsize];
	int t;

	if((pdir = opendir(path)) != NULL)
	{
		while(NULL != (ent  = readdir(pdir)))
		{
			if(ent->d_type == 8)
			{
				for(t = 0; t < level; t++)
				{
					printf("--");
				}
				printf("file:\t%s\n", ent->d_name);
			}
			else 
				if(ent->d_name[0] != '.')
				{
					printf("\n[Dir]:\t%s\n", ent->d_name);
					sprintf(buf, "%s/%s", path, ent->d_name);
					list(buf, level+1);
					printf("返回[%s]\n\n", buf);
				}

		}
		closedir(pdir);
	}
	else
		printf("open dir-[%s] failed\n", path);
}


int main()
{
	char path[] = "/home/dic/desktop";
	list(path, 0);
	return 0;
}
