#include "headers/classes.h"

XJudgerMain::XJudgerMain(QMainWindow *parent): QMainWindow(parent){
	//Basic Building
	CurrentDir = getCwd();
	if (objectName().isEmpty()) setObjectName("XJudgerMain");
	setGeometry((QApplication::desktop() -> width() - 800) / 2, (QApplication::desktop() -> height() - 600) / 2, 800, 600);
	QIcon WindowIcon;
	setWindowIcon(QIcon(":/Icons/XJudgerMain.png"));
    MainActionExit = new QAction(this);
    MainActionExit -> setObjectName("MainActionExit");
	MainActionAbout = new QAction(this);
	MainActionAbout -> setObjectName("MainActionAbout");
    CentralWidget = new QWidget(this);
    CentralWidget -> setObjectName("CentralWidget");
    TestForm = new XJudgerTest(this);
	ViewForm = new XJudgerView(this);
	setCentralWidget(CentralWidget);
    MenuBar = new QMenuBar(this);
    MenuBar -> setObjectName("MenuBar");
    MainMenuFile = new QMenu(MenuBar);
    MainMenuFile -> setObjectName("MainMenuFile");
	MainMenuHelp = new QMenu(MenuBar);
	MainMenuHelp -> setObjectName("MainMenuHelp");
    setMenuBar(MenuBar);
    StatusBar = new QStatusBar(this);
    StatusBar -> setObjectName("StatusBar");
    setStatusBar(StatusBar);
    MenuBar -> addAction(MainMenuFile -> menuAction());
    MainMenuFile -> addAction(MainActionExit);
    MenuBar -> addAction(MainMenuHelp -> menuAction());
	MainMenuHelp -> addAction(MainActionAbout);
	MainTab = new QTabWidget(this);
	MainTab -> setObjectName("MainTab");
	DataConfig = new DataInfo(CurrentDir);
	LayoutMain = new QGridLayout(CentralWidget);
	LayoutMain -> setObjectName("LayoutMain");
	LayoutMain -> addWidget(MainTab, 0, 0, 0, 0);
	
	//Building TabData
	TabData = new QWidget;
	TabData -> setObjectName(QString::fromUtf8("TabData"));
	MainTab -> addTab(TabData, QString::fromUtf8("Data"));
	GroupViewProb = new QGroupBox(TabData);
	GroupViewProb -> setObjectName(QString::fromUtf8("GroupViewProb"));
	GroupViewCase = new QGroupBox(TabData);
	GroupViewCase -> setObjectName(QString::fromUtf8("GroupViewCase"));
	GroupViewData = new QGroupBox(TabData);
	GroupViewData -> setObjectName(QString::fromUtf8("GroupViewData"));
	MainViewData = new TreeView(GroupViewData);
	MainViewData -> setObjectName(QString::fromUtf8("MainViewData"));
	MainViewData -> setMaximumWidth(200);

	TextProbName = new QPlainTextEdit(GroupViewProb);
	TextProbName -> setObjectName("TextProbName");
	TextProbName -> setMaximumHeight(30);
	TextProbName -> setTabChangesFocus(1);
	LabelProb = new QLabel(GroupViewProb);
	LabelProb -> setObjectName("LabelProb");
	LabelProb -> setText("Problem Name: ");
	TextInput = new QPlainTextEdit(GroupViewProb);
	TextInput -> setObjectName("TextInput");
	TextInput -> setMaximumHeight(30);
	TextInput -> setTabChangesFocus(1);
	LabelInput = new QLabel(GroupViewProb);
	LabelInput -> setObjectName("LabelInput");
	LabelInput -> setText("Input File Name: ");
	TextOutput = new QPlainTextEdit(GroupViewProb);
	TextOutput -> setObjectName("TextOutput");
	TextOutput -> setMaximumHeight(30);
	TextOutput -> setTabChangesFocus(1);
	LabelOutput = new QLabel(GroupViewProb);
	LabelOutput -> setObjectName("LabelOutput");
	LabelOutput -> setText("Output File Name: ");
	TextSource = new QPlainTextEdit(GroupViewProb);
	TextSource -> setObjectName("TextSource");
	TextSource -> setMaximumHeight(30);
	TextSource -> setTabChangesFocus(1);
	LabelSource = new QLabel(GroupViewProb);
	LabelSource -> setObjectName("LabelSource");
	LabelSource -> setText("Source File Name: ");
	
	LabelCaseInput = new QLabel(GroupViewCase);
	LabelCaseInput -> setObjectName("LabelCaseInput");
	LabelCaseInput -> setText("Input File Name: ");
	TextCaseInput = new QPlainTextEdit(GroupViewCase);
	TextCaseInput -> setObjectName("TextCaseInput");
	TextCaseInput -> setMaximumHeight(30);
	TextCaseInput -> setTabChangesFocus(1);
	LabelCaseOutput = new QLabel(GroupViewCase);
	LabelCaseOutput -> setObjectName("LabelCaseOutput");
	LabelCaseOutput -> setText("Output File Name: ");
	TextCaseOutput = new QPlainTextEdit(GroupViewProb);
	TextCaseOutput -> setObjectName("TextCaseOutput");
	TextCaseOutput -> setMaximumHeight(30);
	TextCaseOutput -> setTabChangesFocus(1);
	LabelCaseScore = new QLabel(GroupViewCase);
	LabelCaseScore -> setObjectName("LabelCaseScore");
	LabelCaseScore -> setText("Score: ");
	TextCaseScore = new QPlainTextEdit(GroupViewCase);
	TextCaseScore -> setObjectName("TextCaseScore");
	TextCaseScore -> setMaximumHeight(30);
	TextCaseScore -> setTabChangesFocus(1);
	LabelCaseTL = new QLabel(GroupViewCase);
	LabelCaseTL -> setObjectName("LabelCaseTL");
	LabelCaseTL -> setText("Time Limit (second): ");
	TextCaseTL = new QPlainTextEdit(GroupViewCase);
	TextCaseTL -> setObjectName("TextCaseTL");
	TextCaseTL -> setMaximumHeight(30);
	TextCaseTL -> setTabChangesFocus(1);
	LabelCaseML = new QLabel(GroupViewCase);
	LabelCaseML -> setObjectName("LabelCaseML");
	LabelCaseML -> setText("Memory Limit (kb): ");
	TextCaseML = new QPlainTextEdit(GroupViewCase);
	TextCaseML -> setObjectName("TextCaseML");
	TextCaseML -> setMaximumHeight(30);
	TextCaseML -> setTabChangesFocus(1);

	LayoutTabData = new QGridLayout(TabData);
	LayoutTabData -> setObjectName("LayoutTabData");
	LayoutTabData -> addWidget(GroupViewData, 0, 0, 10, 1, Qt::AlignLeft);
	LayoutTabData -> addWidget(GroupViewProb, 0, 1, 10, 1, Qt::AlignTop);
	LayoutTabData -> addWidget(GroupViewCase, 0, 1, 10, 1, Qt::AlignTop);
	GroupViewProb -> setVisible(0);
	GroupViewCase -> setVisible(0);
	LayoutGroupProb = new QGridLayout(GroupViewProb);
	LayoutGroupProb -> setObjectName("LayoutGroupProb");
	LayoutGroupProb -> addWidget(TextProbName, 0, 1, 1, 1);
	LayoutGroupProb -> addWidget(LabelProb, 0, 0, 1, 1);
	LayoutGroupProb -> addWidget(TextInput, 1, 1, 1, 1);
	LayoutGroupProb -> addWidget(LabelInput, 1, 0, 1, 1);
	LayoutGroupProb -> addWidget(TextOutput, 2, 1, 1, 1);
	LayoutGroupProb -> addWidget(LabelOutput, 2, 0, 1, 1);
	LayoutGroupProb -> addWidget(TextSource, 3, 1, 1, 1);
	LayoutGroupProb -> addWidget(LabelSource, 3, 0, 1, 1);
	LayoutGroupProb -> setSizeConstraint(QLayout::SetMinAndMaxSize);
	LayoutGroupData = new QGridLayout(GroupViewData);
	LayoutGroupData -> setObjectName("LayoutGroupData");
	LayoutGroupData -> setSizeConstraint(QLayout::SetMinAndMaxSize);
	LayoutGroupData -> addWidget(MainViewData, 0, 0, 1, 1);
	LayoutGroupCase = new QGridLayout(GroupViewCase);
	LayoutGroupCase -> setObjectName("LayoutGroupCase");
	LayoutGroupCase -> addWidget(TextCaseInput, 0, 1, 1, 1);
	LayoutGroupCase -> addWidget(LabelCaseInput, 0, 0, 1, 1);
	LayoutGroupCase -> addWidget(TextCaseOutput, 1, 1, 1, 1);
	LayoutGroupCase -> addWidget(LabelCaseOutput, 1, 0, 1, 1);
	LayoutGroupCase -> addWidget(TextCaseScore, 2, 1, 1, 1);
	LayoutGroupCase -> addWidget(LabelCaseScore, 2, 0, 1, 1);
	LayoutGroupCase -> addWidget(TextCaseTL, 3, 1, 1, 1);
	LayoutGroupCase -> addWidget(LabelCaseTL, 3, 0, 1, 1);
	LayoutGroupCase -> addWidget(TextCaseML, 4, 1, 1, 1);
	LayoutGroupCase -> addWidget(LabelCaseML, 4, 0, 1, 1);
	
	//Building TabTest
	TabTest = new QWidget;
	TabTest -> setObjectName(QString::fromUtf8("TabTest"));
	MainTab -> addTab(TabTest, QString::fromUtf8("Test"));
	MainViewScore = new TreeView(TabTest);
	MainViewScore -> setObjectName(QString::fromUtf8("MainViewScore"));
	MainViewScore -> setSelectionMode(QAbstractItemView::ExtendedSelection);
	MainViewScore -> setRootIsDecorated(0);
	MainViewScore -> setSortingEnabled(1);
	MainButtonTest = new QPushButton(TabTest);
	MainButtonTest -> setObjectName(QString::fromUtf8("MainButtonTest"));
	MainButtonTestAll = new QPushButton(TabTest);
	MainButtonTestAll -> setObjectName(QString::fromUtf8("MainButtonTestAll"));
    MainButtonRefresh = new QPushButton(TabTest);
	MainButtonRefresh -> setObjectName(QString::fromUtf8("MainButtonRefresh"));
	LayoutTabTest = new QGridLayout(TabTest);
	LayoutTabTest -> setObjectName("LayoutTabTest");
	LayoutTabTest -> addWidget(MainViewScore, 0, 0, 1, 4);
	LayoutTabTest -> addWidget(MainButtonTest, 1, 0, 1, 1);
	LayoutTabTest -> addWidget(MainButtonTestAll, 1, 1, 1, 1);
	LayoutTabTest -> addWidget(MainButtonRefresh, 1, 2, 1, 1);
	
	//Building MenuData
	MenuData = new QMenu(this);
	MenuData -> setObjectName("MenuData");
	MainViewData -> setMenu(MenuData);
	QAction *ActProbInsert = MenuData -> addAction("Insert Problem");
	QAction *ActProbRemove = MenuData -> addAction("Remove Problem");
	MenuData -> addSeparator();
	QAction *ActCaseInsert = MenuData -> addAction("Insert Test Case");
	QAction *ActCaseRemove = MenuData -> addAction("Remove Test Case");
	MenuData -> addSeparator();
	QAction *ActConfigCase = MenuData -> addAction("Automatically Configing Test Cases");

	//Set Title
    setWindowTitle(ProjectName " - " MainVersion " - " VersionNumber);
    MainActionExit -> setText("Exit");
	MainActionAbout -> setText("About");
    MainMenuFile -> setTitle("File");
	MainMenuHelp -> setTitle("Help");
    MainButtonTest -> setText("Test");
    MainButtonTestAll -> setText("Test All");
    MainButtonRefresh -> setText("Refresh");
	
	//Connecting Objects
	connect(MainActionExit, SIGNAL(triggered()), this, SLOT(shut()));
	connect(MainActionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));
	connect(ActProbInsert, SIGNAL(triggered()), this, SLOT(insertProblem()));
	connect(ActProbRemove, SIGNAL(triggered()), this, SLOT(removeProblem()));
	connect(ActCaseInsert, SIGNAL(triggered()), this, SLOT(insertTestCase()));
	connect(ActCaseRemove, SIGNAL(triggered()), this, SLOT(removeTestCase()));
	connect(ActConfigCase, SIGNAL(triggered()), this, SLOT(configTestCase()));
	connect(MainButtonTest, SIGNAL(clicked()), this, SLOT(testSelUser()));
	connect(MainButtonTestAll, SIGNAL(clicked()), this, SLOT(testAllUser()));
	connect(MainButtonRefresh, SIGNAL(clicked()), this, SLOT(scoreRefresh()));
	connect(MainViewData, SIGNAL(leftClicked()), this, SLOT(showProbCase()));
	connect(MainViewData, SIGNAL(rightClicked()), this, SLOT(showProbCase()));
	connect(MainViewData, SIGNAL(keyPressed(int)), this, SLOT(showProbCase()));
	connect(MainViewScore, SIGNAL(doubleClicked()), this, SLOT(viewUserInfo()));
	//Connect to Case Change
	connect(TextCaseInput, SIGNAL(textChanged()), this, SLOT(updateTestCase()));
	connect(TextCaseScore, SIGNAL(textChanged()), this, SLOT(updateTestCase()));
	connect(TextCaseOutput, SIGNAL(textChanged()), this, SLOT(updateTestCase()));
	connect(TextCaseTL, SIGNAL(textChanged()), this, SLOT(updateTestCase()));
	connect(TextCaseML, SIGNAL(textChanged()), this, SLOT(updateTestCase()));
	//Connect to Problem Change
	connect(TextInput, SIGNAL(textChanged()), this, SLOT(updateProblem()));
	connect(TextSource, SIGNAL(textChanged()), this, SLOT(updateProblem()));
	connect(TextOutput, SIGNAL(textChanged()), this, SLOT(updateProblem()));
	connect(TextProbName, SIGNAL(textChanged()), this, SLOT(updateProblem()));
	
	//List -- Show Objects
	updateDir();
	showData();
}

