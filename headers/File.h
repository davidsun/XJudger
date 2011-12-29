#ifndef FILE_H
#define FILE_H

#include "classes.h"

#define dirLinuxFormat(dir) ((string)"'" + dir + "'")

int const FILE_MATCH_YES = 0;
int const FILE_MATCH_DIFF = 1;

struct FileMatchDescription{
	int Status, Location;
	string DiffStr1, DiffStr2;
};

int fileCpy(string, string);
int fileMove(string, string);
int fileChk(string, string);
int fileExist(string, string);
int tDir(char *);
string getCwd(void);
string tDir(string);
FileMatchDescription fileMatch(string, string);

#endif
