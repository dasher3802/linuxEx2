#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	pid_t pid;
	char message[50];
	int n;
	
	printf("fork program starting\n");
	pid = fork();
	switch(pid)
	{
		case -1:
		   	perror("fork failed");
	       	exit(1);
		case 0:
			strcpy(message, "This is the child");
			n = 5;
			break;
		default:
			strcpy(message, "This is the parent");
			n = 3;
			break;
	}
	for(; n > 0; n--)
	{
		puts(message);
		sleep(1);
	}
	exit(0);
}