XJudgerMain::~XJudgerMain(void){
	shut();
}

int XJudgerMain::checkDir(string dir){
	for (int i = 0; i < DataConfig -> Problem.size(); i ++){
		string name = DataConfig -> Problem[i] -> Source;
		if (fileExist(dir, name + ".pas") || fileExist(dir, name + ".cpp") || fileExist(dir, name + ".c")) return 1;
	}
	return 0;
}

int XJudgerMain::getDir(string dir, int &count){
	struct direct *file = NULL;
	DIR *pdir = opendir(dir.c_str());
	dir = tDir(dir);
	if (pdir){
		while ((file = readdir(pdir)) != NULL){
			if (strcmp(file -> d_name, ".") == 0) continue;
			if (strcmp(file -> d_name, "..") == 0) continue;
			if (checkDir(dir + file -> d_name)){
				QTreeWidgetItem *item;
				if (MainViewScore -> topLevelItemCount() <= count) item = new QTreeWidgetItem(MainViewScore);
				else item = MainViewScore -> topLevelItem(count);
				item -> setData(0, 0, file -> d_name);
				item -> setData(3, 0, (dir + file -> d_name).c_str());
				PersonInfo info(dir + file -> d_name);
				char strout[30];
				snprintf(strout, 30, "%5.0lf", info.Score);
				item -> setData(1, 0, strout);
				snprintf(strout, 30, "%.3lf s", info.ACTime);
				item -> setData(2, 0, strout);
				item -> setIcon(0, QIcon(":/Icons/User.png"));
				count ++;
			}
			getDir(dir + file -> d_name, count);
		}
	}
	closedir(pdir);
	return 0;
}

