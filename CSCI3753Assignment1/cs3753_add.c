#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/uaccess.h>
asmlinkage long sys_cs3753_add(int number1,int number2,int *result){
	int temp=number1+number2;
	//copy_to_user(void __user *to, const void *from, unsigned long n);
	//unsigned long n is the size of n
	copy_to_user(result,&temp,4);
	printk(KERN_ALERT"Number1= %d\n",number1);
	printk(KERN_ALERT"Number2= %d\n",number2);
	printk(KERN_ALERT"The result of adding two numbers is: %d\n",temp);
	printk(KERN_ALERT"The result location of adding two numbers is: %p\n",result);
}
