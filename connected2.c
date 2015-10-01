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
/*	static int counter=0;
	char *quit_msgU="Call ";
	char *quit_msgL="Connected";
	send_command(&gpio_desc,0x01);
	send_command(&gpio_desc,0x80);
	for(counter=0;counter<(strlen(quit_msgU));counter++)
		send_character(&gpio_desc,quit_msgU[counter]);
	for(counter=0;counter<(strlen(quit_msgL));counter++)
		send_character(&gpio_desc,quit_msgL[counter]);*/
	(void) signal(SIGINT,SIG_DFL);
	system("kill -2 `pidof /home/lcd/connected2`");
}
int main()
{
	int flag=1;
	gpio_desc.gpio_flag = O_WRONLY;
//	(void) signal(2,handler);//1st argument is signal name and 2nd argument is signal handler function
	system("kill -2 `pidof /home/lcd/caller`");
	sleep(1);
	   static int counter=0;
        char *quit_msgU="Call "; 
        char *quit_msgL="Connected";
        send_command(&gpio_desc,0x01);
	usleep(1000);
        send_command(&gpio_desc,0x80);
        for(counter=0;counter<(strlen(quit_msgU));counter++)
{
                send_character(&gpio_desc,quit_msgU[counter]);
		usleep(100);
}
        //send_command(&gpio_desc,0xC4);
        for(counter=0;counter<(strlen(quit_msgL));counter++)
{
                send_character(&gpio_desc,quit_msgL[counter]);
}

	return 0;
}
