#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main(void)
{
	pid_t pid;
	int sum = 0;
	int temp;
	int s_num = 1;
	int e_num;

	pid = vfork();
	printf("pid = %d\n", pid);
	switch(pid)
	{
			case -1:
				perror("fork failed");
				exit(1);
			case 0:
				e_num = 5000;
				break;
			default:
				e_num = 10000;
	}
	
	for(; s_num <= e_num; s_num++)
		sum += i;

	if(pid != 0)
	{
		if(WIFEXITED(temp))
			printf("자식 정상종료 : %d\n", WEXITSTATUS(temp));
		else if(WIFSIGNALED(temp))
			printf("자식 비정상 종료 : %d\n", WTERMSIG(temp));
		else
			printf("자식 멈춤 : %d\n", WSTOPSIG(temp));
		
		printf("자식 부모 합 : %d\n", sum);
	}
	else
	{
		printf("자식 합 : %d\n", sum);
	}
	exit(0);
}
