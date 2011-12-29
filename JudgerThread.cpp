#include "headers/classes.h"

JudgerThread::JudgerThread(XJudgerTest *parent){
	MainDialog = parent;
}

int JudgerThread::setType(int t, int tag){
	Type = t;
	Tag = tag;
	return 0;
}

string toString(int x){
	string ret = "";
	while (x > 0){
		ret = char(x % 10 + '0') + ret;
		x /= 10;
	}
	if (ret == "") return "0";
	return ret;
}

void JudgerThread::run(void){
	callQuit = 0;
	if (Type == 0){
		TreeView *tView = MainDialog -> Parent -> MainViewScore;
		vector <QTreeWidgetItem *> selItems;
		for (int i = 0; i < tView -> topLevelItemCount(); i ++){
			QTreeWidgetItem *item = tView -> topLevelItem(i);
			if (tView -> isItemSelected(item)) selItems.push_back(item);
		}
		MainDialog -> Parent -> MainViewScore -> setEnabled(1);
		if (tView -> topLevelItemCount()){
			for (unsigned i = 0; i < selItems.size(); i ++){
				if (callQuit) return;
				QTreeWidgetItem *item = selItems[i];
				printf("%s\n", item -> data(0, 0).toString().toAscii().data());
				string user = item -> data(0, 0).toString().toAscii().data();
				string dir = item -> data(3, 0).toString().toAscii().data();
				testDir(user, dir);
				PersonInfo info(dir.c_str());
				char strout[30];
				sprintf(strout, "%.3lf s", info.ACTime);
				item -> setData(2, 0, strout);
				sprintf(strout, "%5.0lf", info.Score);
				item -> setData(1, 0, strout);
			}
		}
	}  else if (Type == 1){
		TreeView *tView = MainDialog -> Parent -> MainViewScore;
		if (tView -> topLevelItemCount()){
			for (int i = 0; i < tView -> topLevelItemCount(); i ++){
				if (callQuit) return;
				QTreeWidgetItem *item = tView -> topLevelItem(i);
				printf("%s\n", item -> data(0, 0).toString().toAscii().data());
				string user = item -> data(0, 0).toString().toAscii().data();
				string dir = item -> data(3, 0).toString().toAscii().data();
				testDir(user, dir);
				PersonInfo info(dir.c_str());
				char strout[30];
				sprintf(strout, "%.3lf s", info.ACTime);
				item -> setData(2, 0, strout);
				sprintf(strout, "%5.0lf", info.Score);
				item -> setData(1, 0, strout);
			}
		}
	}  else if (Type == 2){
		XJudgerView *frm = MainDialog -> Parent -> ViewForm;
		DataInfo *dInfo = MainDialog -> Parent -> DataConfig;
		if (Tag >= 0 && dInfo -> Problem.size() > Tag) testDirProg(Tag, frm -> name(), frm -> dir());
	}
}

int JudgerThread::stopAll(void){
	callQuit = 1;
	pro.terminate();
	exit();
	return 0;
}

string JudgerThread::checkStatus(int status){
	if (status == SIGFPE) return "SIGFPE";
	else if (status == SIGSEGV) return "SIGSEGV";
	else if (status == SIGIOT) return "SIGIOT";
	else return "";
}

