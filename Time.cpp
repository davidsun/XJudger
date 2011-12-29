#include "headers/classes.h"

int msleep(int t){
	struct timespec req, rem;
	req.tv_sec = t / 1000;
	req.tv_nsec = t % 1000 * 1000000000;
	return nanosleep(&req, &rem);
}
