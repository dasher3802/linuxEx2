/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2017.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Listing 24-3 */

#define _BSD_SOURCE     /* To get sbrk() declaration from <unistd.h> in case
                           _XOPEN_SOURCE >= 600; defining _SVID_SOURCE or
                           _GNU_SOURCE also suffices */
#include <sys/wait.h>
#include "tlpi_hdr.h"

static int func(int arg)
{
    int j;


    for (j = 0; j < 0x100; j++)
        if (malloc(0x8000) == NULL)
            errExit("malloc");
    //sbrk(0)은 프로그램이 사용하는 데이터의 끝주소를 리턴
	printf("Program break in child:  %10p\n", sbrk(0));

    return arg;
}

int main(int argc, char *argv[])
{
	//argv[1]인자로 int형 범위의 숫자를 입력받는다.
    int arg = (argc > 1) ? getInt(argv[1], 0, "arg") : 0;
    pid_t childPid;
    int status;

    setbuf(stdout, NULL);           /* stdout의 버퍼링을 막는다. */

	//부모 주소 출력
    printf("Program break in parent: %10p\n", sbrk(0));

    childPid = fork();
    if (childPid == -1)
        errExit("fork");

    if (childPid == 0)              /* 자식 노드일때 */
        exit(func(arg));            /* 부모에게 exit를 이용하여 데이터 전달(8비트까지) */

    /* 부모는 자식이 종료되기를 기다린다. status의 값을 통해 func()의 결과를 알아낼 수 있다. */

    if (wait(&status) == -1)
        errExit("wait");
	
	//부모주소가 바뀌었는지 확인
    printf("Program break in parent: %10p\n", sbrk(0));
	//사용되는 주소 크기와 부모 프로세서가 받은 값 출력
    printf("Status = %d %d\n", status, WEXITSTATUS(status));

    exit(EXIT_SUCCESS);
}
