#include <cstdio>
#include <linux/input.h>
#include <fcntl.h>
#include <sys/time.h>
#include <unistd.h>
#include <iostream>
using namespace std;



void simulate_mouse(int fd,int rel_x,int rel_y) {
	struct input_event event;
	gettimeofday(&event.time,0);

	// relative displacement of x
	event.type = EV_REL;
	event.value = rel_x;
	event.code = REL_X;

	write(fd,&event,sizeof(event));

	// relative displacement of y
	event.type = EV_REL;
	event.value = rel_y;
	event.code = REL_Y;

	write(fd,&event,sizeof(event));

	// syn
	event.type = EV_REL;
	event.value = 0;
	event.code = SYN_REPORT;
	write(fd,&event,sizeof(event));
}


void simulate_key(int fd,int kval) {
	struct input_event event;
	gettimeofday(&event.time,0);

	// press kval
	event.type = EV_KEY;
	event.value = 1;
	event.code = kval;
	write(fd,&event,sizeof(event));

	//syn
	event.type = EV_SYN;
	event.value = 0;
	event.code = SYN_REPORT;
	write(fd,&event,sizeof(event));


	//memset(&event,0,sizeof(event));
	gettimeofday(&event.time,0);


	// release kval
	event.type = EV_KEY;
	event.value = 0;
	event.code = kval;
	write(fd,&event,sizeof(event));

	//syn
	event.type = EV_SYN;
	event.value = 0;
	event.code = SYN_REPORT;
	write(fd,&event,sizeof(event));
}

int main(int argc,char**argv) {
	int fd_mouse = -1;
	int fd_kbd = -1;
	int fd_mice = -1;
	int i = 0;
	fd_mouse = open("/dev/input/event6",O_RDWR,O_SYNC);
	fd_mice = open("/dev/input/mice",O_RDONLY);
	fd_kbd = open("/dev/input/event4",O_RDWR,O_SYNC);

	if (fd_mouse <= 0 ) {
		cout << "can not open mouse input file" << endl;
		return -1;
	}
	if (fd_mice <= 0 ) {
		cout << "can not open mice file" << endl;
		return -1;
	}
	if (fd_kbd <= 0 ) {
		cout << "can not open keyboard input file" << endl;
		return -1;
	}

	int position_x = 0.0;
	int position_y = 0.0;
	fd_set readfs;
	int retval;
	char buf[6];
	struct timeval tv;

	

	for (i=0;i<20;i++) {
	//while (true) {
		//sleep(0.3);
	//}
		//simulate_key(fd_kbd,KEY_A);
		read(fd_mice,buf,6);
		position_x += buf[1];
		position_y += buf[2];
		cout << position_x << "," << position_y << endl;
		//simulate_mouse(fd_mouse,2,2);
		//simulate_key(fd_mouse,BTN_LEFT);
		//usleep(0.1e6);
	}

	close(fd_mouse);
	close(fd_mice);
	close(fd_kbd);
}








