#pragma once
#pragma execution_character_set("utf-8")
#include <QtWidgets/QMainWindow>
#include "ui_SystemCall.h"
#include<CdataStruct.h>
#include<Windows.h>
#include<QDialog_setting.h>
#include<Qth_SystemCall.h>
class SystemCall : public QMainWindow
{
	Q_OBJECT

public:
	SystemCall(QWidget *parent = Q_NULLPTR);
	~SystemCall();

private:
	Ui::SystemCallClass ui;
	CdataStruct data;
	QLabel *lab_pic = nullptr;
	QDialog_setting *pQdialog_setting = nullptr;
	Qth_SystemCall pSystemCall;
	int n_ss = 0;
	void IniWindow();
	
	QString m_pathExe="";
	void SetUIState(bool enable);
private slots:
	void on_pB_connectWin_clicked();

	void on_cbB_function_activated(int curIdx);
	
	void on_pB_start_clicked();
	void on_pB_stop_clicked();
	void on_pB_save_clicked();
	void on_pB_set_clicked();

	void on_pB_sendClick_clicked();

	void on_valReg(double, QString,int);
	void on_pos(int, int);
	void on_error(QString);
	void on_times(int);
};
