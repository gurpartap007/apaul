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
	int flag=0,time,hindi=0,track;
	int hindi_dur,eng_dur;
	int gpio_fd,seek_fd,end_of_playlist_fd;
		system("mpc rm english");
		system("mpc rm hindi");
		system("mpc rm current");
	////////// User Interaction //////////
	printf ("<<<<<<<<<<<<  PLEASE CHOOSE TIME FOR EACH LANGUAGE >>>>>>>>>>>>\n");
	scanf("%d",&time);
	hindi_dur=eng_dur=time;
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
	printf("\n\t\t\t13.haan_di_khushi_ch");
	printf("\n\t\t\t14.ja_ni_ja");
	printf("\n\t\t\t15.dil_de_varke");
	printf("\n\t\t\t16.we_are_one");
	printf("\n\t\t\t17.phool_tujhe_hai");
	printf("\n\t\t\t18.rona_chadta\n");
	scanf("%d",&track);
	system("touch /var/lib/mpd/playlists/current.m3u");
	switch(track)
	{
		case 1:
		printf("inside case 1\n");
		system("echo \"/var/lib/mpd/music/songs/track1.mp3\" >  /var/lib/mpd/playlists/current.m3u");
		break;
		case 2:
		system("echo \"/var/lib/mpd/music/songs/track2.mp3\" >  /var/lib/mpd/playlists/current.m3u");
		break;
		case 3:
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
		break;
		case 11:
		system("echo \"/var/lib/mpd/music/songs/track11.mp3\" >  /var/lib/mpd/playlists/current.m3u");
		break;
		case 12:
		system("echo \"/var/lib/mpd/music/songs/track12.mp3\" >  /var/lib/mpd/playlists/current.m3u");
		break;
		case 13:
		system("echo \"/var/lib/mpd/music/songs/track13.mp3\" >  /var/lib/mpd/playlists/current.m3u");
		break;
		case 14:
		system("echo \"/var/lib/mpd/music/songs/track14.mp3\" >  /var/lib/mpd/playlists/current.m3u");
		break;
		case 15:
		system("echo \"/var/lib/mpd/music/songs/track15.mp3\" >  /var/lib/mpd/playlists/current.m3u");
		break;
		case 16:
		system("echo \"/var/lib/mpd/music/songs/track16.mp3\" >  /var/lib/mpd/playlists/current.m3u");
		break;
		case 17:
		system("echo \"/var/lib/mpd/music/songs/track17.mp3\" >  /var/lib/mpd/playlists/current.m3u");
		break;
		case 18:
		system("echo \"/var/lib/mpd/music/songs/track18.mp3\" >  /var/lib/mpd/playlists/current.m3u");
		break;
		default:
		printf("wrong choice");
		break;
		
}

		system("echo \"/var/lib/mpd/music/songs/silent3.mp3\" >>  /var/lib/mpd/playlists/current.m3u");
	/*##############               HINDI PLAYLIST         #########################*/ 
		printf("hindi playlist\n");	
		system("touch /var/lib/mpd/playlists/hindi.m3u");
//		system("echo \"/var/lib/mpd/music/songs/silence500msec.mp3\" >  /var/lib/mpd/playlists/hindi.m3u");
		system("echo \"/var/lib/mpd/music/hin/welcome.mp3\" >>  /var/lib/mpd/playlists/hindi.m3u");
		system("echo \"/var/lib/mpd/music/hin/agla_station.mp3\" >>  /var/lib/mpd/playlists/hindi.m3u");
		system("echo \"/var/lib/mpd/music/stations/new_delhi.mp3\" >>  /var/lib/mpd/playlists/hindi.m3u");
		system("echo \"/var/lib/mpd/music/hin/hai.mp3\" >>  /var/lib/mpd/playlists/hindi.m3u");
		system("echo \"/var/lib/mpd/music/songs/silent30.mp3\" >>  /var/lib/mpd/playlists/hindi.m3u");
		hindi=1;




	/*##############              ENGLISH PLAYLIST        #########################*/
	
		system("touch /var/lib/mpd/playlists/english.m3u");
		//system("echo \"/var/lib/mpd/music/songs/silence500msec.mp3\" >>  /var/lib/mpd/playlists/english.m3u");
		system("echo \"/var/lib/mpd/music/eng/welcomeE.mp3\" >>  /var/lib/mpd/playlists/english.m3u");
		system("echo \"/var/lib/mpd/music/eng/nextstation.mp3\" >>  /var/lib/mpd/playlists/english.m3u");
		system("echo \"/var/lib/mpd/music/stations/new_delhiE.mp3\" >>  /var/lib/mpd/playlists/english.m3u");
		system("echo \"/var/lib/mpd/music/songs/silent30.mp3\" >>  /var/lib/mpd/playlists/english.m3u");
	
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
				usleep(5000);
			system("mpc play 2");
				usleep(100000);
			system("mpc clear");
			//system("mpc update");
			system("mpc load hindi");
			usleep(10000);
			system("mpc play 1");
			while(hindi_dur)
			{
			printf("Timer value in hindi playlist --> %d\n",hindi_dur);
				-- hindi_dur;
				sleep(1);
			}
			hindi_dur=time;
			
			system("mpc pause");
			system("mpc clear");
			system("mpc update");
			system("mpc load english");
			usleep(10000);
			system("mpc play 1");
			while(eng_dur)
			{
			printf("Timer value in english playlist --> %d\n",eng_dur);
				-- eng_dur;
				sleep(1);
			}
		eng_dur=time;	
			flag = 1;
		}
		if(value == '1' && flag == 1)
		{	
			system("mpc clear");
			system("mpc load current");
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
				usleep(30000);
			system("mpc play 1");
				usleep(3000);
			system(command);
			flag=0;


		}
		close(gpio_fd);

		sleep(0.2);
	}

	return 0;
}
