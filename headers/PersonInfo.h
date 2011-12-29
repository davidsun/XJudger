#ifndef PERSONINFO_H
#define PERSONINFO_H

#include "classes.h"

using namespace std;

class XMLData;

//PersonCaseInfo.Status
int const CASE_INFO_AC = 0;
int const CASE_INFO_WA = 1;
int const CASE_INFO_TLE = 2;
int const CASE_INFO_RE = 3;
int const CASE_INFO_NOOUT = 4;
//PersonProblemInfo.Status
int const PROBLEM_INFO_SUCC = 0;
int const PROBLEM_INFO_CE = 1;
int const PROBLEM_INFO_NOFILE = 2;

struct PersonCaseInfo{
	int Status, Memory;
	string Description;
	double Time, Score;
};

struct PersonProblemInfo{
	int Status;
	string CompileInfo;
	double ACTime, Time, Score;
	vector <PersonCaseInfo *> CaseInfo;
	
	~PersonProblemInfo(void);
	int reset(void);
};

class PersonInfo{
	public:
		double ACTime, Time, Score;
		vector <PersonProblemInfo *> ProblemInfo;
		PersonInfo(string WorkingDir);
		~PersonInfo(void);

		int readData(void);
		int writeData(void);
		int reset(void);
		int updateFromChild(void);
	private:
		QFile *XMLFile;
		XMLReader *PersonXML;

		int updateXML(void);
};

#endif
