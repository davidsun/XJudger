#ifndef JUDGERTHREAD_H
#define JUDGERTHREAD_H

#include <QThread>
#include <QProcess>
#include <string>

#include "classes.h"

using namespace std;

class XJudgerTest;
class XJudgerMain;
class JudgerThread;
struct PersonProblemInfo;
struct ProblemInfo;

class JudgerThread : public QThread{
	Q_OBJECT
	public:
		JudgerThread(XJudgerTest *parent = 0);
		void run(void);
		int stopAll(void);
		int setType(int, int tag = -1);
	signals:
		void setProgress(int);
		void clearHTML(void);
		void setTitle(QString);
		void insertHTML(QString);
		void setLabelText(QString);
	private:
		int Type, Tag, callQuit;
		char StrOut[200];
		XJudgerTest *MainDialog;
		
		JudgerProcess pro;
		double testDir(string, string);
		double testDirProg(int, string, string);
		PersonProblemInfo *testDirProg(ProblemInfo *, string);
		string checkStatus(int);
};

#endif
