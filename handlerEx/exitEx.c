#include <stdio.h>
#include <stdlib.h>

//static 으로 선언해서 메모리에 미리 넣어두어야 한다.

static void testExitHandler(int exitStatus, void *arg)
{
	printf("testExitHandler : exitStatus = %d, arg = %ld\n",
					exitStatus, (long)arg);
}
int main(void)
{
	//종료 핸들러 등록
	if(on_exit(testExitHandler, (void*)10) != 0)
		printf("Handler error1\n");

	if(on_exit(testExitHandler, (void*)20) != 0)
		printf("Handler error2\n");

	//프로그램의 시작
	printf("exit Handler Program : Start!!!\n");

	exit(2);
}
