#ifndef XMLREADER_H
#define XMLREADER_H

#include "classes.h"

class XMLReader{
	public:
		XMLReader(QIODevice *);
		Tree *tree(void);
		
		int readData(void);
		int writeData(void);
		int clearTree(void);
	private:
		QIODevice *XMLDev;
		Tree *XMLTree;
		
		int getData(const QDomElement &, TreeItem *);
		int putData(QDomDocument &, QDomElement &, TreeItem *);
};

#endif

