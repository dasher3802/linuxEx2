/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2017.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Listing 24-2 */

#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "tlpi_hdr.h"

int
main(int argc, char *argv[])
{
    int fd, flags;
    char template[] = "/tmp/testXXXXXX";

    setbuf(stdout, NULL);                   /* stdout의 버퍼링을 막는다. */

	//파일 열기
    fd = mkstemp(template);
    if (fd == -1)
        errExit("mkstemp");

	//현재 커서의 위치를 출력
    printf("File offset before fork(): %lld\n", (long long) lseek(fd, 0, SEEK_CUR));

	//fcntl은 파일의 플래그를 얻어오는 함수 ex)쓰기용, 읽기용
    flags = fcntl(fd, F_GETFL);
    if (flags == -1)
        errExit("fcntl - F_GETFL");
    
	//O_APPEND는 파일끝에 추가해서 작성하는 옵션
	printf("O_APPEND flag before fork() is: %s\n", (flags & O_APPEND) ? "on" : "off");

    switch (fork()) {
    case -1:// fork 실패시
        errExit("fork");

	case 0:     /* 자식 : 파일 오프셋과 상태 플래그를 변경 */
        if (lseek(fd, 1000, SEEK_SET) == -1)
            errExit("lseek");

        flags = fcntl(fd, F_GETFL);         /* 현재 플래그 읽기 */
        if (flags == -1)
            errExit("fcntl - F_GETFL");
        flags |= O_APPEND;                  /* O_APPEND를 설정 */
        if (fcntl(fd, F_SETFL, flags) == -1)
            errExit("fcntl - F_SETFL");
        _exit(EXIT_SUCCESS);

	default:    /* 부모 : 자식이 만든 변경을 볼 수 있는지 확인 */
        if (wait() == -1)
            errExit("wait");                /* 자식의 종료를 기다린다. */
        printf("Child has exited\n");

        printf("File offset in parent: %lld\n", (long long) lseek(fd, 0, SEEK_CUR));

		//플래그를 읽어옴
        flags = fcntl(fd, F_GETFL); 
        if (flags == -1)
            errExit("fcntl - F_GETFL");

		//바뀐 플래그를 출력
        printf("O_APPEND flag in parent is: %s\n", (flags & O_APPEND) ? "on" : "off");
        exit(EXIT_SUCCESS);
	}

