#ifndef XJUDGERTEST_H
#define XJUDGERTEST_H

#include "classes.h"

class XJudgerTest;
class XJudgerMain;
class JudgerThread;

class XJudgerTest : public QDialog{
	Q_OBJECT
	public:
		QProgressBar *TestProgress;
		QLabel *TestLabel;
		QTextEdit *TestInfo;
		XJudgerMain *Parent;
		QTextCharFormat *ProgressFormat;
		QFont *ProgressFont;
		QGridLayout *LayoutFrm;

		XJudgerTest(XJudgerMain *parent = 0);
		int runThread(int type = 0, int tag = -1);
		int stopAll(void);
	private slots:
		void SlotInsertInfo(QString);
		void SlotSetLabelText(QString);
		void SlotChangeTitle(QString);
		void SlotChangeValue(int);
		void SlotClearInfo(void);
		int closeOpt(void);
	private:
		JudgerThread *Thread;
};

#endif