PersonProblemInfo *JudgerThread::testDirProg(ProblemInfo *prob, string dir){
	#define printInfo(a) (emit insertHTML(a))
	PersonProblemInfo *ret = new PersonProblemInfo;
	emit setProgress(0);
	printInfo(("<font size = 4><b>Testing Problem " + prob -> Name + " ...</b><br></font>\n").c_str());
	emit setLabelText(StrOut);
	string tmp = dir + prob -> Source;
	int fileExt = 0;
	if (fileExist("", tmp + ".cpp")){
		fileCpy(tmp + ".cpp", "tmp/a.cpp");
		sprintf(StrOut, "    Compiling %s ...", (prob -> Source + ".cpp").c_str());
		printInfo(StrOut);
		fclose(stderr);
		if (freopen("tmp/CompileInfo.txt", "w", stderr) == NULL) return ret;
		if (system("g++ tmp/a.cpp -Wall -g -o tmp/run.o") == -1) msleep(1);
		fclose(stderr);
		if (freopen("/dev/tty", "w", stderr) == NULL) return ret;
		FILE *fin = fopen("tmp/CompileInfo.txt", "r");
		int c;
		while ((c = fgetc(fin)) != EOF) ret -> CompileInfo += char(c);
		fclose(fin);
		fileExt = 1;
	}  else if (fileExist("", tmp + ".pas")){
		fileCpy(tmp + ".pas", "tmp/a.pas");
		sprintf(StrOut, "    Compiling %s ...", (prob -> Source + ".pas").c_str());
		printInfo(StrOut);
		if (chdir((getCwd() + "tmp/").c_str()) < 0) return ret;
		FILE *fpin = popen("fpc a.pas", "r");
		int c;
		while ((c = fgetc(fpin)) != EOF) ret -> CompileInfo += char(c);	
		pclose(fpin);
		if (chdir((getCwd() + "../").c_str()) < 0) return ret;
		if (fileExist("", "tmp/a")) fileMove("tmp/a", "tmp/run.o");
		fileExt = 1;
	}  else if (fileExist("", tmp + ".c")){
		fileCpy(tmp + ".c", "tmp/a.c");
		sprintf(StrOut, "    Compiling %s ...", (prob -> Source + ".c").c_str());
		printInfo(StrOut);
		fclose(stderr);
		if (freopen("tmp/CompileInfo.txt", "w", stderr) == NULL) return ret;
		if (system("gcc tmp/a.c -Wall -g -o tmp/run.o") == -1) msleep(1);
		fclose(stderr);
		if (freopen("/dev/tty", "w", stderr) == NULL) return ret;
		FILE *fin = fopen("tmp/CompileInfo.txt", "r");
		int c;
		while ((c = fgetc(fin)) != EOF) ret -> CompileInfo += char(c);
		fclose(fin);	
		fileExt = 1;
	}
	if (callQuit) return ret;
	msleep(40);
	if (fileExt){
		if (fileExist("", "tmp/run.o")){
			printInfo(" succeed<br>");
			ret -> Status = PROBLEM_INFO_SUCC;
			for (int i = 0; i < prob -> TestCase.size(); i ++){
				PersonCaseInfo *caseInfo = new PersonCaseInfo;
				TestCaseInfo *tCase = prob -> TestCase[i];
				emit setProgress(i * 100 / prob -> TestCase.size());
				fileCpy(tCase -> Input, "tmp/" + prob -> Input);
				chmod(tCase -> Output.c_str(), 0);
				pro.setTimeLimit(tCase -> TimeLimit);
				pro.setMemoryLimit(tCase -> MemoryLimit);
				RunningStatus stat = pro.start();
				chmod(tCase -> Output.c_str(), S_IWUSR | S_IRUSR);
				if (callQuit) return ret;
				int runTime = int(stat.Time);
				caseInfo -> Time = double(runTime) / 1000.0;
				caseInfo -> Memory = stat.MemoryUsed;
				caseInfo -> Score = 0.0;
				caseInfo -> Description = "";
				sprintf(StrOut, "    <font size = 3><b>Running Test Case %d:</b></font><br>        Result = ", i + 1);
				printInfo(StrOut);
				int ExitStatus = stat.ExitStatus;
				if (runTime < int(tCase -> TimeLimit * 1000.0)){ 
					if (checkStatus(ExitStatus) != ""){
						sprintf(StrOut, "<font color = blue><b>Runtime Error (%s)</b></font><br>", checkStatus(ExitStatus).c_str());
						caseInfo -> Status = CASE_INFO_RE;
						caseInfo -> Description = checkStatus(ExitStatus);
						printInfo(StrOut);
					}  else if (fileExist("", "tmp/" + prob -> Output)){
						if (fileChk(tCase -> Output, "tmp/" + prob -> Output)){
							caseInfo -> Status = CASE_INFO_AC;
							caseInfo -> Score = tCase -> Score;
							printInfo("<font color = green><b>Right Output</b></font><br>");
						}  else {
							FileMatchDescription diff = fileMatch(tCase -> Output, "tmp/" + prob -> Output);
							caseInfo -> Status = CASE_INFO_WA;
							sprintf(StrOut, "At Location %d\n"
											"  Standard Output is '%s'\n"
											"  Wrong Output is '%s'", diff.Location, diff.DiffStr1.c_str(), diff.DiffStr2.c_str());
							caseInfo -> Description = StrOut;
							printInfo("<font color = red><b>Wrong Answer</b></font><br>");
						}
					}  else {
						caseInfo -> Status = CASE_INFO_NOOUT;
						printInfo("<font color = olive><b>No Output</b></font><br>");
					}
				}  else {
					caseInfo -> Status = CASE_INFO_TLE;
					printInfo("<font color = red><b>Time Limit Exceeded</b></font><br>");
				}
				sprintf(StrOut, "        Running Time = <b> %d ms</b><br>", runTime);
				printInfo(StrOut);
				sprintf(StrOut, "        Memory Used = <b> %d kb</b><br>", stat.MemoryUsed);
				printInfo(StrOut);
				while (fileExist("", "tmp/" + prob -> Input)){
					if (system(("rm tmp/" + prob -> Input).c_str()) == -1) msleep(20);
					msleep(20);
				}
				while (fileExist("", "tmp/" + prob -> Output)){
					if (system(("rm tmp/" + prob -> Output).c_str()) == -1) msleep(20);
					msleep(20);
				}
				ret -> CaseInfo.push_back(caseInfo);
				msleep(20);
			}
			while (fileExist("", "tmp/run.o")){
				if (system("rm tmp/run.o") == -1) msleep(20);
				msleep(20);
			}
		}  else {
			printInfo(" failed<br>");
			ret -> Status = PROBLEM_INFO_CE;
		}
	}  else {
		printInfo("    Cannnot find the file.<br>");
		ret -> Status = PROBLEM_INFO_NOFILE;
	}
	printInfo("<br>");
	return ret;
	#undef printInfo
}

