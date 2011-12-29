#include "headers/classes.h"

#ifndef XMLREADER_CPP
#define XMLREADER_CPP

class Tree;
class TreeItem;

XMLReader::XMLReader(QIODevice *device){
	XMLDev = device;
	XMLTree = new Tree;
	readData();
}

Tree *XMLReader::tree(void){
	return XMLTree;
}

int XMLReader::readData(void){
	QString errStr;
	int errLine, errColumn;
	QDomDocument doc;
	XMLDev -> open(QIODevice::ReadOnly);
	if (!XMLDev -> isOpen()) return -1;
	if (!doc.setContent(XMLDev, 1, &errStr, &errLine, &errColumn)){
		XMLDev -> close();
		return -1;
	}
	QDomElement root = doc.documentElement();
	if (root.tagName() != "JudgerXML"){
		XMLDev -> close();
		return -1;
	}
	QDomNode node = root.firstChild();
	while (!node.isNull()){
		if (node.toElement().tagName() == "entry") getData(node.toElement(), 0);
		node = node.nextSibling();
	}
	XMLDev -> close();
	return 0;
}

int XMLReader::getData(const QDomElement &element, TreeItem *parent){
	TreeItem *item;
	if (parent) item = new TreeItem(*parent);
	else item = new TreeItem(*XMLTree);
	item -> setText(0, element.attribute("name").toAscii().data());
	QDomNode node = element.firstChild();
	while (!node.isNull()){
		if (node.toElement().tagName() == "entry"){
			getData(node.toElement(), item);
		}  else if (node.toElement().tagName() == "info"){
			TreeItem *itemx = new TreeItem(*item);
			itemx -> setText(0, node.toElement().attribute("name").toAscii().data());
			itemx -> setText(1, node.firstChild().toText().data().toAscii().data());
		}
		node = node.nextSibling();
	}
	return 0;
}

int XMLReader::writeData(void){
	QDomDocument doc;
	QDomElement root = doc.createElement("JudgerXML");
	doc.appendChild(root);
	for (int i = 0; i < XMLTree -> childCount(); i ++){
		TreeItem *t = XMLTree -> child(i);
		QDomElement ele;
		if (t -> childCount()){
			ele = doc.createElement("entry");
			putData(doc, ele, t);
		}  else {
			ele = doc.createElement("info");
			ele.appendChild(doc.createTextNode(t -> text(1).c_str()));
		}
		ele.setAttribute("name", t -> text(0).c_str());
		root.appendChild(ele);
	}
	XMLDev -> open(QIODevice::WriteOnly);
	if (!XMLDev -> isOpen()) printf("Cannot open the file, with error: %s\n", XMLDev -> errorString().toAscii().data());
	QTextStream out(XMLDev);
	doc.save(out, 4);
	XMLDev -> close();
	return 0;
}

int XMLReader::putData(QDomDocument &doc, QDomElement &element, TreeItem *parent){
	for (int i = 0; i < parent -> childCount(); i ++){
		TreeItem *p = parent -> child(i);
		QDomElement ele;
		if (p -> childCount()){
			ele = doc.createElement("entry");
			putData(doc, ele, p);
		}  else {
			ele = doc.createElement("info");
			ele.appendChild(doc.createTextNode(p -> text(1).c_str()));
		}
		ele.setAttribute("name", p -> text(0).c_str());
		element.appendChild(ele);
	}
	return 0;
}

int XMLReader::clearTree(void){
	delete(XMLTree);
	XMLTree = new Tree;
	return 0;
}

#endif
