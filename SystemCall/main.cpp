#include "SystemCall.h"
#include <QtWidgets/QApplication>
#include<ctime>
#include<qmessagebox.h>
#include<qdatetime.h>
void aaa()
{
	for (int i = 0; i < 10; i++)
	{

		int a = rand() % 100;
		int b = 0;
	}
}
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//QString sqWin = "SystemCall";
	//HWND iWin = ::FindWindowW(NULL, sqWin.toStdWString().c_str());
	//if (iWin != nullptr)
	//{
	//	QMessageBox::information(nullptr, "提示", "程序已经在运行", 0);
	//	return 0;
	//}

	SystemCall w;
	QDate date = QDate::currentDate();
	w.setWindowTitle(date.toString("yyyy-MM-dd"));
	w.show();
	return a.exec();
}
