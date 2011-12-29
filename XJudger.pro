RESOURCES	= artwork/artwork.qrc
HEADERS     = headers/File.h \
			  headers/classes.h \
			  headers/Tree.h \
			  headers/XJudgerMain.h \
			  headers/XJudgerTest.h \
			  headers/JudgerThread.h \
			  headers/XMLReader.h \
			  headers/DataInfo.h \
			  headers/JudgerTreeView.h \
			  headers/PersonInfo.h \
			  headers/JudgerProcess.h \
			  headers/XJudgerView.h \
			  headers/Time.h
FORMS       = XJudgerMain.ui
SOURCES     = XJudgerMain.cpp \
			  XJudgerTest.cpp \
			  JudgerThread.cpp \
			  XMLReader.cpp \
			  DataInfo.cpp \
			  JudgerTreeView.cpp \
			  PersonInfo.cpp \
			  Tree.cpp \
			  JudgerProcess.cpp \
			  XJudgerView.cpp \
			  File.cpp \
			  Time.cpp \
			  main.cpp
QT         += xml
