#include<stdio.h>
#include<linux/kernel.h>
#include<sys/syscall.h>
#include<unistd.h>
#include<stdlib.h>

int main() {
	int number1 = 5;
	int number2 = 6;
	int temp;

	int returnValue=syscall(334, number1, number2, &temp);
	printf("result is %d \n",temp);
	return 0;

}
