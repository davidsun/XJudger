#include "headers/DataInfo.h"

using namespace std;

ProblemInfo::~ProblemInfo(void){
	for (int i = 0; i < TestCase.size(); i ++)
		delete(TestCase[i]);
	TestCase.clear();
}

DataInfo::DataInfo(string WorkingDir){
	WorkingDir = tDir(WorkingDir);
	XMLFile = new QFile((WorkingDir + "dataConfig.xml").c_str());
	DataXML = new XMLReader(XMLFile);
	readData();	
}

DataInfo::~DataInfo(void){
	for (int i = 0; i < Problem.size(); i ++)
		delete(Problem[i]);
	Problem.clear();
	delete(DataXML);
	delete(XMLFile);
}

int DataInfo::readData(void){
	for (int n = 0; n < DataXML -> tree() -> childCount(); n ++){
		TreeItem *t = DataXML -> tree() -> child(n);
		ProblemInfo *q = new ProblemInfo;
		for (int i = 0; i < t -> childCount(); i ++){
			TreeItem *p = t -> child(i);
			if (p -> text(0) == "ProblemName"){
				q -> Name = p -> text(1);
			}  else if (p -> text(0) == "InputName"){
				q -> Input = p -> text(1);
			}  else if (p -> text(0) == "OutputName"){
				q -> Output = p -> text(1);
			}  else if (p -> text(0) == "SourceName"){
				q -> Source = p -> text(1);
			}  else if (p -> text(0) == "TestCases"){
				for (int j = 0; j < p -> childCount(); j ++){
					TestCaseInfo *qx = new TestCaseInfo;
					TreeItem *px = p -> child(j);
					for (int k = 0; k < px -> childCount(); k ++){
						TreeItem *pxx = px -> child(k);
						if (pxx -> text(0) == "InputName"){
							qx -> Input = pxx -> text(1);
						}  else if (pxx -> text(0) == "OutputName"){
							qx -> Output = pxx -> text(1);
						}  else if (pxx -> text(0) == "Score"){
							sscanf(pxx -> text(1).c_str(), "%lf", &qx -> Score);
						}  else if (pxx -> text(0) == "TimeLimit"){
							sscanf(pxx -> text(1).c_str(), "%lf", &qx -> TimeLimit);
						}  else if (pxx -> text(0) == "MemoryLimit"){
							sscanf(pxx -> text(1).c_str(), "%d", &qx -> MemoryLimit);
						}
					}
					if (fileExist("", qx -> Input) && fileExist("", qx -> Output)) q -> TestCase.push_back(qx);
					else delete(qx);
				}
			}
		}
		Problem.push_back(q);
	}
	/*for (int p = 0; p < Problem.size(); p ++){
		ProblemInfo *i = Problem[p];
		printf("name = %s, input = %s, output = %s\n", i -> Name.c_str(), i -> Input.c_str(), i -> Output.c_str());
		for (int px = 0; px < i -> TestCase.size(); px ++){
			TestCaseInfo *j = i -> TestCase[px];
			printf("    Case input = %s, output = %s, timelimit = %.2lf, score = %d\n", j -> Input.c_str(), j -> Output.c_str(), j -> TimeLimit, j -> Score);
		}
	}*/
	return 0;
}

int DataInfo::writeData(void){
	updateXML();
	DataXML -> writeData();
	return 0;
}

int DataInfo::updateXML(void){
	DataXML -> clearTree();
	Tree *t = DataXML -> tree();
	for (int i = 0; i < Problem.size(); i ++){
		TreeItem *pItem = new TreeItem(*t);
		TreeItem *item = new TreeItem(*pItem);
		item -> setText(0, "ProblemName");
		item -> setText(1, Problem[i] -> Name.c_str());
		item = new TreeItem(*pItem);
		item -> setText(0, "InputName");
		item -> setText(1, Problem[i] -> Input.c_str());
		item = new TreeItem(*pItem);
		item -> setText(0, "OutputName");
		item -> setText(1, Problem[i] -> Output.c_str());
		item = new TreeItem(*pItem);
		item -> setText(0, "SourceName");
		item -> setText(1, Problem[i] -> Source.c_str());
		item = new TreeItem(*pItem);
		item -> setText(0, "TestCases");
		char strout[30];
		for (int j = 0; j < Problem[i] -> TestCase.size(); j ++){
			TreeItem *cItem = new TreeItem(*item);
			TreeItem *itemx = new TreeItem(*cItem);
			itemx -> setText(0, "InputName");
			itemx -> setText(1, Problem[i] -> TestCase[j] -> Input.c_str());
			itemx = new TreeItem(*cItem);
			itemx -> setText(0, "OutputName");
			itemx -> setText(1, Problem[i] -> TestCase[j] -> Output.c_str());
			itemx = new TreeItem(*cItem);
			sprintf(strout, "%lf", Problem[i] -> TestCase[j] -> Score);
			itemx -> setText(0, "Score");
			itemx -> setText(1, strout);
			itemx = new TreeItem(*cItem);
			sprintf(strout, "%lf", Problem[i] -> TestCase[j] -> TimeLimit);
			itemx -> setText(0, "TimeLimit");
			itemx -> setText(1, strout);
			itemx = new TreeItem(*cItem);
			sprintf(strout, "%d", Problem[i] -> TestCase[j] -> MemoryLimit);
			itemx -> setText(0, "MemoryLimit");
			itemx -> setText(1, strout);
		}
	}
	return 0;
}

int DataInfo::getProblemID(string s){
	for (int i = 0; i < Problem.size(); i ++)
		if (s == Problem[i] -> Name) return i;
	return -1;
}
