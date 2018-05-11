#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <libgen.h>//basename()선언
#include <unistd.h>

#define CMD_SIZE 200

int main(int argc, char *argv[])
{
	char cmd[CMD_SIZE];
	pid_t childPid;

	setbuf(stdout, NULL);//stdout의 버퍼링을 방지

	printf("Parent PID=%ld\n", (long) getpid());

	switch(childPid = fork()){
		case -1:
			printf("fork");
		case 0://자식 : 바로 종료해서 좀비가 된다.
			printf("Child (PID=%ld) exiting\n", (long) getpid());
			_exit(EXIT_SUCCESS);

		default://부모
			sleep(3);//자식 프로세스가 시작하고 종료될 시간을 준다.
			snprintf(cmd, CMD_SIZE, "ps | grep %s", basename(argv[0]));
			cmd[CMD_SIZE - 1] = '0';// 문자열이 널로 끝남을 보장
			printf("cmd : %s\n", cmd);
			system(cmd); //좀비 자식 프로세스를 보여준다.
			
			//좀비 프로세스에게 kill시그널을 보낸다.

			if(kill(childPid, SIGKILL) == -1)
				printf("kill error");
			sleep(3);//자식프로세스가 시그널에 반응할 시간을 준다.
			printf("After sending SIGKILL to zombie (PID=%ld) : \n", (long) childPid);
			system(cmd);

			exit(EXIT_SUCCESS);
	}
}
