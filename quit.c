#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include"header.h"
struct gpio_descriptor_t gpio_desc;
void handler(int sig)
{	
	static int counter=0;
	char *quit_msgU="LINPHONE";
	char *quit_msgL="APP QUIT";
	send_command(&gpio_desc,0x01);
	send_command(&gpio_desc,0x82);
	for(counter=0;counter<(strlen(quit_msgU));counter++)
		send_character(&gpio_desc,quit_msgU[counter]);
	send_command(&gpio_desc,0xC6);
	for(counter=0;counter<(strlen(quit_msgL));counter++)
		send_character(&gpio_desc,quit_msgL[counter]);
       usleep(500000);
	send_command(&gpio_desc,0x01);
	(void) signal(SIGINT,SIG_DFL);
}
int main()
{
	gpio_desc.gpio_flag = O_WRONLY;
	(void) signal(2,handler);//1st argument is signal name and 2nd argument is signal handler function
	while(1)
	{
	}
	return 0;
}
