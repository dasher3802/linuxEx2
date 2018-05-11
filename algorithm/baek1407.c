#include <stdio.h>
#include <time.h>

long function(long num);

int main(void)
{
	long num1, num2, tot;
	float gap;

//	printf("두 수 입력 : ");
	scanf("%ld %ld",&num1, &num2);
	
	tot = function(num2) - function(num1 - 1);

	printf("%ld", tot);

	return 0;
}

long function(long num)
{
	long tot = 0;
	long b = 2;
	long hol = (num + 1)/2;

	while(b <= num)//2의 개수, 4의 개수, 8의 개수... 더하는 반복문
	{
		tot += (num+b) / (b*2) * b; 
		b *= 2;
	}

	return tot + hol;//짝수합 + 홀수합
}
/*
자연수 N이 주어지면, 자연수를 유지하면서 N을 2로 몇 번까지 나눌 수 있는지를 생각해 볼 수 있다.
즉, N의 모든 약수 중 2의 거듭제곱 꼴이면서 가장 큰 약수를 생각하는 것이다. 예를 들어 15의 경우는
2로 한 번도 나눌 수 없으므로 2^0 = 1이 해당되고, 40의 경우는 2로 세 번까지 나눌 수 있으므로 2^3 = 8이 해당된다.
이러한 약수를 함수값으로 가지는 함수 f(x)를 정의하자. 즉, f(15) = 1이고, f(40) = 8이다. 두 자연수 A, B(A≤B)가 주어지면,
A 이상 B 이하의 모든 자연수에 대해서, 그 자연수의 모든 약수 중 2의 거듭제곱 꼴이면서 가장 큰 약수들의 총 합을 구하는
프로그램을 작성하시오. 즉 아래와 같은 수식의 값을 구해야 한다.

입력
176 177
출력 
17
입력 
5 9
출력 
13
입력
25
28
출력
8


f(A) + f(A+1) + ... + f(B-1) + f(B)
2  = 2 x 1 = 2
4  = 2 x 1 + 4 x 1 = 6
6  = 2 x 2 + 4 x 1 = 8
8  = 2 x 2 + 4 x 1 + 8 x 1 = 16
10 = 2 x 3 + 4 x 1 + 8 x 1 = 18
12 = 2 x 3 + 4 x 2 + 8 x 1 = 22
14 = 2 x 4 + 4 x 2 + 8 x 1 = 24
16 = 2 x 4 + 4 x 2 + 8 x 1 + 16 x 1 = 40 
18 = 2 x 5 + 4 x 2 + 8 x 1 + 16 x 1 = 42
20 = 2 x 5 + 4 x 3 + 8 x 1 + 16 x 1 = 46
22 = 2 x 6 + 4 x 3 + 8 x 1 + 16 x 1 = 48
24 = 2 x 6 + 4 x 3 + 8 x 2 + 16 x 1 = 56
26 = 2 x 7 + 4 x 3 + 8 x 2 + 16 x 1 = 58

주어진 수가 n 일경우
2의 개수 = (n+2)/4
4의 개수 = (n+4)/8
8의 개수 = (n+8)/16
16의 개수 = (n+16)/32
...
b의 개수 = (n + b)/b*2
*/
