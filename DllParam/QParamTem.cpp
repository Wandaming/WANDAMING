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
	//��ǰ���ڵ㣬��ǰ�ڵ�������޸�

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
	ui.tableW_data->setItem(idx, 0, new QTableWidgetItem("��ǰ��Ŀ"));
	ui.tableW_data->setItem(idx, 1, new QTableWidgetItem(QString::fromLocal8Bit(dataPara->listProj.at(_curProj).name.data())));
	
	idx++;
	ui.tableW_data->insertRow(idx);
	ui.tableW_data->setItem(idx, 0, new QTableWidgetItem("��������ֵ"));
	ui.tableW_data->setItem(idx, 1, new QTableWidgetItem(QString::number(dataPara->listProj.at(_curProj).checkTimesTh)));

	idx++;
	ui.tableW_data->insertRow(idx);
	ui.tableW_data->setItem(idx, 0, new QTableWidgetItem("��ǰ����"));
	ui.tableW_data->setItem(idx, 1, new QTableWidgetItem(QString::fromLocal8Bit(dataPara->listProj.at(_curProj).listReg.at(_curReg).name.data())));

	idx++;
	ui.tableW_data->insertRow(idx);
	ui.tableW_data->setItem(idx, 0, new QTableWidgetItem("����������"));
	ui.tableW_data->setItem(idx, 1, new QTableWidgetItem("========"));

	idx++;
	ui.tableW_data->insertRow(idx);
	ui.tableW_data->setItem(idx, 0, new QTableWidgetItem("�����������-��"));
	QPushButton *pb = new QPushButton("��������",ui.tableW_data);
	pb->setProperty("type", 0);
	ui.tableW_data->setCellWidget(idx,1,pb);
	connect(pb, &QPushButton::clicked, this, &QParamTem::on_set_clicked);

	idx++;
	ui.tableW_data->insertRow(idx);
	ui.tableW_data->setItem(idx, 0, new QTableWidgetItem("��ⷽ��"));
	ui.tableW_data->setItem(idx, 1, new QTableWidgetItem(QString::number(dataPara->listProj.at(_curProj).listReg.at(_curReg).mapVal)));

	idx++;
	ui.tableW_data->insertRow(idx);
	ui.tableW_data->setItem(idx, 0, new QTableWidgetItem("�Ƿ���ȡ��"));
	QCheckBox *ckb = new QCheckBox(ui.tableW_data);
	ckb->setChecked(dataPara->listProj.at(_curProj).listReg.at(_curReg).isAntiMap);
	ui.tableW_data->setCellWidget(idx, 1, ckb);

	idx++;
	ui.tableW_data->insertRow(idx);
	ui.tableW_data->setItem(idx, 0, new QTableWidgetItem("����������"));
	ui.tableW_data->setItem(idx, 1, new QTableWidgetItem("========"));

	idx++;
	ui.tableW_data->insertRow(idx);
	ui.tableW_data->setItem(idx, 0, new QTableWidgetItem("�����������-��"));
	pb = new QPushButton("��������", ui.tableW_data);
	pb->setProperty("type", 1);
	ui.tableW_data->setCellWidget(idx, 1, pb);
	connect(pb, &QPushButton::clicked, this, &QParamTem::on_set_clicked);

	idx++;
	ui.tableW_data->insertRow(idx);
	ui.tableW_data->setItem(idx, 0, new QTableWidgetItem("�Ƿ���Ҫ���"));
	ckb = new QCheckBox(ui.tableW_data);
	ckb->setChecked(dataPara->listProj.at(_curProj).listReg.at(_curReg).isNotClick);
	ui.tableW_data->setCellWidget(idx, 1, ckb);

	idx++;
	ui.tableW_data->insertRow(idx);
	ui.tableW_data->setItem(idx, 0, new QTableWidgetItem("У���������"));
	ui.tableW_data->setItem(idx, 1, new QTableWidgetItem("========"));

	idx++;
	ui.tableW_data->insertRow(idx);
	ui.tableW_data->setItem(idx, 0, new QTableWidgetItem("������������-��"));
	pb = new QPushButton("��������", ui.tableW_data);
	pb->setProperty("type", 2);
	ui.tableW_data->setCellWidget(idx, 1, pb);
	connect(pb, &QPushButton::clicked, this, &QParamTem::on_set_clicked);

	idx++;
	ui.tableW_data->insertRow(idx);
	ui.tableW_data->setItem(idx, 0, new QTableWidgetItem("У�鷽��"));
	ui.tableW_data->setItem(idx, 1, new QTableWidgetItem(QString::number(dataPara->listProj.at(_curProj).listReg.at(_curReg).checkVal)));

	idx++;
	ui.tableW_data->insertRow(idx);
	ui.tableW_data->setItem(idx, 0, new QTableWidgetItem("�Ƿ�У��ȡ��"));
	ckb = new QCheckBox(ui.tableW_data);
	ckb->setChecked(dataPara->listProj.at(_curProj).listReg.at(_curReg).isAntiCheck);
	ui.tableW_data->setCellWidget(idx, 1, ckb);
}

