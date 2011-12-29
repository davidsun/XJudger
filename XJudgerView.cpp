#include "headers/classes.h"

XJudgerView::XJudgerView(XJudgerMain *parent){
	Parent = parent;
	resize(800, 600);
	setWindowFlags(Qt::Dialog);
	setWindowIcon(QIcon(":/Icons/XJudgerView.png"));
	ViewInfo = new TreeView(this);	
	ViewInfo -> setEditTriggers(QAbstractItemView::NoEditTriggers);
	ViewInfo -> setColumnCount(2);
	LayoutFrm = new QGridLayout(this);
	LayoutFrm -> addWidget(ViewInfo, 0, 0, 1, 1);

	connect(ViewInfo, SIGNAL(doubleClicked()), this, SLOT(SlotShowCompileInfo()));
}

int XJudgerView::setDir(string s){
	Dir = s;
	return 0;
}

int XJudgerView::setName(string s){
	Name = s;
	return 0;
}

int XJudgerView::showInfo(void){
	setWindowTitle(((string)"Testing Details - " + Name).c_str());
	PersonInfo *info = new PersonInfo(Dir);
	ViewInfo -> clear();
	QStringList HeaderList;
	char strout[100];
	string headerTitle = "Label";
	for (int i = 0; i < 50; i ++) headerTitle += " ";
	HeaderList << headerTitle.c_str() << "Information";
	ViewInfo -> setHeaderLabels(HeaderList);
	ViewInfo -> resizeColumnToContents(0);
	QTreeWidgetItem *item = new QTreeWidgetItem(ViewInfo);
	item -> setData(0, 0, "User Name");
	item -> setData(1, 0, Name.c_str());
	item = new QTreeWidgetItem(ViewInfo);
	item -> setData(0, 0, "Source Directory");
	item -> setData(1, 0, Dir.c_str());
	item = new QTreeWidgetItem(ViewInfo);
	item -> setData(0, 0, "Total Score");
	item -> setData(1, 0, info -> Score);
	item = new QTreeWidgetItem(ViewInfo);
	sprintf(strout, "%.3lf", info -> ACTime);
	item -> setData(0, 0, "Valid Running Time");
	item -> setData(1, 0, strout);
	item = new QTreeWidgetItem(ViewInfo);
	sprintf(strout, "%.3lf", info -> Time);
	item -> setData(0, 0, "Total Running Time");
	item -> setData(1, 0, strout);
	for (unsigned i = 0; i < info -> ProblemInfo.size(); i ++){
		item = new QTreeWidgetItem(ViewInfo);
		item -> setData(0, 0, ("Problem Running Details - " + Parent -> DataConfig -> Problem[i] -> Name).c_str());
		PersonProblemInfo *probInfo = info -> ProblemInfo[i];
		QTreeWidgetItem *itemx = new QTreeWidgetItem(item);
		itemx -> setData(0, 0, "Problem Status");
		if (probInfo -> Status == PROBLEM_INFO_SUCC) itemx -> setData(1, 0, "Compile Succeed");
		else if (probInfo -> Status == PROBLEM_INFO_CE) itemx -> setData(1, 0, "Compile Failed");	
		else if (probInfo -> Status == PROBLEM_INFO_NOFILE) itemx -> setData(1, 0, "Cannot find the Source File");
		else printf("Unknown Status");
		itemx = new QTreeWidgetItem(item);
		itemx -> setData(0, 0, "Total Score");
		itemx -> setData(1, 0, probInfo -> Score);
		itemx = new QTreeWidgetItem(item);
		itemx -> setData(0, 0, "Total Valid Time");
		sprintf(strout, "%.3lf", probInfo -> ACTime);
		itemx -> setData(1, 0, strout);
		itemx = new QTreeWidgetItem(item);
		itemx -> setData(0, 0, "Total Running Time");
		sprintf(strout, "%.3lf", probInfo -> Time);
		itemx -> setData(1, 0, strout);
		itemx = new QTreeWidgetItem(item);
		itemx -> setData(0, 0, "Compile Info");
		if (probInfo -> CompileInfo == "") itemx -> setData(1, 0, "<None>");
		else {
			string s;
			if (probInfo -> CompileInfo.size() > 50) s = probInfo -> CompileInfo.substr(0, 50) + "...";
			else s = probInfo -> CompileInfo;
			itemx -> setData(1, 0, QString::fromUtf8(s.c_str()));
			itemx -> setData(2, 0, QString::fromUtf8(probInfo -> CompileInfo.c_str()));
		}
		if (probInfo -> Status == PROBLEM_INFO_SUCC){
			itemx = new QTreeWidgetItem(item);
			itemx -> setData(0, 0, "Test Case Running Details");
			for (unsigned j = 0; j < probInfo -> CaseInfo.size(); j ++){
				PersonCaseInfo *caseInfo = probInfo -> CaseInfo[j];
				QTreeWidgetItem *itemxx = new QTreeWidgetItem(itemx);
				string stat;
				if (caseInfo -> Status == CASE_INFO_AC) stat = "AC";
				else if (caseInfo -> Status == CASE_INFO_WA) stat = "WA";
				else if (caseInfo -> Status == CASE_INFO_TLE) stat = "TLE";
				else if (caseInfo -> Status == CASE_INFO_RE) stat = "RE";
				else if (caseInfo -> Status == CASE_INFO_NOOUT) stat = "NOOUT";
				else stat = "--";
				sprintf(strout, "Test Case %d (%s)", j + 1, stat.c_str());
				itemxx -> setData(0, 0, strout);
				QTreeWidgetItem *itemxxx = new QTreeWidgetItem(itemxx);
				itemxxx -> setData(0, 0, "Score");
				itemxxx -> setData(1, 0, caseInfo -> Score);
				itemxxx = new QTreeWidgetItem(itemxx);
				itemxxx -> setData(0, 0, "Running Time");
				sprintf(strout, "%.3lf", caseInfo -> Time);
				itemxxx -> setData(1, 0, strout);
				itemxxx = new QTreeWidgetItem(itemxx);
				itemxxx -> setData(0, 0, "Memory Used");
				sprintf(strout, "%d kb", caseInfo -> Memory);
				itemxxx -> setData(1, 0, strout);
				itemxxx = new QTreeWidgetItem(itemxx);
				itemxxx -> setData(0, 0, "Status");
				if (caseInfo -> Status == CASE_INFO_AC) itemxxx -> setData(1, 0, "Right Output");
				else if (caseInfo -> Status == CASE_INFO_WA) itemxxx -> setData(1, 0, "Wrong Answer");
				else if (caseInfo -> Status == CASE_INFO_TLE) itemxxx -> setData(1, 0, "Time Limit Exceeded");
				else if (caseInfo -> Status == CASE_INFO_RE) itemxxx -> setData(1, 0, "Runtime Error");
				else if (caseInfo -> Status == CASE_INFO_NOOUT) itemxxx -> setData(1, 0, "No Ouput");
				else itemxxx -> setData(1, 0, "Unknown Status");
				itemxxx = new QTreeWidgetItem(itemxx);
				itemxxx -> setData(0, 0, "Description");
				if (caseInfo -> Description == "") itemxxx -> setData(1, 0, "<None>");
				else itemxxx -> setData(1, 0, caseInfo -> Description.c_str());
			}
		}
	}
	delete(info);
	return 0;
}

void XJudgerView::SlotShowCompileInfo(void){
	QTreeWidgetItem *item = ViewInfo -> currentItem();
	if (item != NULL && item -> data(0, 0).toString() == "Compile Info" && item -> data(2, 0).toString() != ""){
		QMessageBox::information(this, "Compile Info - Details", item -> data(2, 0).toString());
		/*this -> setModal(0);
		Parent -> TestForm -> setModal(1);
		Parent -> TestForm -> show();
		Parent -> TestForm -> runThread(2, 0);*/
	}
}

string XJudgerView::name(void){
	return Name;
}

string XJudgerView::dir(void){
	return Dir;
}
