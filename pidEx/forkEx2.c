#include <stdio.h>
#include <unistd.h>
int global;
int main(void){
	int i = 20; pid_t pid; int status;

	if((pid = fork()) == 0){
		global = global + 10;
		i += 10;
	}
	else{
		global += 100;
		i+=100;
	}
	printf("global = %d; i = %d\n", global, i);
}