int XJudgerMain::updateDir(void){
	if (chdir(CurrentDir.c_str()) < 0) return -1;
	DIR *pdir = opendir("src/");
	if (pdir){
		MainViewScore -> setSortingEnabled(0);
		QStringList HeaderList;
		HeaderList << "Name" << "Score" << "Running Time" << "Directory";
		MainViewScore -> setHeaderLabels(HeaderList);
		int count = 0;
		getDir("src/", count);
		while (MainViewScore -> topLevelItemCount() > count)
			delete(MainViewScore -> topLevelItem(count));
		MainViewScore -> setSortingEnabled(1);
	}
	MainViewScore -> setEditTriggers(QAbstractItemView::NoEditTriggers);
	closedir(pdir);
	return 0;
}

int XJudgerMain::showData(void){
	for (int i = 0; i < DataConfig -> Problem.size(); i ++){
		QTreeWidgetItem *item;
		if (i >= MainViewData -> topLevelItemCount()) item = new QTreeWidgetItem(MainViewData);
		else item = MainViewData -> topLevelItem(i);
		item -> setData(0, 0, ((string)"Problem: " + DataConfig -> Problem[i] -> Name).c_str());
		item -> setIcon(0, QIcon(":/Icons/TestCaseExpand.png"));
		for (int j = 0; j < DataConfig -> Problem[i] -> TestCase.size(); j ++){
			QTreeWidgetItem *cItem;
			if (j >= item -> childCount()) cItem = new QTreeWidgetItem(item);
			else cItem = item -> child(j);
			cItem -> setData(0, 0, ((string)"Test Case " + toString(j + 1)).c_str());
			cItem -> setIcon(0, QIcon(":/Icons/TestCase.png"));
		}
		while (DataConfig -> Problem[i] -> TestCase.size() < item -> childCount()) delete(item -> child(DataConfig -> Problem[i] -> TestCase.size()));
	}
	while (DataConfig -> Problem.size() < MainViewData -> topLevelItemCount()) delete(MainViewData -> topLevelItem(DataConfig -> Problem.size()));
	MainViewData -> setHeaderHidden(1);
	MainViewData -> setEditTriggers(QAbstractItemView::NoEditTriggers);
	return 0;
}

