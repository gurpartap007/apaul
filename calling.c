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
void handler(int sig)
{	

	send_command(&gpio_desc,0x01);
	(void) signal(SIGINT,SIG_DFL);
	system("kill -2 `pidof /home/lcd/calling`");
}
int main(int argc,char *argv[])
{
	gpio_desc.gpio_flag = O_WRONLY;
	hostname = malloc(20);
	ip =malloc(strlen(argv[2]));
	hostname = (char *)argv[1];
	ip =(char *)argv[2];
	static int counter=0;
	printf("hostname = %s\n",hostname);
	printf("Ip = %s\n",ip);
	char *quit_msgU="Dialling";
	char *quit_msgL="IP";
	//char value;
	int flag=1;
	//int gpio_fd;
	while(1)
	{	
		if(flag==2)
		{
			printf("Inside If\n");
			break;
		}	
		send_command(&gpio_desc,0x01);
		send_command(&gpio_desc,0x82);
		for(counter=0;counter<(strlen(quit_msgU));counter++)
			send_character(&gpio_desc,quit_msgU[counter]);
		send_command(&gpio_desc,0x8b);
		for(counter=0;counter<(strlen(quit_msgL));counter++)
			send_character(&gpio_desc,quit_msgL[counter]);
		usleep(500000);
		//send_command(&gpio_desc,0x84);
		//for(counter=0;counter<(strlen(hostname));counter++)
			//send_character(&gpio_desc,hostname[counter]);
		send_command(&gpio_desc,0xC1);
		for(counter=0;counter<(strlen(ip));counter++)
			send_character(&gpio_desc,ip[counter]);
		sleep(1);
		flag++;
		//send_command(&gpio_desc,0x01);
	}
/*	gpio_fd=open("/sys/class/gpio/gpio64/value",O_RDONLY);
		while(1)
		{
		read(gpio_fd,&value,sizeof(char));	
		lseek(gpio_fd,0,SEEK_SET);
		if(value == '1')
			{
			system("linphonecsh generic \"answer\"");
			break;
			}
		}*/
			
	return 0;
}
