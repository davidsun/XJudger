#include "headers/classes.h"

using namespace std;

int fileCpy(string sor, string des){
	sor = "cp " + dirLinuxFormat(sor) + " " + dirLinuxFormat(des);
	if (system(sor.c_str()) < 0) return -1;
	return 0;
}

int fileMove(string f1, string f2){
	f1 = "mv " + dirLinuxFormat(f1) + " " + dirLinuxFormat(f2);
	if (system(f1.c_str()) < 0) return -1;
	return 0;
}

int fileChk(string f1, string f2){
	#define getNext(F, c) \
		while ((c = fgetc(F)) != EOF) \
			if (c > 31 && c != ' ') break;
	FILE *F1 = fopen(f1.c_str(), "r");
	FILE *F2 = fopen(f2.c_str(), "r");
	if (F1 == 0 || F2 == 0){
		if (F1) fclose(F1);
		if (F2) fclose(F2);
		return 0;
	}
	int c1 = 0, c2 = 0;
	while (c1 != EOF){
		if (c1 != c2){
			fclose(F1);
			fclose(F2);
			return 0;
		}
		getNext(F1, c1);
		getNext(F2, c2);
	}
	if (c2 != EOF){
		fclose(F1);
		fclose(F2);
		return 0;
	}
	fclose(F1);
	fclose(F2);
	return 1;
	#undef getNext
}

FileMatchDescription fileMatch(string f1, string f2){
	#define getNext(F, c) \
		while ((c = fgetc(F)) != EOF) \
			if (c > 31 && c != ' ') break;
	#define showRet() \
		ret.Status = FILE_MATCH_DIFF; \
		ret.Location = len; \
		ret.DiffStr1 = ret.DiffStr2 = ""; \
		for (int i = 0; i < 5; i ++){ \
			if (c1 == EOF) break; \
			ret.DiffStr1 += char(c1); \
			getNext(F1, c1); \
		} \
		if (c1 != EOF) ret.DiffStr1 += "..."; \
		for (int i = 0; i < 5; i ++){ \
			if (c2 == EOF) break; \
			ret.DiffStr2 += char(c2); \
			getNext(F2, c2); \
		} \
		if (c2 != EOF) ret.DiffStr2 += "..."; 
	FileMatchDescription ret;
	ret.Status = FILE_MATCH_YES;
	FILE *F1 = fopen(f1.c_str(), "r");
	FILE *F2 = fopen(f2.c_str(), "r");
	if (F1 == 0 || F2 == 0){
		if (F1) fclose(F1);
		if (F2) fclose(F2);
		return ret;
	}
	int c1 = 0, c2 = 0, len = 0;
	while (c1 != EOF){
		if (c1 != c2){
			showRet();
			fclose(F1);
			fclose(F2);
			return ret;
		}
		len ++;
		getNext(F1, c1);
		getNext(F2, c2);
	}
	if (c2 != EOF) showRet();
	fclose(F1);
	fclose(F2);
	return ret;
	#undef getNext
	#undef showRet
}

int tDir(char *s){
	int len = strlen(s);
	if (len == 0) return 0;
	if (s[len - 1] != '/') s[len - 1] = '/';
	s[len] = 0;
	return 0;
}

string tDir(string dir){
	if (dir.size() == 0) return "./";
	if (dir[dir.size() - 1] != '/') dir += '/';
	return dir;
}

int fileExist(string dir, string f){
	dir = tDir(dir);
	dir += f;
	if (access(dir.c_str(), 4) == 0) return 1;
	else return 0;
}

string getCwd(void){
	size_t size = 16;
	char *buff;
	while (1){
		buff = new(char[size]);
		if (getcwd(buff, size) == buff) break;
		delete(buff);
		size <<= 1;
	}
	string ret = buff;
	delete(buff);
	return tDir(ret);
}