int XJudgerMain::showProbCase(void){
	QModelIndex index = MainViewData -> currentIndex();
	if (index.isValid()){
		NoTextUpdate = 1;
		string title = index.data().toString().toAscii().data();
		if (title.substr(0, 9) == "Problem: "){
			title = title.substr(9, title.size() - 9);
			int probID = DataConfig -> getProblemID(title);
			ProblemInfo *prob = DataConfig -> Problem[probID];
			TextProbName -> setPlainText(title.c_str());
			TextSource -> setPlainText(prob -> Source.c_str());
			TextInput -> setPlainText(prob -> Input.c_str());
			TextOutput -> setPlainText(prob -> Output.c_str());
			GroupViewProb -> setVisible(1);
			GroupViewCase -> setVisible(0);
		}  else {
			int id, probID;
			sscanf(title.c_str(), "Test Case %d", &id); id --;
			string progTitle = index.parent().data().toString().toAscii().data();
			progTitle = progTitle.substr(9, progTitle.size() - 9);
			probID = DataConfig -> getProblemID(progTitle);
			TestCaseInfo *tCase = DataConfig -> Problem[probID] -> TestCase[id];
			TextCaseInput -> setPlainText(tCase -> Input.c_str());
			TextCaseOutput -> setPlainText(tCase -> Output.c_str());
			char sOut[30];
			snprintf(sOut, 30, "%lf", tCase -> Score);
			TextCaseScore -> setPlainText(sOut);
			snprintf(sOut, 30, "%lf", tCase -> TimeLimit);
			TextCaseTL -> setPlainText(sOut);
			snprintf(sOut, 30, "%d", tCase -> MemoryLimit);
			TextCaseML -> setPlainText(sOut);
			GroupViewProb -> setVisible(0);
			GroupViewCase -> setVisible(1);
		}
		NoTextUpdate = 0;
	}
	return 0;
}

