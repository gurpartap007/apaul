#include<stdio.h>
#include<signal.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include"header.h"
struct gpio_descriptor_t gpio_desc;
char *hostname,*ip;
static int counter=0;
char *quit_msgU="CALLING...";
char *quit_msgL="YOU";
volatile int running=1;
volatile int complete=0;
volatile int call_connected=0;
volatile char value;
void handler(int sig)
{	
	pid_t pid;	
	if(complete == 1)
	{
		printf("complete = %d\n",complete);
		running=0;
		send_command(&gpio_desc,0x01);
		(void) signal(SIGINT,SIG_DFL);
	}
	else
	{
		printf("complete = %d\n",complete);
		send_command(&gpio_desc,0x84);
		for(counter=0;counter<(strlen(hostname));counter++)
			send_character(&gpio_desc,hostname[counter]);
		send_command(&gpio_desc,0xC1);
		for(counter=0;counter<(strlen(ip));counter++)
			send_character(&gpio_desc,ip[counter]);
		usleep(500000);
		send_command(&gpio_desc,0x01);
		send_command(&gpio_desc,0x81);
		for(counter=0;counter<(strlen(quit_msgU));counter++)
			send_character(&gpio_desc,quit_msgU[counter]);
		send_command(&gpio_desc,0xCa);
		for(counter=0;counter<(strlen(quit_msgL));counter++)
			send_character(&gpio_desc,quit_msgL[counter]);
		running=0;
		send_command(&gpio_desc,0x01);
		(void) signal(SIGINT,SIG_DFL);
	}
}
int main(int argc,char *argv[])
{	
	int ret;
	gpio_desc.gpio_flag = O_WRONLY;
	hostname = malloc(20);
	ip =malloc(strlen(argv[2]));
	hostname = (char *)argv[1];
	ip =(char *)argv[2];
	printf("hostname = %s\n",hostname);
	printf("Ip = %s\n",ip);
	int gpio_fd;

	(void) signal(2,handler);//1st argument is signal name and 2nd argument is signal handler function
	while(running)
	{

		send_command(&gpio_desc,0x01);
		send_command(&gpio_desc,0x84);
		for(counter=0;counter<(strlen(hostname));counter++)
			send_character(&gpio_desc,hostname[counter]);
		send_command(&gpio_desc,0xC1);
		for(counter=0;counter<(strlen(ip));counter++)
			send_character(&gpio_desc,ip[counter]);
		usleep(500000);
		send_command(&gpio_desc,0x01);         
		send_command(&gpio_desc,0x81);
		for(counter=0;counter<(strlen(quit_msgU));counter++)
			send_character(&gpio_desc,quit_msgU[counter]);
		send_command(&gpio_desc,0xCa);
		for(counter=0;counter<(strlen(quit_msgL));counter++)
			send_character(&gpio_desc,quit_msgL[counter]);
		sleep(1);
				send_command(&gpio_desc,0x01);
		gpio_fd=open("/sys/class/gpio/gpio23_ph16/value",O_RDONLY);
		read(gpio_fd,&value,sizeof(char));
		lseek(gpio_fd,0,SEEK_SET);
		if(value == '1')
		{
			close(gpio_fd);
			send_command(&gpio_desc,0x01);
			printf("inside first while\n");
		ret =	system("linphonecsh generic \"answer\"");
			running=0;
			call_connected=1;
			break;
		}
		close(gpio_fd);
		complete=1;
	}
	while(call_connected)
		{
			printf("inside secod while\n");
		 gpio_fd=open("/sys/class/gpio/gpio23_ph16/value",O_RDONLY);
                read(gpio_fd,&value,sizeof(char));
                lseek(gpio_fd,0,SEEK_SET);
			printf("value inside second while %c\n",value);
		 if(value == '0')
                { 
                        send_command(&gpio_desc,0x01);
                        if(-1 ==  system("linphonecsh generic \"terminate\""))
			perror("terminate command");
                        break;
                } 
			close(gpio_fd);

		}
	return 0;
}
