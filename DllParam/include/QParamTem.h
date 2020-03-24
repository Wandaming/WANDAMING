#pragma once
#pragma execution_character_set("utf-8")
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
signals:
	void sig_projClicked(int itemId);
	void sig_regClicked(int curProj, int curReg);
	void sig_pbSetClicked(int curProj,int itemId,int pbType);
private:
	Ui::QParamTem ui;
	void RenewTree();
	void RenewDataTable(int _curProj,int _curReg);
	CdataStruct *dataPara = nullptr;
	void IniWindows();
private slots:
	void on_pB_addProj_clicked();
	void on_pB_addReg_clicked();
	void on_pB_del_clicked();
	void on_pB_moveUp_clicked();
	void on_pB_moveDown_clicked();
	void on_pB_insertReg_clicked();
	void on_pB_save_clicked();

	//列表点击事件
	void on_treeW_itemClicked(QTreeWidgetItem *item, int col);
	void on_tableW_reg_itemClicked(QTableWidgetItem* item);

	void on_set_clicked();

};