int XJudgerMain::shut(void){
	DataConfig -> writeData();
	TestForm -> stopAll();
	exit(0);
}

int XJudgerMain::testSelUser(void){
	if (MainViewScore -> currentIndex().isValid()){
		MainButtonTest -> setEnabled(0);
		MainButtonTestAll -> setEnabled(0);
		MainButtonRefresh -> setEnabled(0);
		MainViewScore -> setSortingEnabled(0);
		MainViewScore -> setEnabled(0);
		TabData -> setEnabled(0);
		TestForm -> show();
		TestForm -> runThread();
	}
	return 0;
}

int XJudgerMain::testAllUser(void){
	if (MainViewScore -> model() -> rowCount()){
		MainButtonTest -> setEnabled(0);
		MainButtonTestAll -> setEnabled(0);
		MainButtonRefresh -> setEnabled(0);
		MainViewScore -> setSortingEnabled(0);
		TabData -> setEnabled(0);
		TestForm -> show();
		TestForm -> runThread(1);
	}
	return 0;
}

int XJudgerMain::scoreRefresh(void){
	updateDir();
	return 0;
}

int XJudgerMain::updateTestCase(void){
	QModelIndex index = MainViewData -> currentIndex();
	if (!NoTextUpdate && index.isValid() && GroupViewCase -> isVisible()){
		string title = index.data().toString().toAscii().data();
		int id, probID;
		sscanf(title.c_str(), "Test Case %d", &id); id --;
		string progTitle = index.parent().data().toString().toAscii().data();
		progTitle = progTitle.substr(9, progTitle.size() - 9);
		probID = DataConfig -> getProblemID(progTitle);
		TestCaseInfo *tCase = DataConfig -> Problem[probID] -> TestCase[id];
		tCase -> Input = TextCaseInput -> toPlainText().toAscii().data();
		tCase -> Output = TextCaseOutput -> toPlainText().toAscii().data();
		tCase -> TimeLimit = TextCaseTL -> toPlainText().toDouble();
		tCase -> MemoryLimit = TextCaseML -> toPlainText().toInt();
		tCase -> Score = TextCaseScore -> toPlainText().toDouble();
		showData();
	}
	return 0;
}

