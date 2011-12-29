#include "headers/classes.h"

TreeView::TreeView(QWidget *parent){
	RightClickMenu = 0;
	Parent = parent;
}

int TreeView::setMenu(QMenu *menu){
	RightClickMenu = menu;
	return 0;
}

void TreeView::mouseReleaseEvent(QMouseEvent *e){
	QTreeView::mouseReleaseEvent(e);
	if (e -> button() == Qt::LeftButton) emit leftClicked();
	else if (e -> button() == Qt::RightButton){
		emit rightClicked();
		if (RightClickMenu) RightClickMenu -> popup(e -> globalPos());
	}
}

void TreeView::keyPressEvent(QKeyEvent *e){
	QTreeView::keyPressEvent(e);
	emit keyPressed(e -> key());
}

void TreeView::mouseDoubleClickEvent(QMouseEvent *e){
	QTreeView::mouseDoubleClickEvent(e);
	emit doubleClicked();
}
