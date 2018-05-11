#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	printf("Running ps with execlp\n");
	execlp("ps", "ps", "-ax", (char*)NULL);
	printf("Done.\n");
	exit(0);
}