int XJudgerMain::updateProblem(void){
	QModelIndex index = MainViewData -> currentIndex();
	if (!NoTextUpdate && index.isValid() && GroupViewProb -> isVisible()){
		string title = index.data().toString().toAscii().data();
		title = title.substr(9, title.size() - 9);
		int probID;
		probID = DataConfig -> getProblemID(title);
		ProblemInfo *prob = DataConfig -> Problem[probID];
		prob -> Input = TextInput -> toPlainText().toAscii().data();
		prob -> Output = TextOutput -> toPlainText().toAscii().data();
		prob -> Source = TextSource -> toPlainText().toAscii().data();
		prob -> Name = TextProbName -> toPlainText().toAscii().data();
		showData();
	}
	return 0;
}

int XJudgerMain::insertProblem(void){
	DataConfig -> Problem.push_back(new ProblemInfo);
	showData();
	MainViewData -> setCurrentItem(MainViewData -> topLevelItem(MainViewData -> topLevelItemCount() - 1));
	showProbCase();
	return 0;
}

int XJudgerMain::removeProblem(void){
	QModelIndex index = MainViewData -> currentIndex();
	if (index.isValid()){
		string title = index.data().toString().toAscii().data();
		if (title.substr(0, 9) == "Problem: ");
		else title = index.parent().data().toString().toAscii().data();
		title = title.substr(9, title.size() - 9);
		int probID = DataConfig -> getProblemID(title);
		DataConfig -> Problem.removeAt(probID);
	}
	showData();
	showProbCase();
	return 0;
}

int XJudgerMain::insertTestCase(void){
	QModelIndex index = MainViewData -> currentIndex();
	if (index.isValid()){
		string title = index.data().toString().toAscii().data();
		if (title.substr(0, 9) == "Problem: ");
		else title = index.parent().data().toString().toAscii().data();
		title = title.substr(9, title.size() - 9);
		int probID = DataConfig -> getProblemID(title);
		DataConfig -> Problem[probID] -> TestCase.push_back(new TestCaseInfo);
		showData();
		MainViewData -> setItemExpanded(MainViewData -> topLevelItem(probID), 1);
		MainViewData -> setCurrentItem(MainViewData -> topLevelItem(probID) -> child(DataConfig -> Problem[probID] -> TestCase.size() - 1));
		showProbCase();
	}
	return 0;
}

int XJudgerMain::removeTestCase(void){
	QTreeWidgetItem *item = MainViewData -> currentItem();
	if (item != NULL){
		string title = item -> data(0, 0).toString().toAscii().data();
		if (title.substr(0, 9) == "Problem: ") return 0;
		else title = item -> parent() -> data(0, 0).toString().toAscii().data();
		title = title.substr(9, title.size() - 9);
		int probID = DataConfig -> getProblemID(title);
		if (probID == -1) return 0;
		DataConfig -> Problem[probID] -> TestCase.removeAt(item -> parent() -> indexOfChild(item));
		showData();
		MainViewData -> setItemExpanded(MainViewData -> topLevelItem(probID), 1);
		MainViewData -> setCurrentItem(MainViewData -> topLevelItem(probID) -> child(DataConfig -> Problem[probID] -> TestCase.size() - 1));
		showProbCase();
	}
	return 0;
}

