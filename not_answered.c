#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include"header.h"
struct gpio_descriptor_t gpio_desc;
/*void handler(int sig)
{	
	sleep(2);
	static int counter=0;
	char *quit_msgU="Not";
	char *quit_msgL="Answered";
	send_command(&gpio_desc,0x01);
	send_command(&gpio_desc,0x86);
	for(counter=0;counter<(strlen(quit_msgU));counter++)
		send_character(&gpio_desc,quit_msgU[counter]);
	send_command(&gpio_desc,0xC3);
	for(counter=0;counter<(strlen(quit_msgL));counter++)
		send_character(&gpio_desc,quit_msgL[counter]);
	(void) signal(SIGINT,SIG_DFL);
	system("kill -15 `pidof /home/lcd/not_answered")
}*/
int main()
{
	gpio_desc.gpio_flag = O_WRONLY;
//	(void) signal(2,handler);//1st argument is signal name and 2nd argument is signal handler function
        static int counter=0;
        char *quit_msgU="Not";
        char *quit_msgL="Answered";
	system("kill -2 `pidof /home/lcd/caller`");
	sleep(2);
        send_command(&gpio_desc,0x01);
        send_command(&gpio_desc,0x86);
        for(counter=0;counter<(strlen(quit_msgU));counter++)
                send_character(&gpio_desc,quit_msgU[counter]);
        send_command(&gpio_desc,0xC3);
        for(counter=0;counter<(strlen(quit_msgL));counter++)
                send_character(&gpio_desc,quit_msgL[counter]);
	sleep(3);
        send_command(&gpio_desc,0x01);
	return 0;
}
