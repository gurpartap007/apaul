#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
int main()
{	
	volatile char value=1;
	char *position;
	char * seek;
	char * command;
	unsigned int counter;
	int flag=0;
	int gpio_fd,seek_fd;
	system("mpc clear");
	system("mpc load songs");
	system("mpc play 8");
	command = malloc(sizeof(char)*15);
	position = malloc(sizeof(char) * 5);
	memset(command,'\0',15);
	memset(position,'\0',5);
	seek_fd=open("/tmp/seek.txt",O_RDONLY);
	while(1)
	{
		gpio_fd=open("/sys/class/gpio/gpio22_ph15/value",O_RDONLY);
		read(gpio_fd,&value,sizeof(char));
		lseek(gpio_fd,0,SEEK_SET);
		if(value == '0')
		{
			close(gpio_fd);
			system ("mpc | awk 'NR==2' | awk '{print $3}' | colrm 5 > /tmp/seek.txt");

			system("mpc pause");
			system("mpc clear"); 
			system("mpc load hindi");
			system("mpc play 19");
			usleep(4000000);
			system("mpc pause");
			system("mpc play 1");
			usleep (1000000);
			system("mpc clear");
			system ("mpc load stations");
			system("mpc play 1");
			usleep (1200000);
			system("mpc clear");
			system("mpc load hindi");
			system ("mpc play 4");
			usleep (700000);
			system ("mpc pause");
			flag = 1;
		}
		if(value == '1' && flag == 1)
		{
			printf("seek_fd = %d\n",seek_fd);
			read(seek_fd,position,5);
			lseek(seek_fd,0,SEEK_SET);
			printf("position read is = %s\n",position);
			seek = malloc(sizeof(char)*5);
			memset(seek,'\0',5);
			sprintf(command,"mpc seek 00:%s",position);
			printf(" total command is = %s\n",command);
			system("mpc clear");
			system("mpc load songs");
			system("mpc play 8");
			system(command);
			flag=0;


		}
		close(gpio_fd);
		sleep(0.5);
	}

	return 0;
}
