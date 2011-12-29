#include "headers/classes.h"

PersonProblemInfo::~PersonProblemInfo(void){
	reset();
}

int PersonProblemInfo::reset(void){
	for (unsigned i = 0; i < CaseInfo.size(); i ++)
		delete(CaseInfo[i]);
	CaseInfo.clear();
	return 0;
}

PersonInfo::PersonInfo(string WorkingDir){
	WorkingDir = tDir(WorkingDir);
	XMLFile = new QFile((WorkingDir + "testInfo.xml").c_str());
	PersonXML = new XMLReader(XMLFile);
	readData();
}

PersonInfo::~PersonInfo(void){
	reset();
	delete(PersonXML);
	delete(XMLFile);
}

int PersonInfo::readData(void){
	for (int i = 0; i < PersonXML -> tree() -> childCount(); i ++){
		PersonProblemInfo *prob = new PersonProblemInfo;
		TreeItem *item0 = PersonXML -> tree() -> child(i);
		for (int j = 0; j < item0 -> childCount(); j ++){
			TreeItem *p = item0 -> child(j);
			if (p -> text(0) == "CompileInfo"){
				prob -> CompileInfo = p -> text(1);
			}  else if (p -> text(0) == "Status"){
				sscanf(p -> text(1).c_str(), "%d", &prob -> Status);
			}  else if (p -> text(0) == "CaseInfo"){
				for (int k = 0; k < p -> childCount(); k ++){
					TreeItem *px = p -> child(k);
					PersonCaseInfo *pCase = new PersonCaseInfo;
					for (int l = 0; l < px -> childCount(); l ++){
						TreeItem *pxx = px -> child(l);
						if (pxx -> text(0) == "Status"){
							sscanf(pxx -> text(1).c_str(), "%d", &pCase -> Status);
						}  else if (pxx -> text(0) == "Description"){
							pCase -> Description = pxx -> text(1);
						}  else if (pxx -> text(0) == "Time"){
							sscanf(pxx -> text(1).c_str(), "%lf", &pCase -> Time);
						}  else if (pxx -> text(0) == "Score"){
							sscanf(pxx -> text(1).c_str(), "%lf", &pCase -> Score);
						}  else if (pxx -> text(0) == "Memory"){
							sscanf(pxx -> text(1).c_str(), "%d", &pCase -> Memory);
						}
					}
					prob -> CaseInfo.push_back(pCase);
				}
			}
		}
		Score += prob -> Score;
		Time += prob -> Time;
		ProblemInfo.push_back(prob);
	}
	updateFromChild();
	return 0;
}

int PersonInfo::writeData(void){
	updateXML();
	PersonXML -> writeData();
	return 0;
}

int PersonInfo::updateXML(void){
	PersonXML -> clearTree();
	Tree *t = PersonXML -> tree();
	char strout[30];
	for (unsigned i = 0; i < ProblemInfo.size(); i ++){
		TreeItem *pItem = new TreeItem(*t);
		TreeItem *item = new TreeItem(*pItem);
		item -> setText(0, "CompileInfo");
		item -> setText(1, ProblemInfo[i] -> CompileInfo.c_str());
		item = new TreeItem(*pItem);
		sprintf(strout, "%d", ProblemInfo[i] -> Status);
		item -> setText(0, "Status");
		item -> setText(1, strout);
		item = new TreeItem(*pItem);
		item -> setText(0, "CaseInfo");
		for (unsigned j = 0; j < ProblemInfo[i] -> CaseInfo.size(); j ++){
			TreeItem *cItem = new TreeItem(*item);
			TreeItem *itemx = new TreeItem(*cItem);
			itemx -> setText(0, "Status");
			sprintf(strout, "%d", ProblemInfo[i] -> CaseInfo[j] -> Status);
			itemx -> setText(1, strout);
			itemx = new TreeItem(*cItem);
			itemx -> setText(0, "Description");
			itemx -> setText(1, ProblemInfo[i] -> CaseInfo[j] -> Description.c_str());
			itemx = new TreeItem(*cItem);
			itemx -> setText(0, "Time");
			sprintf(strout, "%lf", ProblemInfo[i] -> CaseInfo[j] -> Time);
			itemx -> setText(1, strout);
			itemx = new TreeItem(*cItem);
			itemx -> setText(0, "Score");
			sprintf(strout, "%lf", ProblemInfo[i] -> CaseInfo[j] -> Score);
			itemx -> setText(1, strout);
			itemx = new TreeItem(*cItem);
			itemx -> setText(0, "Memory");
			sprintf(strout, "%d", ProblemInfo[i] -> CaseInfo[j] -> Memory);
			itemx -> setText(1, strout);
		}
	}
	return 0;
}

int PersonInfo::reset(void){
	for (unsigned i = 0; i < ProblemInfo.size(); i ++)
		delete(ProblemInfo[i]);
	ProblemInfo.clear();
	return 0;
}

int PersonInfo::updateFromChild(void){
	Time = Score = ACTime = 0.0;
	for (unsigned i = 0; i < ProblemInfo.size(); i ++){
		ProblemInfo[i] -> Time = ProblemInfo[i] -> Score = ProblemInfo[i] -> ACTime = 0.0;
		for (unsigned j = 0; j < ProblemInfo[i] -> CaseInfo.size(); j ++){
			ProblemInfo[i] -> Time += ProblemInfo[i] -> CaseInfo[j] -> Time;
			ProblemInfo[i] -> Score += ProblemInfo[i] -> CaseInfo[j] -> Score;
			if (ProblemInfo[i] -> CaseInfo[j] -> Status == CASE_INFO_AC)
				ProblemInfo[i] -> ACTime += ProblemInfo[i] -> CaseInfo[j] -> Time;
		}
		Time += ProblemInfo[i] -> Time;
		Score += ProblemInfo[i] -> Score;
		ACTime += ProblemInfo[i] -> ACTime;
	}
	return 0;
}