void QParamTem::IniWindows()
{
	//ˢ������ͼ
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
	//�������
	dataPara->AddProj();
	//���������һ�����ڵ�
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
		QMessageBox::information(this, tr("��ʾ"), tr("û��ѡ��ǰ��Ŀ"), 0);
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
	//ѡ��ǰ��
	QTreeWidgetItem *item = ui.treeW->currentItem();
	if (item)
	{
		if (item->parent())
		{
			//��������Ϊ������
			//ֻ��Ҫɾ������
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
			//��Ϊ��Ŀ��
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
		QMessageBox::information(this, tr("��ʾ"), tr("û��ѡ��ǰ��Ŀ"), 0);
		return;
	}
	int curReg = dataPara->listProj.at(curProj).curReg;
	if (curReg < 0 || curReg >= dataPara->listProj.at(curProj).listReg.size())
	{
		QMessageBox::information(this, tr("��ʾ"), tr("û��ѡ��ǰ����"), 0);
		return;
	}

	dataPara->listProj.at(curProj).MoveUp(curReg);



}
void QParamTem::on_pB_moveDown_clicked()
{
	int curProj = dataPara->curProj;
	if (curProj < 0 || curProj >= dataPara->listProj.size())
	{
		QMessageBox::information(this, tr("��ʾ"), tr("û��ѡ��ǰ��Ŀ"), 0);
		return;
	}
	int curReg = dataPara->listProj.at(curProj).curReg;
	if (curReg < 0 || curReg >= dataPara->listProj.at(curProj).listReg.size())
	{
		QMessageBox::information(this, tr("��ʾ"), tr("û��ѡ��ǰ����"), 0);
		return;
	}

	dataPara->listProj.at(curProj).MoveDown(curReg);


}

void QParamTem::on_pB_insertReg_clicked()
{
	int curProj = dataPara->curProj;
	if (curProj < 0 || curProj >= dataPara->listProj.size())
	{
		QMessageBox::information(this, tr("��ʾ"), tr("û��ѡ��ǰ��Ŀ"), 0);
		return;
	}
	int curReg = dataPara->listProj.at(curProj).curReg;
	if (curReg < 0 || curReg >= dataPara->listProj.at(curProj).listReg.size())
	{
		QMessageBox::information(this, tr("��ʾ"), tr("û��ѡ��ǰ����"), 0);
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
	int idx = 0;//��Ŀ��
	QTableWidgetItem *item = ui.tableW_data->item(idx, 1);
	if (item)
	{
		dataPara->listProj.at(curProj).name = item->text().toLocal8Bit().toStdString();
		//��Ҫˢ����״ͼ
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
	idx++;//��������ֵ
	item = ui.tableW_data->item(idx, 1);
	if (item)
	{
		dataPara->listProj.at(curProj).checkTimesTh = item->text().toInt();
	}
	idx++;//������
	item = ui.tableW_data->item(idx, 1);
	if (item)
	{
		dataPara->listProj.at(curProj).listReg.at(curReg).name = item->text().toLocal8Bit().toStdString();
		//��Ҫˢ����״ͼ
		QTreeWidgetItem *treeItem = ui.treeW->currentItem();
		if (treeItem->parent())
		{
			treeItem->setText(0, QString::fromLocal8Bit(dataPara->listProj.at(curProj).listReg.at(curReg).name.data()));
		}
	}
	idx++;//�ָ���
	idx++;//�����������
	idx++;//��ⷽ��
	item = ui.tableW_data->item(idx, 1);
	if (item)
	{
		dataPara->listProj.at(curProj).listReg.at(curReg).mapVal = item->text().toDouble();
	}
	idx++;//�Ƿ�ȡ��
	QCheckBox *ckb = (QCheckBox *)ui.tableW_data->cellWidget(idx, 1);
	if (ckb)
	{	
		dataPara->listProj.at(curProj).listReg.at(curReg).isAntiMap = ckb->isChecked();
	}
	idx++;//�ָ���
	idx++;//�����������
	idx++;//�Ƿ���Ҫ���
	ckb = (QCheckBox *)ui.tableW_data->cellWidget(idx, 1);
	if (ckb)
	{
		dataPara->listProj.at(curProj).listReg.at(curReg).isNotClick = ckb->isChecked();
	}
	idx++;//�ָ���
	idx++;//У����������
	idx++;//У�鷽��
	item = ui.tableW_data->item(idx, 1);
	if (item)
	{
		dataPara->listProj.at(curProj).listReg.at(curReg).checkVal = item->text().toDouble();
	}
	idx++;//�Ƿ�ȡ��
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
		//���������Ŀ
		curProj = ui.treeW->currentIndex().row();
		dataPara->curProj = curProj;
		if (!arithClass::IdxIsInVect(curProj, dataPara->listProj))
			return;
		dataPara->listProj.at(curProj).curReg = -1;
	}
	else
	{
		//�����������
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
		QMessageBox::information(this, tr("��ʾ"), tr("û��ѡ��ǰ��Ŀ"), 0);
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
