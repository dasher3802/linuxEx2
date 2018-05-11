#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main(void)
{
	pid_t pid;
	int temp;
	int fd;
	char *pa = "나는 부모입니다.\n";
	char *ch = "나는 자식입니다.\n";

	fd = open("test.txt", O_RDWR | O_CREAT | O_TRUNC, \
					S_IRWXU | S_IRGRP | S_IWGRP | S_IROTH);
	pid = fork();

	for(int i = 0; i < 5; i++)
	{
		switch(pid)
		{
			case -1:
				perror("fork failed");
				exit(1);
			case 0:
				write(fd, "나는 자식입니다.\n", strlen(ch));
				break;
			default:
				write(fd, "나는 부모입니다.\n", strlen(pa));
		}
		sleep(1);
	}
	close(fd);

	if(pid == 0)
		exit(0);

	if(WIFEXITED(temp))
		printf("자식 정상종료 : %d\n", WEXITSTATUS(temp));
	else if(WIFSIGNALED(temp))
		printf("자식 비정상 종료 : %d\n", WTERMSIG(temp));
	else
		printf("자식 멈춤 : %d\n", WSTOPSIG(temp));
	exit(0);
}
