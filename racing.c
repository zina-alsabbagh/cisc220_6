// Zina Al-Sabbagh 10161380
// Rita Alsattah 10154610

#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int players[5] = {0,0,0,0,0};

void begin(int play) {
	int pass;
	int space;
	for (pass=0;pass<players[play-1];pass++) {
		printf("~");
	}
	printf("|->");
	for (space=40;space>players[play-1];space--) {
		printf(" ");
	}
	printf("# Lane %d #\n", play);
} 

int noWin() {
	int i;
	for(i=0;i<5;i++) {
		if (players[i]==40) {
			return 0;
		}
	}
	return 1;	
}

void* win() { 
	while (noWin()) {
		int l;
		system("clear");
		printf("Welcome to CISC220 Racing Arena. Hit Enter to move forward!\n");
		for(l=1;l<6;l++) {
			begin(l);
		}
		usleep(20*1000);
	}
	int i;
	for(i=0;i<5;i++) {
		int lane = i+1;
		if ((players[i] == 40) && (lane == 1)) {
			printf("You win the race! \n");
		}
		else if (players[i] == 40) {
			printf("Player%d wins he race! \n",lane);
		}
	}
	pthread_exit(NULL);
}

void* player(void *string) {
	while (noWin()) {
		char c = getchar();
		if ( c == '\n') {
			players[0]+= 1;
		}
	}
	pthread_exit(NULL);
}

void* computer(void *string) {
	while (noWin()){
		long lane = (long)string;
		int s=rand()%100;
		int milli=s*10000;
		players[lane]+=1;	
		usleep(milli);
	}
	pthread_exit(NULL);
}

int main() {
	pthread_t threads[6];
	int n;
	long lane;
	n = pthread_create(threads+0,NULL,win,(void *) 0);
	for(lane=1;lane<=5;lane++) {
		if(lane == 1) {
			n=pthread_create(threads+lane, NULL, player,(void *) lane);
		}
		else {
			n=pthread_create(threads+lane, NULL, computer, (void *) lane);
		}
		if (n) {
			printf("Error");
			exit(-1);
		}
	}
	for(lane=0; lane<6; lane++) {
		pthread_join(threads[lane],NULL);
	}
	pthread_exit(NULL);
	return 0;
}