#include "AutoPlay.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AutoPlay w;
	w.show();
	return a.exec();
}
