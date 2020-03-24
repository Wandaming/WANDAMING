#pragma once
#pragma execution_character_set("utf-8")
#include <QObject>
#include "../dllwincontrol_global.h"
#include<Windows.h>
#include<opencv2/opencv.hpp>

class DLLWINCONTROL_EXPORT QWinControl : public QObject
{
	Q_OBJECT

public:
	QWinControl(QObject *parent = nullptr);
	~QWinControl();
	static void GetMat(HWND hWnd,cv::Mat &_srcpic);
	static void GetMat2(HWND hWnd,cv::Mat &_srcpic);
	static HWND GetWinHWND(QString winname);
	static void SendWinLClick(HWND win,int posX,int posY);
};
