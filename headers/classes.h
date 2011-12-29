#ifndef CLASSES_H
#define CLASSES_H

#include <QtGui>
#include <QtXml>
#include <QLayout>
#include <QThread>
#include <QPushButton>
#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QListView>
#include <QTableView>
#include <QTreeView>
#include <QMenu>
#include <QMainWindow>
#include <QMenuBar>
#include <QStatusBar>
#include <QProgressBar>
#include <QTabWidget>
#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QPlainTextEdit>

#include <string>

#include <errno.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <sys/resource.h>
#include <sys/vlimit.h>

#include "Tree.h"
#include "Time.h"
#include "XMLReader.h"
#include "XJudgerView.h"
#include "XJudgerMain.h"
#include "JudgerProcess.h"
#include "JudgerThread.h"
#include "XJudgerTest.h"
#include "DataInfo.h"
#include "JudgerTreeView.h"
#include "PersonInfo.h"
#include "File.h"

#define ProjectName "XJudger"
#define MainVersion "Alpha"
#define VersionNumber "0.95.30"

class XJudgerTest;
class XJudgerMain;
class JudgerThread;
class XMLReader;
class DataInfo;
class TreeView;
class PersonInfo;
class Tree;
class XJudgerView;
class JudgerProcess;

#endif
