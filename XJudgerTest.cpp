#include "headers/classes.h"

XJudgerTest::XJudgerTest(XJudgerMain *parent){
	//Setting Up Form
	Parent = parent;
	resize(600, 400);
	setWindowFlags(Qt::Dialog);
	setWindowIcon(QIcon(":/Icons/XJudgerTest.png"));
	TestInfo = new QTextEdit(this);
	TestInfo -> setObjectName("TestInfo");
	TestInfo -> setReadOnly(1);
	TestProgress = new QProgressBar(this);
	TestProgress -> setObjectName("TestProgress");
	TestLabel = new QLabel(this);
	TestLabel -> setObjectName("TestLabel");
    TestLabel -> setText("Test Ready ...");
	LayoutFrm = new QGridLayout(this);
	LayoutFrm -> addWidget(TestLabel, 0, 0, 1, 1);
	LayoutFrm -> addWidget(TestProgress, 1, 0, 1, 1);
	LayoutFrm -> addWidget(TestInfo, 2, 0, 1, 1);
	Thread = new JudgerThread(this); 
	ProgressFormat = new QTextCharFormat;
	ProgressFont = new QFont;

	//Connecting Objects
	connect(this, SIGNAL(rejected()), this, SLOT(closeOpt()));
	connect(Thread, SIGNAL(setTitle(QString)), this, SLOT(SlotChangeTitle(QString)));
	connect(Thread, SIGNAL(setProgress(int)), this, SLOT(SlotChangeValue(int)));
	connect(Thread, SIGNAL(insertHTML(QString)), this, SLOT(SlotInsertInfo(QString)));
	connect(Thread, SIGNAL(clearHTML()), this, SLOT(SlotClearInfo()));
	connect(Thread, SIGNAL(setLabelText(QString)), this, SLOT(SlotSetLabelText(QString)));
}

int XJudgerTest::runThread(int type, int tag){
	Thread -> setType(type, tag);
	Thread -> start();
	return 0;
}

void XJudgerTest::SlotChangeValue(int v){
	TestProgress -> setValue(v);
}

void XJudgerTest::SlotInsertInfo(QString s){
	TestInfo -> moveCursor(QTextCursor::EndOfBlock);
	TestInfo -> insertHtml((QString)"<pre>" + s + "</pre>");
	TestInfo -> moveCursor(QTextCursor::EndOfBlock);
}

void XJudgerTest::SlotClearInfo(void){
	TestInfo -> setPlainText("");
}

void XJudgerTest::SlotSetLabelText(QString s){
	TestLabel -> setText(s);
}

void XJudgerTest::SlotChangeTitle(QString s){
	setWindowTitle(s);
}

int XJudgerTest::closeOpt(void){
	if (Parent -> ViewForm -> isVisible()) Parent -> ViewForm -> showInfo();
	return stopAll();
}

int XJudgerTest::stopAll(void){
	Thread -> stopAll();
	Parent -> MainButtonTest -> setEnabled(1);
	Parent -> MainButtonTestAll -> setEnabled(1);
	Parent -> MainButtonRefresh -> setEnabled(1);
	Parent -> MainViewScore -> setSortingEnabled(1);
	Parent -> TabData -> setEnabled(1);
	return 0;
}

