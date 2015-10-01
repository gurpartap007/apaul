#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
volatile char value;
int main(int argc,char *argv[])
{	
	int gpio_fd;
while(1)
{
		gpio_fd=open("/sys/class/gpio/gpio22_ph15/value",O_RDONLY);
		read(gpio_fd,&value,sizeof(char));
		lseek(gpio_fd,0,SEEK_SET);
		if(value == '0')
		{
			close(gpio_fd);
			system("linphonecsh dial root@192.168.0.105");
		}
		close(gpio_fd);
}
	return 0;
}
