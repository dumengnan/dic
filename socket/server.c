#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/syscall.h>
#include <linux/aio_abi.h>
#include <inttypes.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <aio.h>
#include <pthread.h>

#define BUF_SIZE 1024

inline int io_setup(unsigned nr, aio_context_t *ctxp)
{
	return syscall(__NR_io_setup, nr, ctxp);
}

inline int io_destroy(aio_context_t ctx)
{
	return syscall(__NR_io_destroy, ctx);
}

inline int io_submit(aio_context_t ctx, long nr, struct iocb **iocbpp)
{
	return syscall(__NR_io_submit, ctx, nr, iocbpp);
}

inline int io_getevents(aio_context_t ctx, long min_nr, long max_nr,
		struct io_event *events, struct timespec *timeout)
{
	return syscall(__NR_io_getevents, ctx, min_nr, max_nr, events, timeout);
}

void io_init(int fd)
{
	aio_context_t ctx;//对应内核中的一个结构，为异步ＩＯ请求提供上下文环境
	struct iocb cb; //iocb用来完整地描述一个ＩＯ请求
	struct iocb *cbs[1];
	char data[4096];
	struct io_event events[1];
	int ret;
	


	ctx = 0;
	
	ret = io_setup(128, &ctx);//建立一个io任务
	if(ret < 0)
	{
		perror("io_setup error");
		exit(1);
	}
	
	//setup io control block
	memset(&cb, 0, sizeof(cb));
	cb.aio_fildes = fd;//指定要操作的文件指针
	cb.aio_lio_opcode = IOCB_CMD_PREAD;//表示操作的类型

	//command-specific options
	cb.aio_buf = (uint64_t)(uintptr_t)data;
	cb.aio_offset = 0;
	cb.aio_nbytes = 4096;

	cbs[0] = &cb;
	
	ret = io_submit(ctx, 1, cbs);//提交io任务
	if(ret != 1)
	{
		if(ret < 0)
			perror("io_submit error");
		else
			fprintf(stderr, "could not sumbit io");
		exit(1);
	}

	ret = io_getevents(ctx, 1, 1, events, NULL);//提供一个io_event数组给内核copy完成的io请求
	printf("the client send message is %s\n", data);

	ret = io_destroy(ctx);//销毁io任务
	if(ret < 0)
	{
		perror("io_destroy error");
		exit(1);
	}

}


int main()
{
	int sockfd;
	int sin_size;
	struct sockaddr_in addr, cliaddr;
	
	
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("createSocket");
		exit(1);
	}
	

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(7091);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	
	if(bind(sockfd,(struct sockaddr *)&addr,sizeof(struct sockaddr))==-1)
	{
		perror("bind");
		return -1;
	}
	

	if(listen(sockfd,10)==-1)
	{
		perror("listen");
		return -1;
	}
	
	
	printf("server is running!\n");
	
	while(1) 
	{
		int new_fd;
  		struct aiocb my_aiocb;
		sin_size = sizeof(struct sockaddr_in);
		
	
		if((new_fd = accept(sockfd, (struct sockaddr *)&cliaddr, (socklen_t*)&sin_size))==-1)
		{
			perror("accept");
			return -1;
		}

		printf("Thread id %u accept connect, fd: %d\n", (unsigned int)pthread_self(), new_fd);
		io_init(new_fd);
		
	}
	close(new_fd);
}
