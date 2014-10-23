#include<stdio.h>
#include<stdlib.h>
#include<sys/msg.h>

#define bufsize 1024

int main(void)
{
	char some_data[bufsize];
	char some_data1[bufsize];
	pid_t id;
	int msgid; 
	msgid = msgget((key_t)123, 0666|IPC_CREAT);
	if(msgid == -1)
	{
		printf("msgget is error\n");
		exit(1);
	}

	id = fork();
	if(id < 0)
	{
		printf("fork is error\n");
		exit(1);
	}
	else
		if(id == 0)
		{
			printf("enter some text:\n");
			fgets(some_data, bufsize, stdin);

			if(msgsnd(msgid,(void *)&some_data, bufsize, 0) == -1)
			{
				printf("msgnd is error\n");
				exit(1);
			}
		}
		else
		{
			wait(NULL);
			if(msgrcv(msgid, (void *)&some_data1, bufsize, 0,0) == -1)
			{
				printf("msgrcv is error\n");
				exit(1);
			}
			printf("you input in the child is %s\n", some_data1);

 			if(msgctl(msgid, IPC_RMID, 0 ) == -1)
			{
				printf("msgctl is error\n");
				exit(1);
			}
		}


	return 0;
}
