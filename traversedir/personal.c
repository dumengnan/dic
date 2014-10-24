#include<stdio.h>
#include<string.h>
#include<dirent.h>
#include<errno.h>
#include<unistd.h>
#include<sys/stat.h>
#define bufsize 10240
void traverse(char *pathname);

int main(int argc, char *argv[])
{
	char buffer[bufsize];
	if(argc < 2)
	{
		printf("the programe need a dirname\n");
		return 1;
	}
	chdir(argv[1]);
	getcwd(buffer, bufsize);
	traverse(buffer);

	return 0;
}

void traverse(char *pathname)
{
	DIR *dir = NULL;
	struct dirent *ent;
	char buf[bufsize];
	memset(buf, '\0', bufsize);
	dir = opendir(pathname);

	while(ent = readdir(dir))
	{
		if(strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
			continue;
		sprintf(buf, "%s/%s", pathname, ent->d_name);
		struct stat st;
		stat(buf , &st);
		if(S_ISDIR(st.st_mode))
			traverse(buf);
		else
			printf("%s\n", buf);
	}
	closedir(dir);
}