int XJudgerMain::configTestCase(void){
	if (chdir(CurrentDir.c_str()) < 0) return -1;
	QTreeWidgetItem *item = MainViewData -> currentItem();
	if (item != NULL){
		string title = item -> data(0, 0).toString().toAscii().data();
		if (title.substr(0, 9) == "Problem: ");
		else title = item -> parent() -> data(0, 0).toString().toAscii().data();
		title = title.substr(9, title.size() - 9);
		int probID = DataConfig -> getProblemID(title);
		if (probID == -1) return 0;
		char inputName[50], outputName[50];
		snprintf(inputName, 50, "data/%s/%s*.in", title.c_str(), title.c_str());
		string inputFormat = QInputDialog::getText(this, "Input File", "The Format of Input Files is ", QLineEdit::Normal, inputName).toAscii().data();
		int count = 0;
		for (unsigned i = 0; i < inputFormat.size(); i ++)
			if (inputFormat[i] == '*') count ++;
		if (count != 1){
			if (inputFormat.size())
				QMessageBox::critical(this, "Error", "There should be ONE '*' in the format.");
			return 0;
		}
		snprintf(outputName, 50, "data/%s/%s*.out", title.c_str(), title.c_str());
		string outputFormat = QInputDialog::getText(this, "Output File", "The Format of Output Files is ", QLineEdit::Normal, outputName).toAscii().data();
		count = 0;
		for (unsigned i = 0; i < outputFormat.size(); i ++)
			if (outputFormat[i] == '*') count ++;
		if (count != 1){
			if (outputFormat.size())
				QMessageBox::critical(this, "Error", "There should be ONE '*' in the format.");
			return 0;
		}
		DataConfig -> Problem[probID] -> TestCase.clear();
		for (int i = 0; i < 1000; i ++){
			for (unsigned j = 0; j < inputFormat.size(); j ++){
				if (inputFormat[j] == '*'){
					snprintf(inputName, 50, "%s%d%s", inputFormat.substr(0, j).c_str(), i, inputFormat.substr(j + 1, inputFormat.size() - 1).c_str());
					break;
				}
			}
			for (unsigned j = 0; j < outputFormat.size(); j ++){
				if (outputFormat[j] == '*'){
					snprintf(outputName, 50, "%s%d%s", outputFormat.substr(0, j).c_str(), i, outputFormat.substr(j + 1, outputFormat.size() - 1).c_str());
					break;
				}
			}
			if (fileExist("", inputName) && fileExist("", outputName)){
				TestCaseInfo *tCase = new TestCaseInfo;
				tCase -> Input = inputName;
				tCase -> Output = outputName;
				tCase -> TimeLimit = 1.0;
				DataConfig -> Problem[probID] -> TestCase.push_back(tCase);
			}
		}
		if (DataConfig -> Problem[probID] -> TestCase.size()){
			double score = 100.0 / DataConfig -> Problem[probID] -> TestCase.size();
			for (int i = 0; i < DataConfig -> Problem[probID] -> TestCase.size(); i ++){
				DataConfig -> Problem[probID] -> TestCase[i] -> Score = score;
				DataConfig -> Problem[probID] -> TestCase[i] -> MemoryLimit = 1 << 17;
			}
		}
		showData();
	}
	return 0;
}

int XJudgerMain::viewUserInfo(void){
	if (!TestForm -> isVisible() && MainViewScore -> currentIndex().isValid()){
		QTreeWidgetItem *item = MainViewScore -> topLevelItem(MainViewScore -> currentIndex().row());
		ViewForm -> setModal(1);
		ViewForm -> setName(item -> data(0, 0).toString().toAscii().data());
		ViewForm -> setDir(item -> data(3, 0).toString().toAscii().data());
		ViewForm -> showInfo();
		ViewForm -> show();
	}
	return 0;
}

int XJudgerMain::showAbout(void){
	QMessageBox::about(this, "About", ProjectName "\n  Version: " MainVersion " " VersionNumber "\n              By Sunzheng");
	return 0;
}

void XJudgerMain::closeEvent(QCloseEvent *){
	shut();
}
