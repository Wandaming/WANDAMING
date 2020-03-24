#include "SystemCall.h"
#include"QDateTime"
#include"qmessagebox.h"
#include"arithClass.h"
#include<QWinControl.h>
#include<thread>
#include<atomic>

#include<mmsystem.h>
#pragma comment(lib, "winmm.lib")

std::atomic_bool g_isStop=true;
SystemCall::SystemCall(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//获取本窗口句柄

	m_pathExe = QCoreApplication::applicationDirPath()/*.toLocal8Bit().toStdString()*/;
	connect(&pSystemCall, SIGNAL(sig_valReg(double, QString,int)), this, SLOT(on_valReg(double, QString,int)), Qt::QueuedConnection);
	connect(&pSystemCall, SIGNAL(sig_pos(int, int)), this, SLOT(on_pos(int, int)), Qt::QueuedConnection);
	connect(&pSystemCall, SIGNAL(sig_error(QString)), this, SLOT(on_error(QString)), Qt::QueuedConnection);
	connect(&pSystemCall, SIGNAL(sig_time(int)), this, SLOT(on_times(int)), Qt::QueuedConnection);
	IniWindow();
}
SystemCall::~SystemCall()
{
}

void SystemCall::IniWindow()
{

	if (!data.DataRead(m_pathExe.toLocal8Bit().toStdString()))
	{
		QDateTime time = QDateTime::currentDateTime();
		QString ss = time.toString("yyyy_mm_dd hh:mm:ss.zzz ") + tr("获取数据失败");
		QMessageBox::information(this, tr("提示"), tr("获取数据失败"), 0);
	}
	else
	{
		ui.lE_winName->setText(QString::fromLocal8Bit(data.winName.data()));
		QStringList qlist;
		for (int i=0;i< data.listProj.size();i++)
		{
			qlist <<QString::fromLocal8Bit(data.listProj.at(i).name.data());
		}
		ui.cbB_function->addItems(qlist);
		if (data.curProj >= 0 &&data.curProj < data.listProj.size())
		{
			ui.cbB_function->setCurrentIndex(data.curProj);
		}
		pSystemCall.getData(&data);
	}

	
}

void SystemCall::SetUIState(bool enable)
{
	ui.pB_set->setEnabled(enable);
	ui.pB_save->setEnabled(enable);
	ui.cbB_function->setEnabled(enable);
	ui.lE_winName->setEnabled(enable);
}


void SystemCall::on_pB_connectWin_clicked()
{
	
	QString a = QString::fromLocal8Bit(data.winName.data());
	HWND pWnd = ::FindWindowW(NULL, a.toStdWString().c_str());
	if (pWnd == NULL)
	{
		QMessageBox::warning(this, tr("提示"), tr("获取窗口失败"),
			tr("确定"), tr("取消"), tr("退出"), 2);
	}
	else
	{
		QMessageBox::warning(this, tr("提示"), tr("获取窗口成功"),
			tr("确定"), tr("取消"), tr("退出"), 2);
	}
}
void SystemCall::on_pB_save_clicked()
{
	QString winName = ui.lE_winName->text();
	data.winName = winName.toLocal8Bit().toStdString();
	data.curProj = ui.cbB_function->currentIndex();

	if (data.DataWrite(m_pathExe.toLocal8Bit().toStdString()))
	{
		QMessageBox::information(this, tr("提示"), tr("保存数据成功"), 0);
		ui.lE_winName->setText(QString::fromLocal8Bit(data.winName.data()));
	}
	else
	{
		QDateTime time = QDateTime::currentDateTime();
		QString ss = time.toString("yyyy_mm_dd hh:mm:ss.zzz ") + tr("保存数据失败");
		QMessageBox::information(this, tr("提示"), tr("保存数据失败"), 0);
		ui.lE_winName->setText(QString::fromLocal8Bit(data.winName.data()));
	}
}


void SystemCall::on_pB_set_clicked()
{
	if (pQdialog_setting != nullptr)
		return;
	pQdialog_setting = new QDialog_setting(&data, this);
	if (pQdialog_setting->exec() == QDialog::Accepted)
	{

	}
	//刷新ckb
	QStringList listproj;
	for (int i = 0; i < data.listProj.size(); i++)
	{
		listproj <<QString::fromLocal8Bit(data.listProj.at(i).name.data());
	}
	ui.cbB_function->clear();
	ui.cbB_function->addItems(listproj);
	ui.cbB_function->setCurrentIndex(data.curProj);
	pQdialog_setting->deleteLater();
	pQdialog_setting = nullptr;
}

void SystemCall::on_pB_sendClick_clicked()
{
	int sendX = ui.lE_x->text().toInt();
	int sendY = ui.lE_y->text().toInt();
	QString name = QString::fromLocal8Bit(data.winName.data());
	HWND win = QWinControl::GetWinHWND(name);
	if (win != nullptr)
	{
		QWinControl::SendWinLClick(win, sendX, sendY);
	}
	else
	{
		QMessageBox::information(this, tr("提示"), tr("窗口句柄为空"), 0);
	}
}

void SystemCall::on_valReg(double val, QString name,int type)
{
	ui.lE_val->setText(QString::number(val));
	QString text;
	if (type == 0)
	{
		text = name + tr("_检测");
	}
	else if (type==2)
	{
		text = name + tr("_校验");
	}
	ui.lE_curReg->setText(text);
	QCoreApplication::processEvents(QEventLoop::AllEvents, 10);
}

void SystemCall::on_pos(int x, int y)
{
	ui.lE_x->setText(QString::number(x));
	ui.lE_y->setText(QString::number(y));
	QCoreApplication::processEvents(QEventLoop::AllEvents, 10);
}

void SystemCall::on_error(QString err)
{
	QMessageBox::information(this, tr("提示"), err, 0);
	PlaySound(NULL, NULL, SND_PURGE);
}

void SystemCall::on_times(int _time)
{
	ui.lE_times->setText(QString::number(_time));
	QCoreApplication::processEvents(QEventLoop::AllEvents, 10);

}

void SystemCall::on_cbB_function_activated(int curIdx)
{
	//data.curProj = curIdx;
}

void SystemCall::on_pB_start_clicked()
{
	//先采集一张图片，然后进行算法匹配，结果为真的时候，则发送点击信号
	QString name = QString::fromLocal8Bit(data.winName.data());
	HWND win = QWinControl::GetWinHWND(name);
	if (win == nullptr)
	{
		QMessageBox::information(this, tr("提示"), tr("获取窗口句柄失败"), 0);
		return;
	}

	g_isStop = false;	
	ui.pB_start->setStyleSheet("background-color: rgb(100, 100, 100);");
	SetUIState(false);

	data.count = 0;
	std::thread task01(&Qth_SystemCall::processPic, &pSystemCall, win);
	task01.detach();
}

void SystemCall::on_pB_stop_clicked()
{
	ui.pB_start->setStyleSheet("");
	g_isStop = true;
	SetUIState(true);
}