double JudgerThread::testDir(string user, string dir){
	#define printInfo(a) (emit insertHTML(a))
	#define quitFunc(x){\
		delete(info); \
		if (system("rm -R tmp/") < 0) return x; \
		return x; \
	}
	dir = tDir(dir);
	PersonInfo *info = new PersonInfo(dir);
	info -> reset();
	emit setTitle(((string)"Testing " + user + " ...").c_str());
	emit setProgress(0);
	emit setLabelText("Testing Ready ...");
	emit clearHTML();
	mkdir("tmp/", S_IRWXU);
	for (int tc = 0; tc < MainDialog -> Parent -> DataConfig -> Problem.size(); tc ++){
		ProblemInfo *prob = MainDialog -> Parent -> DataConfig -> Problem[tc];
		sprintf(StrOut, "User %s, Testing Problem %d/%d: %s", user.c_str(), tc + 1, MainDialog -> Parent -> DataConfig -> Problem.size(), prob -> Name.c_str());
		info -> ProblemInfo.push_back(testDirProg(prob, dir));
		if (callQuit) quitFunc(- 1.0);
	}
	emit setProgress(100);
	printInfo("<br><font size = 4><b>Testing Finished.</b></font><br>");
	info -> updateFromChild();
	info -> writeData();
	double ret = info -> Score;
	quitFunc(ret);
	#undef printInfo
	#undef quitFunc
}

double JudgerThread::testDirProg(int tc, string user, string dir){
	#define printInfo(a) (emit insertHTML(a))
	#define quitFunc(x){\
		delete(info); \
		if (system("rm -R tmp/") < 0) return x; \
		return x; \
	}
	dir = tDir(dir);
	PersonInfo *info = new PersonInfo(dir);
	delete(info -> ProblemInfo[Tag]);
	emit setTitle(((string)"Testing " + user + " ...").c_str());
	emit setProgress(0);
	emit setLabelText("Testing Ready ...");
	emit clearHTML();
	mkdir("tmp/", S_IRWXU);
	ProblemInfo *prob = MainDialog -> Parent -> DataConfig -> Problem[tc];
	sprintf(StrOut, "User %s, Testing Problem 1/1: %s", user.c_str(), prob -> Name.c_str());
	info -> ProblemInfo[tc] = testDirProg(prob, dir); 
	if (callQuit) quitFunc(- 1.0);
	emit setProgress(100);
	printInfo("<br><font size = 4><b>Testing Finished.</b></font><br>");
	info -> updateFromChild();
	info -> writeData();
	double ret = info -> Score;
	quitFunc(ret);
	#undef printInfo
	#undef quitFunc
}
