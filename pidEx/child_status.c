/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2017.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Listing 26-3 */

#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "print_wait_status.h"          /* Declares printWaitStatus() */

void sigHandler(int sig)
{
	printf("\n아앗! 신호다.\n");
}

int main(int argc, char *argv[])
{
    int status;
    pid_t childPid;

    if (argc > 1 && strcmp(argv[1], "--help") == 0)
        printf("%s [exit-status]\n", argv[0]);

    switch (fork()) {
    case -1: printf("fork");

	case 0:	/* 자식 : 주어진 상태값을 갖고 바로 종료하거나 시그널을 기다리기를 반복한다.*/
        printf("Child started with PID = %ld\n", (long) getpid());
        if (argc > 1)                   /* 명령행으로부터 상태값이 주어졌는가? */
			exit(atoi(argv[1]));
        else                            /* 아니면 시그널을 기다린다. */
            for (;;)
                pause();
        exit(EXIT_FAILURE);             /* 여기에 도달하지는 않지만, 좋은 코드 스타일이다. */

	default: /* 부모: 계속해서 자식이 종료하거나 시그널에 의해 종료될 때까지 기다린다.*/
		//종료되지 않게 시그널을 등록한다.
		if(signal(SIGINT, sigHandler) == SIG_ERR)
			printf("시그널 등록 에러\n");

		for (;;) {
            childPid = waitpid(-1, &status, WUNTRACED
#ifdef WCONTINUED       /* 리눅스 예전 버전에서는 지원하지 않는다. */
                                                | WCONTINUED
#endif
                    );
            if (childPid == -1)
                printf("waitpid");

            /* status 값을 16진수와 2개의 10진수 바이트로 출력한다. */

            printf("waitpid() returned: PID=%ld; status=0x%04x (%d,%d)\n",
                    (long) childPid,
                    (unsigned int) status, status >> 8, status & 0xff);
            printWaitStatus(NULL, status);

            if (WIFEXITED(status) || WIFSIGNALED(status))
                exit(EXIT_SUCCESS);
        }
    }
}
