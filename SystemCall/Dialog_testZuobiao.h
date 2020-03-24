#pragma once

#include <QDialog>
#include "ui_Dialog_testZuobiao.h"

class Dialog_testZuobiao : public QDialog
{
	Q_OBJECT

public:
	Dialog_testZuobiao(QWidget *parent = Q_NULLPTR);
	~Dialog_testZuobiao();

private:
	Ui::Dialog_testZuobiao ui;
private slots:
	void on_pB_grab_clicked();
	void on_pB_click_clicked();


};
