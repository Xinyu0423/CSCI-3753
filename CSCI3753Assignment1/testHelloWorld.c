#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>

int main(){
	int result=syscall(333);
	printf("%d \n",result);
	return 0;
}
