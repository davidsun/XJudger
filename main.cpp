#include <QApplication>

#include "JudgerThread.cpp"
#include "XJudgerTest.cpp"
#include "XJudgerMain.cpp"

int main(int argc, char *argv[]){
	QApplication app(argc, argv);
	QPixmap pixmap(":/Jpegs/Splash.xcf");
	QSplashScreen *splash = new QSplashScreen(pixmap);
	splash -> show();
	splash -> showMessage("Loading ...", Qt::AlignRight, Qt::white);
	XJudgerMain JudgerMain;
	JudgerMain.show();
	delete(splash);
	return app.exec();
}
