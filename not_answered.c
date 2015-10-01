#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include"header.h"
struct gpio_descriptor_t gpio_desc;
int main()
{
	gpio_desc.gpio_flag = O_WRONLY;
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
