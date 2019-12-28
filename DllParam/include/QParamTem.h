#pragma once

#include <QDialog>
#include "ui_QParamTem.h"
#include "../dllparam_global.h"
#include"CdataStruct.h"

class DLLPARAM_EXPORT QParamTem : public QDialog
{
	Q_OBJECT

public:
	QParamTem(QWidget *parent = Q_NULLPTR);
	~QParamTem();
	void getData(CdataStruct *_data);
private:
	Ui::QParamTem ui;
	void RenewProjTable();
	void RenewRegTable(int _curProj);
	CdataStruct *dataPara = nullptr;
private slots:
	void on_pB_addProj_clicked();
	void on_pB_delProj_clicked();
	void on_pB_save_clicked();
	void on_pB_reg_clicked();
	void on_pB_delReg_clicked();
	void on_pB_moveUp_clicked();
	void on_pB_moveDown_clicked();

};
