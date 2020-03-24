#pragma once

#include <QDialog>
#include "ui_QDialog_setting.h"
#include<opencv2/opencv.hpp>
#include<CdataStruct.h>
#include<QParamTem.h>
#include<qlabel.h>
#include<Windows.h>
#include<arithClass.h>
#include<qevent.h>
#include<QMyLabel.h>

class QDialog_setting : public QDialog
{
	Q_OBJECT

public:
	QDialog_setting(CdataStruct *_data, QWidget *parent = Q_NULLPTR);
	~QDialog_setting();

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void resizeEvent(QResizeEvent *event);
private:
	Ui::QDialog_setting ui;
	CdataStruct *m_data = nullptr;
	QParamTem *pQparamTem = nullptr;
	QMyLabel *lab_pic = nullptr;
	cv::Mat m_srcpic;
	cv::Mat m_showPic;
	QPoint mous2pic1;//����������pic��λ�ã������λ��
	QPoint mous2pic2;//����������pic��λ�ã��ͷŵ�λ��
	QPoint mous2lab1;//����������lab��λ�ã������λ��
	QPoint mous2lab2;//����������lab��λ�ã��ͷŵ�λ��
	QPoint pic2lab;//ͼƬ�����lab��λ��
	QPoint lab2this;//lab�����this��λ��
	QRect m_rect2lab;//�����lab��rect
	int Hvalue;
	int Vvalue;//��������λ��
	float picScale=1;
	HWND pWnd=nullptr;
	bool m_isSetRoi = false;
	bool isMoveLab = false;
	void IniWindow();
	bool ptIsInLab(QPoint &pt,QMyLabel *lab);

	int drawRecType = 0;//3�������,7�������,10У������
	void RenewPic();
	bool CheckCurData(int &curProj, int &curReg, bool isNeedCheckReg = true);
private slots:
	void on_pB_grab_clicked();
	void on_ckB_adjReg_clicked();

	//�����б�ĵ���¼���Ӧ
	void on_projClicked();
	void on_regClicked();
	void on_setClicked(int curProj, int curReg, int pbType);

	//���Ե��
	void on_pB_sendClick_clicked();

};
