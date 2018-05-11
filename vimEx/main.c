#include <stdio.h>
extern int add(int num1, int num2);
extern int sub(int num1, int num2);
extern int mul(int num1, int num2);
extern int div(int num1, int num2);

int main(void)
{
	int num1, num2, result;
	
	result = add(num1, num2);
	result = sub(num1, num2);
	result = mul(num1, num2);
	result = div(num1, num2);

	return 0;
}

