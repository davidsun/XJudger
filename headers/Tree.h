#ifndef TREE_H
#define TREE_H

#include "classes.h"

using namespace std;

class Tree;

class TreeItem{
	public:
		TreeItem(void);
		TreeItem(Tree &);
		TreeItem(TreeItem &);
		~TreeItem(void);
		int insertChild(TreeItem *);
		int childCount(void);
		int setText(int, string);
		string text(int);
		TreeItem *child(int);
	private:
		vector <string> Text;
		vector <TreeItem *> Child;
};

class Tree{
	public:
		Tree(void);
		~Tree(void);
		int insertChild(TreeItem *);
		int childCount(void);
		TreeItem *child(int);
	private:
		vector <TreeItem *> Child;
};

#endif
