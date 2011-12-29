#ifndef JUDGERTREEVIEW_H
#define JUDGERTREEVIEW_H

#include "classes.h"

class TreeView : public QTreeWidget{
	Q_OBJECT
	public:
		QWidget *Parent;
		
		TreeView(QWidget *parent = 0);
		int setMenu(QMenu *);
	signals:
		void leftClicked(void);
		void rightClicked(void);
		void doubleClicked(void);
		void keyPressed(int);
	protected slots:
		void mouseReleaseEvent(QMouseEvent *);
		void mouseDoubleClickEvent(QMouseEvent *);
		void keyPressEvent(QKeyEvent *);
	private:
		QMenu *RightClickMenu;
};

#endif
