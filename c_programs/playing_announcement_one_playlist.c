#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
int main()
{	
	volatile char value=1;
	char * position;
	char * seek;
	char * command;
	char * ifsilence;
	unsigned int counter;
	int flag=0,choice,hindi=0,track;
	int gpio_fd,seek_fd,end_of_playlist_fd;
	////////// User Interaction //////////
	printf ("<<<<<<<<<<<<  PLEASE CHOOSE LANGUAGE  >>>>>>>>>>>>");
	printf("\n\t\t\t1.HINDI");
	printf("\n\t\t\t2.ENGLISH\n");
	scanf("%d",&choice);
	printf ("<<<<<<<<<<<<  PLEASE CHOOSE BACKGROUND MUSIC TRACK  >>>>>>>>>>>>");
	printf("\n\t\t\t1.sanwal_rangiye");
	printf("\n\t\t\t2.eid");
	printf("\n\t\t\t3.yaad");
	printf("\n\t\t\t4.tappe");
	printf("\n\t\t\t5.heer");
	printf("\n\t\t\t6.ki_banu_duniya_da");
	printf("\n\t\t\t7.yaari_chandigarh_waliye");
	printf("\n\t\t\t8.addiyan_chuk_chuk");
	printf("\n\t\t\t9.Tyaari_haan_di_a");
	printf("\n\t\t\t10.Haye_mera_dil");
	printf("\n\t\t\t11.gulabi_aankhein");
	printf("\n\t\t\t12.desi_da_drum");
	printf("\n\t\t\t13.haan_di_khushi_ch\n");
	scanf("%d",&track);
	system("mpc rm current");
	system("touch /var/lib/mpd/playlists/current.m3u");
	switch(track)
	{
		case 1:
		system("echo \"/var/lib/mpd/music/songs/track1.mp3\" >  /var/lib/mpd/playlists/current.m3u");
		break;
		case 2:
		system("echo \"/var/lib/mpd/music/songs/track2.mp3\" >  /var/lib/mpd/playlists/current.m3u");
		break;
		case3:
		system("echo \"/var/lib/mpd/music/songs/track3.mp3\" >  /var/lib/mpd/playlists/current.m3u");
		break;
		case 4:
		system("echo \"/var/lib/mpd/music/songs/track4.mp3\" >  /var/lib/mpd/playlists/current.m3u");
		break;
		case 5:
		system("echo \"/var/lib/mpd/music/songs/track5.mp3\" >  /var/lib/mpd/playlists/current.m3u");
		break;
		case 6:
		system("echo \"/var/lib/mpd/music/songs/track6.mp3\" >  /var/lib/mpd/playlists/current.m3u");
		break;
		case 7:
		system("echo \"/var/lib/mpd/music/songs/track7.mp3\" >  /var/lib/mpd/playlists/current.m3u");
		break;
		case 8:
		system("echo \"/var/lib/mpd/music/songs/track8.mp3\" >  /var/lib/mpd/playlists/current.m3u");
		break;
		case 9:
		system("echo \"/var/lib/mpd/music/songs/track9.mp3\" >  /var/lib/mpd/playlists/current.m3u");
		break;
		case 10:
		system("echo \"/var/lib/mpd/music/songs/track10.mp3\" >  /var/lib/mpd/playlists/current.m3u");
		case 11:
		system("echo \"/var/lib/mpd/music/songs/track11.mp3\" >  /var/lib/mpd/playlists/current.m3u");
		break;
		case 12:
		system("echo \"/var/lib/mpd/music/songs/track12.mp3\" >  /var/lib/mpd/playlists/current.m3u");
		break;
		case 13:
		system("echo \"/var/lib/mpd/music/songs/track13.mp3\" >  /var/lib/mpd/playlists/current.m3u");
		break;
		default:
		printf("wrong choice");
		break;
		
	}
	switch(choice)
	{
		case 1:
//		system("echo \"/var/lib/mpd/music/songs/track8.mp3\" >  /var/lib/mpd/playlists/current.m3u");
		system("echo \"/var/lib/mpd/music/songs/silent3.mp3\" >>  /var/lib/mpd/playlists/current.m3u");
		system("echo \"/var/lib/mpd/music/hin/welcome.mp3\" >>  /var/lib/mpd/playlists/current.m3u");
		system("echo \"/var/lib/mpd/music/hin/agla_station.mp3\" >>  /var/lib/mpd/playlists/current.m3u");
		system("echo \"/var/lib/mpd/music/stations/new_delhi.mp3\" >>  /var/lib/mpd/playlists/current.m3u");
		system("echo \"/var/lib/mpd/music/hin/hai.mp3\" >>  /var/lib/mpd/playlists/current.m3u");
		system("echo \"/var/lib/mpd/music/songs/silence.mp3\" >>  /var/lib/mpd/playlists/current.m3u");
		hindi=1;
		system("mpc clear");
		system("mpc update");
		system("mpc load current");
		break;
		case 2:
//		system("echo \"/var/lib/mpd/music/songs/track9.mp3\" >  /var/lib/mpd/playlists/current.m3u");
		system("echo \"/var/lib/mpd/music/songs/silent3.mp3\" >>  /var/lib/mpd/playlists/current.m3u");
		system("echo \"/var/lib/mpd/music/eng/welcomeE.mp3\" >>  /var/lib/mpd/playlists/current.m3u");
		system("echo \"/var/lib/mpd/music/eng/nextstation.mp3\" >>  /var/lib/mpd/playlists/current.m3u");
		system("echo \"/var/lib/mpd/music/stations/new_delhiE.mp3\" >>  /var/lib/mpd/playlists/current.m3u");
		system("echo \"/var/lib/mpd/music/songs/silence.mp3\" >>  /var/lib/mpd/playlists/current.m3u");
		system("mpc clear");
		system("mpc update");
		system("mpc load current");
		break;
		default:
		printf("wrong choice");

	}
	system("mpc clear");
	system("mpc load current");
	system("mpc play 1");
	command = malloc(sizeof(char)*15);
	ifsilence = malloc(sizeof(char)*8);
	position = malloc(sizeof(char) * 5);
	memset(command,'\0',15);
	memset(ifsilence,'\0',8);
	memset(position,'\0',5);
	seek_fd=open("/tmp/seek.txt",O_RDONLY|O_CREAT);
	if(1 > (end_of_playlist_fd=open("/tmp/end",O_CREAT|O_RDONLY)))
		perror("end of file access");
	while(1)
	{
		gpio_fd=open("/sys/class/gpio/gpio22_ph15/value",O_RDONLY);
		read(gpio_fd,&value,sizeof(char));
		lseek(gpio_fd,0,SEEK_SET);
		if(value == '0')
		{
			close(gpio_fd);
			system ("mpc | awk 'NR==2' | awk '{print $3}' | colrm 5 > /tmp/seek.txt");
				usleep(500000);
			//if(!hindi)
			//system("mpc play 5");
			//else	
			//system("mpc play 6");
			//	usleep(1000000);
			system("mpc play 2");
			while(1)
			{
				usleep(300000);
				system("mpc | awk 'NR==1' | awk '{print $1}' > /tmp/end");
				read(end_of_playlist_fd,ifsilence,8);
				lseek(end_of_playlist_fd,0,SEEK_SET);
				printf("end of playlist  is =%s\n",ifsilence);
				if((strncmp(ifsilence,"silence",7))==0)
				
					break;
			}
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
				//system("mpc clear");
			//	system("mpc load current");
				usleep(300000);
			system("mpc play 1");
				usleep(300000);
			system(command);
			flag=0;


		}
		close(gpio_fd);
//		close(seek_fd);
//		close(end_of_playlist_fd);

		sleep(0.2);
	}

	return 0;
}
