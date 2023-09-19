#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int8_t write_buf[1024];
int8_t read_buf[1024];
#define MAX_LIMIT 1024

int main()
{
	int fd;
	char option;
	printf("DEMO OF char driver\n");

	fd = open("/home/yocto/Documents/char/char_dev",O_RDWR);
	if(fd<0)
	{
		printf("cannot open file\n");fflush(stdout);
		return -1;
	}
//	while(1)
	{
		printf("............menu.............\n");
		printf("        1. write             \n");
		printf("        2. Read               \n");
		printf("        3.Exit                \n");
		printf(" your option : ");fflush(stdout);
		scanf("%c",&option);

		switch(option)
		{
			case '1' :
				printf("Enter string : \n");
				scanf("%s", write_buf);
				printf("data written\n");fflush(stdout);
				write(fd,write_buf,strlen(write_buf)+1);
				printf("done..\n");
				break;

			case '2' :
				printf("Data is reading..\n");
				read(fd,read_buf,1024);
				printf("Data = %s\n\n",read_buf);
				break;
			case '3' :
				close(fd);
				exit(1);
				break;
			default :
				printf("enter valid option \n");
				break;
		}
	}
close(fd);
}




