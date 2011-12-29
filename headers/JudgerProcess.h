#ifndef JUDGEPROCESS_H
#define JUDGEPROCESS_H

#include "classes.h"

struct RunningStatus{
	int MemoryUsed;
	double Time;
	int ExitStatus;
};

class JudgerProcess{
	public:
		JudgerProcess(void);
		int setMemoryLimit(int);
		int setTimeLimit(double);
		int terminate(void);
		int static getMemoryUse(int);
		RunningStatus start(void);
	private:
		string Dir, ExeName;
		int MemoryLimit;
		double TimeLimit;
		static int ProcessID, ExitStatus, RunningTime, TL, MemUsed;
		static struct itimerval value;
		static struct timespec tReq, tRem;
		static struct timeb tNow, tNew;
		static struct sigaction act, retAct;

		void static timeOut(int);
		void static sigHandler(int, siginfo_t *, void *);
};

#endif
