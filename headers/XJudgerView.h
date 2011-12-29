#ifndef XJUDGERVIEW_H
#define XJUDGERVIEW_H

#include "classes.h"

using namespace std;

class TreeView;
class XJudgerMain;

class XJudgerView : public QDialog{
	Q_OBJECT
	public:
		TreeView *ViewInfo;
		QGridLayout *LayoutFrm;

		XJudgerView(XJudgerMain *parent = 0);
		int setDir(string);
		int setName(string);
		int showInfo(void);
		string name();
		string dir();
	private slots:
		void SlotShowCompileInfo(void);
	private:
		XJudgerMain *Parent;
		string Name, Dir;
};

#endif
