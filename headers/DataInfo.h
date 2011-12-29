#ifndef DATAINFO_H
#define DATAINFO_H

#include "classes.h"

using namespace std;

class XMLData;

struct TestCaseInfo{
	string Input, Output;
	int MemoryLimit;
	double Score;
	double TimeLimit;
};

struct ProblemInfo{
	string Name, Input, Output, Source;
	QList <TestCaseInfo *> TestCase;
	~ProblemInfo(void);
};

class DataInfo{
	public:
		QList <ProblemInfo *> Problem;
		
		DataInfo(string WorkingDir = "");
		~DataInfo(void);
		int readData(void);
		int writeData(void);
		int getProblemID(string s);
	private:
		QFile *XMLFile;
		XMLReader *DataXML;
		
		int updateXML(void);
};

#endif
