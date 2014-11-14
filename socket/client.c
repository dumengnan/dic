#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("%s: input IP & port\n",argv[0]);
		return 1;
	}
	int sockfd,numbytes;
	char buf[100] = "hello world";
	struct hostent *he;
	struct sockaddr_in their_addr;
	
	
	he = gethostbyname(argv[1]);
	

	if((sockfd = socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("socket");
		exit(1);
	}
	
	
	their_addr.sin_family = AF_INET;
	their_addr.sin_port = htons(7091);
	their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	bzero(&(their_addr.sin_zero),8);
	
	
	if(connect(sockfd,(struct sockaddr *)&their_addr,sizeof(struct sockaddr))==-1)
	{
		perror("connect");
		exit(1);
	}

	
	
	if(send(sockfd,buf,strlen(buf),0)==-1)
	{
		perror("send");
		exit(1);
	}

	//if((numbytes = recv(sockfd, buf, 100, 0)) == -1)
	//{
	//	perror("recv");
	//	return 1;
	//}

	printf("recv: %s\n", buf);
	
	close(sockfd);
	return 0;
}
