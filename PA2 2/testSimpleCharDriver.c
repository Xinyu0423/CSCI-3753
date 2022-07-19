#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>

#define DEVICE_PATH "/dev/PA2_simple_char_driver"
#define BUFFER_SIZE 1024

int main(){
	int file = open(DEVICE_PATH, O_RDWR);
	char input='z';
	int readSize=0;
	char* buffer;
	int offset=0;
	int whence;
	while(input!='e'){
		printf("Press r to read from device\n");
		printf("Press w to write to the device\n");
		printf("Press s to seek into the device\n");
		printf("Press e to exit from the device\n");
		printf("Press anything else to keep reading or writing from the device\n");
		printf("Enter command:\n");
		scanf("%c",&input);

		if(input=='r'){
			printf("Please enter number of bytes you want to read\n");
			scanf("%d",&readSize);
			char *tempBuffer=malloc(readSize);
			read(file,tempBuffer,readSize);
			printf("Data that been read:%s\n",tempBuffer);
		}else if(input=='w'){
			printf("Please enter a string you want to wirte\n");
			scanf("%c",buffer);
			write(file,buffer,strlen(buffer));
			while(getchar() != '\n');
		}else if(input=='s'){
			printf("Please enter your offset value");
			scanf("%d",&offset);
			printf("Please enter your whence value\n");
			scanf("%d",&whence);
			lseek(file,offset,whence);
		}else if(input=='e'){
			//exit=1;
			printf("You have exitted the device\n");
			return 0;
		}
		getchar();
	}
	close(file);
	return 0;
}
