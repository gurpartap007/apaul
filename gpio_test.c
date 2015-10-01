#include <stdio.h>
 
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
 
#include "header.h"
 
/****************************************        
         MAIN
 *****************************************/
int main(int argc, char **argv, char **envp)
{
    int j=1,g=0;
    char *msg  = "LINPHONE IpPHONE";
    char *msg1 = "192.168.0.115";
    char *msg2 = "CALL CONNECTED";
    struct gpio_descriptor_t gpio_desc;
    gpio_desc.gpio_flag = O_WRONLY;
    printf("\n   *** GPIO TESTING UTILITY ***   \n");
    send_command(&gpio_desc,0x02);
    usleep(2);
    send_command(&gpio_desc,0x28);
    usleep(2);
    send_command(&gpio_desc,0x06);
    usleep(2);
    send_command(&gpio_desc,0x0c);
    usleep(2);
    send_command(&gpio_desc,0x80);
    usleep(2);
    send_command(&gpio_desc,0x01);
        usleep(100);
 
    ///////////////////////////
    for(j=0;j<5;j++)
    {
        for(g=0;g<17;g++)
        {
            send_character(&gpio_desc,msg[g]);
            usleep(40);
 
        }
        usleep(400000);
        send_command(&gpio_desc,1);
        for(g=0;g<13;g++)
        {
            send_character(&gpio_desc,msg1[g]);
            usleep(40);
 
        }
        usleep(800000);
        send_command(&gpio_desc,1);
        usleep(800000);
    }
    for(g=0;g<14;g++)
    {
        send_character(&gpio_desc,msg2[g]);
        usleep(40);
 
    }
    return 0;
}
