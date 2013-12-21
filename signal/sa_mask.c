/*************************************************************************
	> File Name: process_.c
	> Author: Simba
	> Mail: dameng34@163.com 
	> Created Time: Sat 23 Feb 2013 02:34:02 PM CST
 ************************************************************************/
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<signal.h>

#define ERR_EXIT(m) \
	do { \
		perror(m); \
		exit(EXIT_FAILURE); \
	} while(0)

void handler(int sig);


int main(int argc, char *argv[])
{
	struct sigaction act;
	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGQUIT); // 在信号处理函数执行期间屏蔽SIGQUIT信号，完毕后会抵达
	/* 注意sigprocmask中屏蔽的信号是一直不能抵达的，除非解除了阻塞*/
	act.sa_flags = 0;

	if (sigaction(SIGINT, &act, NULL) < 0)
		ERR_EXIT("sigaction error");

	for (; ;)
		pause();

	return 0;

}

void handler(int sig)
{
	printf("rev sig=%d\n", sig);
	sleep(5);
}



