#pragma once

#include <QObject>
#include<CdataStruct.h>
#include<Windows.h>
#include<qstringlist.h>
#include<arithClass.h>
#include<qvariant.h>
#include<qtimer.h>
#include<qdatetime.h>
class Qth_SystemCall : public QObject
{
	Q_OBJECT

public:
	Qth_SystemCall(QObject *parent=nullptr);
	~Qth_SystemCall();
	void processPic(HWND win);
	void getData(CdataStruct* _data);
signals:
	void sig_valReg(double, QString,int);
	void sig_pos(int, int);
	void sig_error(QString);
	void sig_time(int);
private:
	CdataStruct *m_data = nullptr;
	QStringList datalist;
	arithClass *pArith = nullptr;
	int m_clickCount=0;//鼠标连续点击的次数
	int m_checkCount = 0;//检测次数

	//相对于区域的点击位置
	int m_mousX = 0;
	int m_mousY = 0;
	//区域的宽高
	int m_width = 0;
	int m_height = 0;
	//重复点击时的区域
	cv::Rect m_clickReg;
	//重复点击区域边长
	int m_regW = 10;
	//重复点击的前次数
	int m_dclick = 0;

	std::vector<cv::Mat> listTemMap;
	std::vector<cv::Mat> listTemCheck;

	int m_times = 0;
	QTimer timer;
	bool m_isMap = false;
	bool m_isClick = false;
	bool m_isCheck = false;
	double m_val=0;
	HWND m_win;
	cv::Mat m_srcpic;
	cv::Mat dstpic;
	std::vector<QVariant> res;
	void AutoState(bool ismap, bool isclick, bool ischeck);
	bool m_isNeedRepeClick = false;
	bool SystemCall(cv::Mat &_srcpic, HWND win,int curProj);
	bool AutoCCPlay(cv::Mat &_srcpic, HWND win, int curProj);
	int GetValue(QStringList &datalist, int curReg, int type);
	int CheckPic(cv::Mat &_srcpic, HWND win, int curProj,int curReg, int type);
private slots:
	void on_Timer();

};
