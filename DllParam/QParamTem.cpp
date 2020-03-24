#include "include/QParamTem.h"
#include<qmessagebox.h>
#include<qcheckbox.h>
#include<arithClass.h>
QParamTem::QParamTem(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	ui.tableW_data->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

QParamTem::~QParamTem()
{
}

void QParamTem::getData(CdataStruct * _data)
{
	dataPara = _data;
	IniWindows();
}





void QParamTem::RenewTree()
{
	//当前父节点，当前节点的名字修改

}

void QParamTem::RenewDataTable(int _curProj, int _curReg)
{
	if (!arithClass::IdxIsInVect(_curProj, dataPara->listProj))
		return;
	if (!arithClass::IdxIsInVect(_curReg, dataPara->listProj.at(_curProj).listReg))
		return;

	ui.tableW_data->setRowCount(0);
	int idx = 0;
	ui.tableW_data->insertRow(idx);
	ui.tableW_data->setItem(idx, 0, new QTableWidgetItem("当前项目"));
	ui.tableW_data->setItem(idx, 1, new QTableWidgetItem(QString::fromLocal8Bit(dataPara->listProj.at(_curProj).name.data())));
	
	idx++;
	ui.tableW_data->insertRow(idx);
	ui.tableW_data->setItem(idx, 0, new QTableWidgetItem("检测次数阈值"));
	ui.tableW_data->setItem(idx, 1, new QTableWidgetItem(QString::number(dataPara->listProj.at(_curProj).checkTimesTh)));

	idx++;
	ui.tableW_data->insertRow(idx);
	ui.tableW_data->setItem(idx, 0, new QTableWidgetItem("当前区域"));
	ui.tableW_data->setItem(idx, 1, new QTableWidgetItem(QString::fromLocal8Bit(dataPara->listProj.at(_curProj).listReg.at(_curReg).name.data())));

	idx++;
	ui.tableW_data->insertRow(idx);
	ui.tableW_data->setItem(idx, 0, new QTableWidgetItem("检测区域参数"));
	ui.tableW_data->setItem(idx, 1, new QTableWidgetItem("========"));

	idx++;
	ui.tableW_data->insertRow(idx);
	ui.tableW_data->setItem(idx, 0, new QTableWidgetItem("检测区域设置-绿"));
	QPushButton *pb = new QPushButton("设置区域",ui.tableW_data);
	pb->setProperty("type", 0);
	ui.tableW_data->setCellWidget(idx,1,pb);
	connect(pb, &QPushButton::clicked, this, &QParamTem::on_set_clicked);

	idx++;
	ui.tableW_data->insertRow(idx);
	ui.tableW_data->setItem(idx, 0, new QTableWidgetItem("检测方差"));
	ui.tableW_data->setItem(idx, 1, new QTableWidgetItem(QString::number(dataPara->listProj.at(_curProj).listReg.at(_curReg).mapVal)));

	idx++;
	ui.tableW_data->insertRow(idx);
	ui.tableW_data->setItem(idx, 0, new QTableWidgetItem("是否检测取反"));
	QCheckBox *ckb = new QCheckBox(ui.tableW_data);
	ckb->setChecked(dataPara->listProj.at(_curProj).listReg.at(_curReg).isAntiMap);
	ui.tableW_data->setCellWidget(idx, 1, ckb);

	idx++;
	ui.tableW_data->insertRow(idx);
	ui.tableW_data->setItem(idx, 0, new QTableWidgetItem("点击区域参数"));
	ui.tableW_data->setItem(idx, 1, new QTableWidgetItem("========"));

	idx++;
	ui.tableW_data->insertRow(idx);
	ui.tableW_data->setItem(idx, 0, new QTableWidgetItem("点击区域设置-黄"));
	pb = new QPushButton("设置区域", ui.tableW_data);
	pb->setProperty("type", 1);
	ui.tableW_data->setCellWidget(idx, 1, pb);
	connect(pb, &QPushButton::clicked, this, &QParamTem::on_set_clicked);

	idx++;
	ui.tableW_data->insertRow(idx);
	ui.tableW_data->setItem(idx, 0, new QTableWidgetItem("是否不需要点击"));
	ckb = new QCheckBox(ui.tableW_data);
	ckb->setChecked(dataPara->listProj.at(_curProj).listReg.at(_curReg).isNotClick);
	ui.tableW_data->setCellWidget(idx, 1, ckb);

	idx++;
	ui.tableW_data->insertRow(idx);
	ui.tableW_data->setItem(idx, 0, new QTableWidgetItem("校验区域参数"));
	ui.tableW_data->setItem(idx, 1, new QTableWidgetItem("========"));

	idx++;
	ui.tableW_data->insertRow(idx);
	ui.tableW_data->setItem(idx, 0, new QTableWidgetItem("检验区域设置-红"));
	pb = new QPushButton("设置区域", ui.tableW_data);
	pb->setProperty("type", 2);
	ui.tableW_data->setCellWidget(idx, 1, pb);
	connect(pb, &QPushButton::clicked, this, &QParamTem::on_set_clicked);

	idx++;
	ui.tableW_data->insertRow(idx);
	ui.tableW_data->setItem(idx, 0, new QTableWidgetItem("校验方差"));
	ui.tableW_data->setItem(idx, 1, new QTableWidgetItem(QString::number(dataPara->listProj.at(_curProj).listReg.at(_curReg).checkVal)));

	idx++;
	ui.tableW_data->insertRow(idx);
	ui.tableW_data->setItem(idx, 0, new QTableWidgetItem("是否校验取反"));
	ckb = new QCheckBox(ui.tableW_data);
	ckb->setChecked(dataPara->listProj.at(_curProj).listReg.at(_curReg).isAntiCheck);
	ui.tableW_data->setCellWidget(idx, 1, ckb);
}

void QParamTem::IniWindows()
{
	//刷新树形图
	QTreeWidgetItem *item;
	QTreeWidgetItem *ziItem;
	for (int i=0;i<dataPara->listProj.size();i++)
	{
		item = new QTreeWidgetItem(ui.treeW);
		item->setText(0, QString::fromLocal8Bit(dataPara->listProj.at(i).name.data()));
		for (int j=0;j<dataPara->listProj.at(i).listReg.size();j++)
		{
			ziItem = new QTreeWidgetItem(item);
			ziItem->setText(0, QString::fromLocal8Bit(dataPara->listProj.at(i).listReg.at(j).name.data()));
		}
	}
}



void QParamTem::on_pB_addProj_clicked()
{
	//数据添加
	dataPara->AddProj();
	//在树中添加一个根节点
	QTreeWidgetItem *item = new QTreeWidgetItem(ui.treeW);
	item->setText(0, "addProj");
	ui.treeW->setCurrentItem(item);
	dataPara->curProj = ui.treeW->currentIndex().row();
}

void QParamTem::on_pB_addReg_clicked()
{
	int curProj = dataPara->curProj;
	if (curProj < 0 || curProj >= dataPara->listProj.size())
	{
		QMessageBox::information(this, tr("提示"), tr("没有选择当前项目"), 0);
		return;
	}
	dataPara->listProj.at(curProj).AddReg();
	QTreeWidgetItem *item;
	item=ui.treeW->currentItem();
	if (item)
	{
		if (item->parent())
		{
			item = item->parent();
		}
		QTreeWidgetItem *ziItem = new QTreeWidgetItem(item);
		ziItem->setText(0, "addReg");
		ui.treeW->setCurrentItem(ziItem);
		if (!arithClass::IdxIsInVect(dataPara->curProj, dataPara->listProj))
			return;
		dataPara->listProj.at(dataPara->curProj).curReg = ui.treeW->currentIndex().row();
	}

}

void QParamTem::on_pB_del_clicked()
{
	//选择当前树
	QTreeWidgetItem *item = ui.treeW->currentItem();
	if (item)
	{
		if (item->parent())
		{
			//表明此项为区域项
			//只需要删除区域
			int curReg = ui.treeW->currentIndex().row();
			QTreeWidgetItem *itemFu = item->parent();
			ui.treeW->setCurrentItem(itemFu);
			int curProj = ui.treeW->currentIndex().row();
			if (!arithClass::IdxIsInVect(curProj, dataPara->listProj))
				return;
			if (!arithClass::IdxIsInVect(curReg, dataPara->listProj.at(curProj).listReg))
				return;
			dataPara->listProj.at(curProj).RemoveReg(curReg);
			delete item;
			item = nullptr;

		}
		else
		{
			//此为项目项
			int curProj = ui.treeW->currentIndex().row();
			if (!arithClass::IdxIsInVect(curProj, dataPara->listProj))
				return;
			dataPara->RemovePorj(curProj);
			delete ui.treeW->takeTopLevelItem(ui.treeW->currentIndex().row());
		}
	}
	
}

void QParamTem::on_pB_moveUp_clicked()
{
	int curProj = dataPara->curProj;
	if (curProj < 0 || curProj >= dataPara->listProj.size())
	{
		QMessageBox::information(this, tr("提示"), tr("没有选择当前项目"), 0);
		return;
	}
	int curReg = dataPara->listProj.at(curProj).curReg;
	if (curReg < 0 || curReg >= dataPara->listProj.at(curProj).listReg.size())
	{
		QMessageBox::information(this, tr("提示"), tr("没有选择当前区域"), 0);
		return;
	}

	dataPara->listProj.at(curProj).MoveUp(curReg);



}
void QParamTem::on_pB_moveDown_clicked()
{
	int curProj = dataPara->curProj;
	if (curProj < 0 || curProj >= dataPara->listProj.size())
	{
		QMessageBox::information(this, tr("提示"), tr("没有选择当前项目"), 0);
		return;
	}
	int curReg = dataPara->listProj.at(curProj).curReg;
	if (curReg < 0 || curReg >= dataPara->listProj.at(curProj).listReg.size())
	{
		QMessageBox::information(this, tr("提示"), tr("没有选择当前区域"), 0);
		return;
	}

	dataPara->listProj.at(curProj).MoveDown(curReg);


}

void QParamTem::on_pB_insertReg_clicked()
{
	int curProj = dataPara->curProj;
	if (curProj < 0 || curProj >= dataPara->listProj.size())
	{
		QMessageBox::information(this, tr("提示"), tr("没有选择当前项目"), 0);
		return;
	}
	int curReg = dataPara->listProj.at(curProj).curReg;
	if (curReg < 0 || curReg >= dataPara->listProj.at(curProj).listReg.size())
	{
		QMessageBox::information(this, tr("提示"), tr("没有选择当前区域"), 0);
		return;
	}
	dataPara->listProj.at(curProj).InsertReg(curReg);
	QTreeWidgetItem *item =new QTreeWidgetItem();
	item->setText(0, "newRegInsert");
	ui.treeW->currentItem()->parent()->insertChild(curReg, item);


}

void QParamTem::on_pB_save_clicked()
{
	int curProj = dataPara->curProj;
	if (!arithClass::IdxIsInVect(curProj, dataPara->listProj))
		return;
	int curReg = dataPara->listProj.at(curProj).curReg;
	if (!arithClass::IdxIsInVect(curReg, dataPara->listProj.at(curProj).listReg))
		return;
	int idx = 0;//项目名
	QTableWidgetItem *item = ui.tableW_data->item(idx, 1);
	if (item)
	{
		dataPara->listProj.at(curProj).name = item->text().toLocal8Bit().toStdString();
		//需要刷新树状图
		QTreeWidgetItem *treeItem = ui.treeW->currentItem();
		if (treeItem->parent())
		{
			treeItem->parent()->setText(0, QString::fromLocal8Bit(dataPara->listProj.at(curProj).name.data()));
		}
		else
		{
			treeItem->setText(0, QString::fromLocal8Bit(dataPara->listProj.at(curProj).name.data()));
		}

	}
	idx++;//检测次数阈值
	item = ui.tableW_data->item(idx, 1);
	if (item)
	{
		dataPara->listProj.at(curProj).checkTimesTh = item->text().toInt();
	}
	idx++;//区域名
	item = ui.tableW_data->item(idx, 1);
	if (item)
	{
		dataPara->listProj.at(curProj).listReg.at(curReg).name = item->text().toLocal8Bit().toStdString();
		//需要刷新树状图
		QTreeWidgetItem *treeItem = ui.treeW->currentItem();
		if (treeItem->parent())
		{
			treeItem->setText(0, QString::fromLocal8Bit(dataPara->listProj.at(curProj).listReg.at(curReg).name.data()));
		}
	}
	idx++;//分割线
	idx++;//检测区域设置
	idx++;//检测方差
	item = ui.tableW_data->item(idx, 1);
	if (item)
	{
		dataPara->listProj.at(curProj).listReg.at(curReg).mapVal = item->text().toDouble();
	}
	idx++;//是否取反
	QCheckBox *ckb = (QCheckBox *)ui.tableW_data->cellWidget(idx, 1);
	if (ckb)
	{	
		dataPara->listProj.at(curProj).listReg.at(curReg).isAntiMap = ckb->isChecked();
	}
	idx++;//分割线
	idx++;//点击区域设置
	idx++;//是否需要点击
	ckb = (QCheckBox *)ui.tableW_data->cellWidget(idx, 1);
	if (ckb)
	{
		dataPara->listProj.at(curProj).listReg.at(curReg).isNotClick = ckb->isChecked();
	}
	idx++;//分割线
	idx++;//校验区域设置
	idx++;//校验方差
	item = ui.tableW_data->item(idx, 1);
	if (item)
	{
		dataPara->listProj.at(curProj).listReg.at(curReg).checkVal = item->text().toDouble();
	}
	idx++;//是否取反
	ckb = (QCheckBox *)ui.tableW_data->cellWidget(idx, 1);
	if (ckb)
	{
		dataPara->listProj.at(curProj).listReg.at(curReg).isAntiCheck = ckb->isChecked();
	}

	dataPara->DataWrite(QApplication::applicationDirPath().toLocal8Bit().toStdString());
}


void QParamTem::on_treeW_itemClicked(QTreeWidgetItem * item, int col)
{
	int curProj, curReg;
	if (!item->parent())
	{
		//点击的是项目
		curProj = ui.treeW->currentIndex().row();
		dataPara->curProj = curProj;
		if (!arithClass::IdxIsInVect(curProj, dataPara->listProj))
			return;
		dataPara->listProj.at(curProj).curReg = -1;
	}
	else
	{
		//点击的是区域
		curReg=ui.treeW->currentIndex().row();
		ui.treeW->setCurrentItem(item->parent());
		curProj = ui.treeW->currentIndex().row();
		ui.treeW->setCurrentItem(item);

		dataPara->curProj = curProj;
		if (!arithClass::IdxIsInVect(curProj, dataPara->listProj))
			return;
		dataPara->listProj.at(curProj).curReg = curReg;
		RenewDataTable(curProj, curReg);
	}

	emit sig_regClicked(dataPara->curProj,dataPara->listProj.at(curProj).curReg);
}

void QParamTem::on_tableW_reg_itemClicked(QTableWidgetItem * item)
{
	int curProj = dataPara->curProj;
	if (curProj < 0 || curProj >= dataPara->listProj.size())
	{
		QMessageBox::information(this, tr("提示"), tr("没有选择当前项目"), 0);
		return;
	}

}

void QParamTem::on_set_clicked()
{
	int curProj = dataPara->curProj;
	if (curProj < 0 || curProj >= dataPara->listProj.size())
		return;
	int curReg = dataPara->listProj.at(curProj).curReg;
	if (curReg<0 || curReg>=dataPara->listProj.at(curProj).listReg.size())
		return;
	QPushButton *pb = (QPushButton *)sender();
	int type = pb->property("type").toInt();
	emit sig_pbSetClicked(curProj, curReg, type);
}
