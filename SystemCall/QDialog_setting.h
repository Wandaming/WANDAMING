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
	QPoint mous2pic1;//鼠标点击相对于pic的位置，点击的位置
	QPoint mous2pic2;//鼠标点击相对于pic的位置，释放的位置
	QPoint mous2lab1;//鼠标点击相对于lab的位置，点击的位置
	QPoint mous2lab2;//鼠标点击相对于lab的位置，释放的位置
	QPoint pic2lab;//图片相对于lab的位置
	QPoint lab2this;//lab相对于this的位置
	QRect m_rect2lab;//相对于lab的rect
	int Hvalue;
	int Vvalue;//滚动条的位置
	float picScale=1;
	HWND pWnd=nullptr;
	bool m_isSetRoi = false;
	bool isMoveLab = false;
	void IniWindow();
	bool ptIsInLab(QPoint &pt,QMyLabel *lab);

	int drawRecType = 0;//3检测区域,7点击区域,10校验区域
	void RenewPic();
	bool CheckCurData(int &curProj, int &curReg, bool isNeedCheckReg = true);
private slots:
	void on_pB_grab_clicked();
	void on_ckB_adjReg_clicked();

	//参数列表的点击事件响应
	void on_projClicked();
	void on_regClicked();
	void on_setClicked(int curProj, int curReg, int pbType);

	//测试点击
	void on_pB_sendClick_clicked();

};
