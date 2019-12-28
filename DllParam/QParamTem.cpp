#include "include/QParamTem.h"

QParamTem::QParamTem(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	ui.tableW_proj->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.tableW_reg->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

QParamTem::~QParamTem()
{
}

void QParamTem::getData(CdataStruct * _data)
{
	dataPara = _data;
}

void QParamTem::RenewProjTable()
{
	//将界面清空
	ui.tableW_proj->setRowCount(0);
	for (int i=0;i<dataPara->listProj.size();i++)
	{
		ui.tableW_proj->insertRow(i);
		ui.tableW_proj->setItem(i,0,new QTableWidgetItem(QString::fromLocal8Bit(dataPara->listProj.at(i).name.data())));
	}

}

void QParamTem::RenewRegTable(int _curProj)
{

}

void QParamTem::on_pB_addProj_clicked()
{
	//数据添加
	dataPara->AddProj();
	//刷新table
	
}

void QParamTem::on_pB_delProj_clicked()
{

}
void QParamTem::on_pB_save_clicked()
{
}
void QParamTem::on_pB_reg_clicked()
{
}
void QParamTem::on_pB_delReg_clicked()
{
}
void QParamTem::on_pB_moveUp_clicked()
{
}
void QParamTem::on_pB_moveDown_clicked()
{
}