/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2017.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Listing 26-1 */

#include <sys/wait.h>
#include <time.h>
#include "curr_time.h"              /* Declaration of currTime() */
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    int numDead;       /* 기다리고 있는 자식의 수 */
    pid_t childPid;    /* 기다리는 자식의 프로세스 ID */
    int j;

    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s sleep-time...\n", argv[0]);

    setbuf(stdout, NULL);           /* stdout이 버퍼링되지 않게 함 */

    for (j = 1; j < argc; j++) {    /* 인수의 수만큼 자식 프로세서 생성 */
        switch (fork()) {
        case -1:
            errExit("fork");

        case 0:                     /* 자식 프로세스는 잠시 잠들었다가 종료 */
            printf("[%s] child %d started with PID %ld, sleeping %s "//currTime()은 현재시간 출력
                    "seconds\n", currTime("%T"), j, (long) getpid(),
                    argv[j]);
			//실행 인자로 받은 수만큼 자식프로세서 sleep
            sleep(getInt(argv[j], GN_NONNEG, "sleep-time"));
            _exit(EXIT_SUCCESS);

        default:                    /* 부모 프로세스는 계속 진행 */
            break;
        }
    }

    numDead = 0;
    for (;;) {                      /* 부모는 자식 프로세스들이 종료되기를 기다린다. */
        childPid = wait(NULL);
		//자식 프로세서가 없는경우 -1
        if (childPid == -1) {
            if (errno == ECHILD) {
                printf("No more children - bye!\n");
                exit(EXIT_SUCCESS);
            } else {                /* 예기치 못한 에러 발생 */
                errExit("wait");
            }
        }
		//자식이 종료된경우
        numDead++;
        printf("[%s] wait() returned child PID %ld (numDead=%d)\n",
                currTime("%T"), (long) childPid, numDead);
    }
}
