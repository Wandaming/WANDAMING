#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_AutoPlay.h"
#include<QParamTem.h>
class AutoPlay : public QMainWindow
{
	Q_OBJECT

public:
	AutoPlay(QWidget *parent = Q_NULLPTR);
	~AutoPlay();
private:
	Ui::AutoPlayClass ui;
	QParamTem *pQparamTem = nullptr;
};
