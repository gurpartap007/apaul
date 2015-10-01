	
/********************************
        HEADER FILES
 ********************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
 
#include "header.h"
 
/* GPIO - EXPORT */
int gpio_export(struct gpio_descriptor_t *gpio_desc)
{
 
    gpio_desc->gpio_fd = open(gpio_desc->gpio_dev, gpio_desc->gpio_flag);
 
    sprintf(gpio_desc->buf, "%d", gpio_desc->gpio_num);
 
    write(gpio_desc->gpio_fd, gpio_desc->buf, strlen(gpio_desc->buf));
    return 0;
}
 
/* GPIO - SET DIRECTION */
int gpio_set_dir(struct gpio_descriptor_t *gpio_desc, unsigned char dir)
{
    int setdir_fd;
 
    sprintf(gpio_desc->buf, "/sys/class/gpio/gpio%d/direction", gpio_desc->gpio_num);
 
    setdir_fd  = open(gpio_desc->buf, gpio_desc->gpio_flag);
 
    if(dir)
        write(setdir_fd, "out", 4);
    else
        write(setdir_fd, "in", 3);
 
    close(gpio_desc->gpio_fd);
    return 0;
 
}
int gpio_set_value(struct gpio_descriptor_t* gpio_desc, unsigned int val)
{
    int setval_fd;
	switch(gpio_desc->gpio_num)
	{
		case 25:
    		sprintf(gpio_desc->buf, "/sys/class/gpio/gpio25_ph18/value",gpio_desc->gpio_num);
		break;
		case 26:
                sprintf(gpio_desc->buf, "/sys/class/gpio/gpio26_ph19/value",gpio_desc->gpio_num);
                break;
		case 27:
                sprintf(gpio_desc->buf, "/sys/class/gpio/gpio27_ph20/value",gpio_desc->gpio_num);
                break;
		case 28:
                sprintf(gpio_desc->buf, "/sys/class/gpio/gpio28_ph21/value",gpio_desc->gpio_num);
                break;
		case 29:
                sprintf(gpio_desc->buf, "/sys/class/gpio/gpio29_ph22/value",gpio_desc->gpio_num);
                break;
		case 30:
                sprintf(gpio_desc->buf, "/sys/class/gpio/gpio30_ph23/value",gpio_desc->gpio_num);
                break;
		default:
		break;
	
	}
    setval_fd = open(gpio_desc->buf, gpio_desc->gpio_flag);
    if (val)
        write(setval_fd, "1", 2);
    else
        write(setval_fd, "0", 2);
 
    close(gpio_desc->gpio_fd);
    return 0;
}
 
 
/* GPIO - CLOSE(fd) */
int gpio_fd_close(struct gpio_descriptor_t *gpio_desc)
{
    close(gpio_desc->gpio_fd);
 
    gpio_desc->gpio_fd = -1;
 
    return 0;
}

void send_command(struct gpio_descriptor_t *gpio_desc, int command_recieved)
{
	union ascii_num command;
	command.command_copy= (command_recieved ) & 0xf0;
	gpio_desc->gpio_num=RS;					// register select = 0
	gpio_set_value(gpio_desc,0);
	gpio_desc->gpio_num=D0;					// D0
	gpio_set_value(gpio_desc,command.decimal_val.d4);
	gpio_desc->gpio_num=D1;					// D1
	gpio_set_value(gpio_desc,command.decimal_val.d5);
	gpio_desc->gpio_num=D2;					// D2
	gpio_set_value(gpio_desc,command.decimal_val.d6);
	gpio_desc->gpio_num=D3;					// D3
	gpio_set_value(gpio_desc,command.decimal_val.d7);
	gpio_desc->gpio_num=EN;					// EN(high)
	gpio_set_value(gpio_desc,1);
	usleep(10000);
	gpio_desc->gpio_num=EN;					// EN(low)
	gpio_set_value(gpio_desc,0);
	gpio_desc->gpio_num=RS;					// register select = 0
	gpio_set_value(gpio_desc,0);
	command.command_copy= (command_recieved << 4) & 0xf0;
	gpio_desc->gpio_num=D0;					// D0
	gpio_set_value(gpio_desc,command.decimal_val.d4);
	gpio_desc->gpio_num=D1;					// D1
	gpio_set_value(gpio_desc,command.decimal_val.d5);
	gpio_desc->gpio_num=D2;					// D2
	gpio_set_value(gpio_desc,command.decimal_val.d6);
	gpio_desc->gpio_num=D3;					// D3
	gpio_set_value(gpio_desc,command.decimal_val.d7);
	gpio_desc->gpio_num=EN;					// EN(high)
	gpio_set_value(gpio_desc,1);
	gpio_desc->gpio_num=EN;					// EN(low)
	gpio_set_value(gpio_desc,0);
	usleep(1000);
	gpio_desc->gpio_num=RS;					// register select = 0
	gpio_set_value(gpio_desc,1);
}



/////////////////// SEND CHARACTER  ///////////////////////////////

void send_character(struct gpio_descriptor_t *gpio_desc, int command_recieved)
{
	union ascii_num command;
	command.command_copy= (command_recieved ) & 0xf0;
	gpio_desc->gpio_num=RS;					// register select = 0
	gpio_set_value(gpio_desc,0);
	gpio_desc->gpio_num=RS;					// register select = 0
	gpio_set_value(gpio_desc,1);
	gpio_desc->gpio_num=D0;					// D0
	gpio_set_value(gpio_desc,command.decimal_val.d4);
	gpio_desc->gpio_num=D1;					// D1
	gpio_set_value(gpio_desc,command.decimal_val.d5);
	gpio_desc->gpio_num=D2;					// D2
	gpio_set_value(gpio_desc,command.decimal_val.d6);
	gpio_desc->gpio_num=D3;					// D3
	gpio_set_value(gpio_desc,command.decimal_val.d7);
	gpio_desc->gpio_num=EN;					// EN(high)
	gpio_set_value(gpio_desc,1);
	usleep(10000);
	gpio_desc->gpio_num=EN;					// EN(low)
	gpio_set_value(gpio_desc,0);
	gpio_desc->gpio_num=RS;					// register select = 0
	gpio_set_value(gpio_desc,0);
	gpio_desc->gpio_num=RS;					// register select = 0
	gpio_set_value(gpio_desc,1);
	command.command_copy= (command_recieved << 4) & 0xf0;
	gpio_desc->gpio_num=D0;					// D0
	gpio_set_value(gpio_desc,command.decimal_val.d4);
	gpio_desc->gpio_num=D1;					// D1
	gpio_set_value(gpio_desc,command.decimal_val.d5);
	gpio_desc->gpio_num=D2;					// D2
	gpio_set_value(gpio_desc,command.decimal_val.d6);
	gpio_desc->gpio_num=D3;					// D3
	gpio_set_value(gpio_desc,command.decimal_val.d7);
	gpio_desc->gpio_num=EN;					// EN(high)
	gpio_set_value(gpio_desc,1);
	usleep(10000);
	gpio_desc->gpio_num=EN;					// EN(low)
	gpio_set_value(gpio_desc,0);
}


