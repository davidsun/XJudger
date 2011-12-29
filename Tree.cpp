#include "headers/classes.h"

TreeItem::TreeItem(void){
}

TreeItem::TreeItem(Tree &parent){
	parent.insertChild(this);
}

TreeItem::TreeItem(TreeItem &parent){
	parent.insertChild(this);
}

TreeItem::~TreeItem(void){
	for (unsigned i = 0; i < Child.size(); i ++) delete(Child[i]);
	Child.clear();
}

int TreeItem::insertChild(TreeItem *c){
	Child.push_back(c);
	return 0;
}

int TreeItem::childCount(void){
	return Child.size();
}

int TreeItem::setText(int loc, string s){
	if (unsigned(loc) >= Text.size()) Text.resize(loc + 1);
	Text[loc] = s;
	return 0;
}

string TreeItem::text(int loc){
	if (unsigned(loc) >= Text.size()) return "";
	return Text[loc];
}

TreeItem *TreeItem::child(int id){
	return Child[id];
}

Tree::Tree(void){
}

Tree::~Tree(void){
	for (unsigned i = 0; i < Child.size(); i ++) delete(Child[i]);
	Child.clear();
}

int Tree::insertChild(TreeItem *c){
	Child.push_back(c);
	return 0;
}

int Tree::childCount(void){
	return Child.size();
}

TreeItem *Tree::child(int id){
	return Child[id];
}
