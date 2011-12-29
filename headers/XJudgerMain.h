#ifndef XJUDGERMAIN_H
#define XJUDGERMAIN_H

#include "classes.h"

using namespace std;

class XJudgerTest;
class XJudgerMain;
class JudgerThread;
class XMLReader;
class DataInfo;
class TreeView;
class XJudgerView;

class XJudgerMain : public QMainWindow{
	Q_OBJECT
	public:
		QPushButton *MainButtonTest;
		QPushButton *MainButtonRefresh;
		QPushButton *MainButtonTestAll;
		QAction *MainActionExit, *MainActionAbout;
	    QWidget *CentralWidget;
	    TreeView *MainViewScore, *MainViewData;
	    QMenuBar *MenuBar;
	    QMenu *MainMenuFile, *MainMenuHelp;
		QMenu *MenuData, *MenuScore;
		QStatusBar *StatusBar;
		QTabWidget *MainTab;
		XJudgerTest *TestForm;
		XJudgerView *ViewForm;
		QWidget *TabTest, *TabData;
		DataInfo *DataConfig;	
		QGridLayout *LayoutMain, *LayoutTabData, *LayoutTabTest, *LayoutGroupProb, *LayoutGroupData, *LayoutGroupCase;
		QGroupBox *GroupViewData, *GroupViewProb, *GroupViewCase;
		QPlainTextEdit *TextProbName, *TextInput, *TextOutput, *TextSource;
		QLabel *LabelProb, *LabelInput, *LabelOutput, *LabelSource;
		QPlainTextEdit *TextCaseScore, *TextCaseInput, *TextCaseOutput, *TextCaseTL, *TextCaseML;
		QLabel *LabelCaseScore, *LabelCaseInput, *LabelCaseOutput, *LabelCaseTL, *LabelCaseML;
		string CurrentDir;
		int NoTextUpdate;

		XJudgerMain(QMainWindow *parent = 0);
		~XJudgerMain(void);
		int updateDir(void);
		int showData(void);
	private slots:
		int shut(void);
		int insertProblem(void);
		int removeProblem(void);
		int insertTestCase(void);
		int removeTestCase(void);
		int configTestCase(void);
		int updateTestCase(void);
		int updateProblem(void);
		int showProbCase(void);
		int testSelUser(void);
		int testAllUser(void);
		int viewUserInfo(void);
		int scoreRefresh(void);
		int showAbout(void);
		int checkDir(string);
		int getDir(string, int &);
		void closeEvent(QCloseEvent *);
	private:
};

#endif
