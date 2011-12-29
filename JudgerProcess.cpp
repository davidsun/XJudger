#include "headers/classes.h"

int JudgerProcess::RunningTime, JudgerProcess::TL, JudgerProcess::ProcessID, JudgerProcess::ExitStatus, JudgerProcess::MemUsed;
struct itimerval JudgerProcess::value;
struct timespec JudgerProcess::tReq, JudgerProcess::tRem;
struct timeb JudgerProcess::tNow, JudgerProcess::tNew;
struct sigaction JudgerProcess::act, JudgerProcess::retAct;

JudgerProcess::JudgerProcess(void){
	ExeName = "run.o";
	Dir = "tmp/";
	MemoryLimit = -1;
	TimeLimit = 1.0;
	ProcessID = 0;
}

void JudgerProcess::timeOut(int){
	if (RunningTime < TL) return;
	if (ProcessID) kill(ProcessID, SIGKILL);
}

void JudgerProcess::sigHandler(int, siginfo_t *info, void *){
	ftime(&tNew);
	ExitStatus = info -> si_status;
}

int JudgerProcess::terminate(void){
	if (!ProcessID) return 0;
	MemUsed = max(MemUsed, getMemoryUse(ProcessID));
	if (!kill(ProcessID, SIGKILL)) kill(ProcessID, SIGKILL);
	return 0;
}

RunningStatus JudgerProcess::start(void){
	value.it_value.tv_sec = int(TimeLimit);
	value.it_value.tv_usec = int(TimeLimit * 1000000) % 1000000 + 100000;
	value.it_interval = value.it_value;
	tReq.tv_sec = 0;
	tReq.tv_nsec = 5000000;
	RunningTime = 0;
	MemUsed = 0;
	TL = int(TimeLimit * 50.0);
	if (chdir(Dir.c_str()) < 0) return RunningStatus();
	int pfd1[2], pfd2[2];
	int p1 = pipe(pfd1); 
	if (p1 == -1){
		printf("Pipe Creation Failed\n");
		if (errno == EMFILE) printf("Too many pipes open in CURRENT process\n");
		else printf("Too many pipes open in operating system\n");
	}
	int p2 = pipe(pfd2); 
	if (p2 == -1){
		printf("Pipe Creation Failed\n");
		if (errno == EMFILE) printf("Too many pipes open in CURRENT process\n");
		else printf("Too many pipes open in operating system\n");
	}
	retAct.sa_flags = SA_NOCLDWAIT | SA_RESTART | SA_SIGINFO;
	sigemptyset(&retAct.sa_mask);
	retAct.sa_sigaction = sigHandler;
	sigaction(SIGCHLD, &retAct, NULL);
	ProcessID = fork();
	if (ProcessID == 0){
		if (MemoryLimit > 0){
			struct rlimit rlp;
			rlp.rlim_cur = MemoryLimit << 10;
			rlp.rlim_max = MemoryLimit << 10;
			setrlimit(RLIMIT_AS, &rlp);
		}
		char c;
		close(pfd2[0]);
		if (write(pfd2[1], "c", 1) < 0) return RunningStatus();
		close(pfd2[1]);
		close(pfd1[1]);
		if (read(pfd1[0], &c, 1) < 0) return RunningStatus();
		close(pfd1[0]);
		execl(("./" + ExeName).c_str(), ExeName.c_str(), NULL);
	}  else if (ProcessID < 0){
	}  else {
		RunningTime = 0;
		act.sa_handler = timeOut;	
		sigemptyset(&act.sa_mask);
		act.sa_flags = SA_NOCLDWAIT | SA_RESTART;
		sigaction(SIGALRM, &act, NULL);
		char c;
		close(pfd2[1]);
		if (read(pfd2[0], &c, 1) < 0) return RunningStatus();
		close(pfd2[0]);
		close(pfd1[0]);
		if (write(pfd1[1], "p", 1) < 0) return RunningStatus();
		close(pfd1[1]);
		ftime(&tNow);
		setitimer(ITIMER_REAL, &value, NULL);
		MemUsed = max(MemUsed, getMemoryUse(ProcessID));
		while (!kill(ProcessID, 0)){
			RunningTime ++;
			MemUsed = max(MemUsed, getMemoryUse(ProcessID));
			nanosleep(&tReq, &tRem);
		}
	}
	MemUsed = max(MemUsed, getMemoryUse(ProcessID));
	act.sa_handler = SIG_IGN;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_NOCLDWAIT | SA_RESTART;
	sigaction(SIGALRM, &act, NULL);
	act.sa_handler = SIG_IGN;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_NOCLDWAIT | SA_RESTART;
	sigaction(SIGCHLD, &act, NULL);
	if (chdir("..") < 0) return RunningStatus();
	RunningStatus ret;
	ret.ExitStatus = ExitStatus;
	ret.Time = max(0.0, difftime(tNew.time, tNow.time) * 1000.0 + tNew.millitm - tNow.millitm);
	ret.MemoryUsed = MemUsed;
	return ret;
}

int JudgerProcess::setTimeLimit(double v){
	TimeLimit = v;
	return 0;
}

int JudgerProcess::setMemoryLimit(int v){
	MemoryLimit = v;
	return 0;
}

int JudgerProcess::getMemoryUse(int pid){
	long long size = 0;
	char buf[30];
	snprintf(buf, 30, "/proc/%d/stat", pid);
	FILE *pf;
	if ((pf = fopen(buf, "r")) != 0){
		if (fscanf(pf, "%*d %*s %*c %*d %*d %*d %*d %*d %*u %*u %*u %*u %*u %*u %*u %*d %*d %*d %*d %*u %*u %*d %*u %lld", &size) != 1) size = -1;
		fclose(pf);
	}
	return size * sysconf(_SC_PAGESIZE) / 1024;
}
