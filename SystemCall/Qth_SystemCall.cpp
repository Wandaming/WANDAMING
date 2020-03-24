#include "Qth_SystemCall.h"
#include<qmessagebox.h>
#include<QWinControl.h>
#include<atomic>
#include<arith_SystemCall.h>
#include<ctime>

#include<mmsystem.h>
#pragma comment(lib, "winmm.lib")
extern std::atomic_bool g_isStop;
Qth_SystemCall::Qth_SystemCall(QObject *parent)
	: QObject(parent)
{
	QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(on_Timer()));
	
}

Qth_SystemCall::~Qth_SystemCall()
{
	if (pArith != nullptr)
	{
		delete pArith;
		pArith = nullptr;
	}

	
}
void Qth_SystemCall::on_Timer()
{
	timer.stop();

	if (!g_isStop)
	{	
		if (m_isMap)
		{
			//���׶�
			AutoState(0, 0, 0);
			int ires = CheckPic(m_srcpic, m_win, m_data->curProj, m_data->count, 0);
			if (ires == -1)
			{
				g_isStop = true;
				return;
			}
			else if (ires == 0)
			{
				//�����ƥ�䣬�����µ��������ɼ�ͼ��
				//int time = rand() % 300;
				//Sleep(time);
				AutoState(1, 0, 0);
				if (m_data->listProj.at(m_data->curProj).checkTimesTh>0)
				{
					m_checkCount++;
					if (m_checkCount >= m_data->listProj.at(m_data->curProj).checkTimesTh)
					{
						//Ƶ����������������ź�
						g_isStop = true;
						PlaySound(TEXT("waring.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
						emit sig_error(tr("����������"));
					}
				}
			}
			else if (ires == 1)
			{
				//���ƥ�䣬�ڸ�����������һ��
				AutoState(0, 1, 0);
				//ƥ��ɹ�֮�󣬵ȴ�һ����е��
				Sleep(rand() % 300);
				m_clickCount = 0;
				m_checkCount = 0;
			}
			emit sig_valReg(m_val,QString::fromLocal8Bit(m_data->listProj.at(m_data->curProj).listReg.at(m_data->count).name.data()),0);
		}

		if (m_isClick)
		{
			//����׶�
			AutoState(0, 0, 0);		
			//�Ƿ���Ҫ���
			if (!m_data->listProj.at(m_data->curProj).listReg.at(m_data->count).isNotClick)
			{

				if (m_clickCount==0)
				{
					m_width = m_data->listProj.at(m_data->curProj).listReg.at(m_data->count).rectRoiClick.width*m_data->picScale;
					m_height = m_data->listProj.at(m_data->curProj).listReg.at(m_data->count).rectRoiClick.height*m_data->picScale;
					
					m_mousX = rand() % m_width;
					m_mousY = rand() % m_height;
					m_mousX = m_mousX + m_data->listProj.at(m_data->curProj).listReg.at(m_data->count).rectRoiClick.x*m_data->picScale;
					m_mousY = m_mousY + m_data->listProj.at(m_data->curProj).listReg.at(m_data->count).rectRoiClick.y*m_data->picScale;
					//�ظ�������������
					m_dclick = 3 + rand() % 5;
					//����һ��С��������
					m_clickReg = cv::Rect(m_mousX - m_regW / 2, m_mousY - m_regW / 2, m_regW, m_regW);
				}
				else if(m_clickCount>0&& m_clickCount< m_dclick)
				{
					
					m_mousX = rand() % m_regW;
					m_mousY = rand() % m_regW;
					m_mousX += m_clickReg.x;
					m_mousY += m_clickReg.y;

				}
				else if (m_clickCount>= m_dclick)
				{
					m_width = m_data->listProj.at(m_data->curProj).listReg.at(m_data->count).rectRoiClick.width*m_data->picScale;
					m_height = m_data->listProj.at(m_data->curProj).listReg.at(m_data->count).rectRoiClick.height*m_data->picScale;
					m_mousX = rand() % m_width;
					m_mousY = rand() % m_height;
					m_mousX = m_mousX + m_data->listProj.at(m_data->curProj).listReg.at(m_data->count).rectRoiClick.x*m_data->picScale;
					m_mousY = m_mousY + m_data->listProj.at(m_data->curProj).listReg.at(m_data->count).rectRoiClick.y*m_data->picScale;
				}


				//������λ�÷�������ź�
				QWinControl::SendWinLClick(m_win, m_mousX, m_mousY);
				emit sig_pos(m_mousX, m_mousY);
				m_clickCount++;
				if (m_clickCount>=10)
				{
					//Ƶ����������������ź�
					g_isStop = true;
					PlaySound(TEXT("waring.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
					emit sig_error(tr("�ظ������������"));
				}
			}			
			AutoState(0, 0, 1);	
		}

		if (m_isCheck)
		{
			AutoState(0, 0, 0);
			//��������У��׶ο��Եȴ�һ��
			Sleep(rand() % 400);
			int ires = CheckPic(m_srcpic, m_win, m_data->curProj, m_data->count, 2);
			if (ires == -1)
			{
				g_isStop = true;
				return;
			}
			else if (ires == 0)
			{
				//У��ʧ�ܣ������ظ����
				AutoState(0, 1, 0);
			}
			else if (ires == 1)
			{
				//У��ɹ�
				//�����źź������½���ѭ��
				if (m_data->count >= m_data->listProj.at(m_data->curProj).listReg.size() - 1)
				{
					//һ�ֽ���֮�󣬿��ԵȾ�һ��
					m_data->count = 0;
					m_times++;
					emit sig_time(m_times);
					Sleep(rand() % 3000);

				}
				else
				{
					m_data->count++;
				}
				AutoState(1, 0, 0);
			}
			emit sig_valReg(m_val, QString::fromLocal8Bit(m_data->listProj.at(m_data->curProj).listReg.at(m_data->count).name.data()),2);
		}
	}
	timer.start();
}


void Qth_SystemCall::processPic(HWND win)
{
	cv::Mat srcpic;
	if (win == nullptr)
		return;
	m_win = win;
	if (pArith==nullptr)
	{
		pArith = new arith_SystemCall();
	}

	int curProj = m_data->curProj;
	if (curProj < 0 || curProj >= m_data->listProj.size())
	{
		emit sig_error("û��ѡ�е�ǰ��Ŀ");
		return;
	}
	

	//����ģ��ͼƬ
	listTemMap.swap(std::vector<cv::Mat>(m_data->listProj.at(curProj).listReg.size()));
	listTemCheck.swap(std::vector<cv::Mat>(m_data->listProj.at(curProj).listReg.size()));
	cv::Mat pic;
	for (int i=0;i< m_data->listProj.at(curProj).listReg.size();i++)
	{
		pic= cv::imread(m_data->listProj.at(curProj).listReg.at(i).roiPicPathMap, -1);
		if (!pic.empty())
			listTemMap.at(i) = pic.clone();
		pic = cv::imread(m_data->listProj.at(curProj).listReg.at(i).roiPicPathCheck, -1);
		if (!pic.empty())
			listTemCheck.at(i) = pic.clone();
	}
	m_data->count = 0;
	m_times = 0;
	m_checkCount = 0;
	srand(time(0));
	AutoState(1, 0, 0);
	timer.start(200);
	//SystemCall(srcpic, win, curProj);
}

void Qth_SystemCall::getData(CdataStruct * _data)
{
	m_data = _data;
}

void Qth_SystemCall::AutoState(bool ismap, bool isclick, bool ischeck)
{
	m_isMap = ismap;	
	m_isClick = isclick;
	m_isCheck = ischeck;
}

bool Qth_SystemCall::SystemCall(cv::Mat &srcpic, HWND _win,int curProj)
{
	//�������
	//���������������������������У������
	//��������У����ȷ����һ�ּ������
	//�������������ظ��������
	//����������������������ټ������һ��
	if (!g_isStop)
	{
		srand(time(0));
		int ires = CheckPic(srcpic, _win, curProj, m_data->count,0);
		if (ires == -1)
		{
			return false;
		}
		else if(ires==0)
		{
			//�����ƥ�䣬�����µ��������ɼ�ͼ��
			int time = rand() % 300;
			Sleep(time);
			SystemCall(srcpic, _win, curProj);
			
		}
		else if (ires == 1)
		{
			//���ƥ�䣬�ڸ�����������һ��
			if (AutoCCPlay(srcpic, _win, curProj))
			{
				SystemCall(srcpic, _win, curProj);
			}
			else
			{
				return false;
			}

		}

	}
	return true;
}

bool Qth_SystemCall::AutoCCPlay(cv::Mat & _srcpic, HWND _win, int curProj)
{
	if (!g_isStop)
	{
		srand(time(0));
		//���ǵ�����
		Sleep(rand() % 2000);
		int width = m_data->listProj.at(curProj).listReg.at(m_data->count).rectRoiClick.width*m_data->picScale;
		int height = m_data->listProj.at(curProj).listReg.at(m_data->count).rectRoiClick.height*m_data->picScale;

		int mousX = rand() % width;
		int mousY = rand() % height;

		mousX = mousX + m_data->listProj.at(curProj).listReg.at(m_data->count).rectRoiClick.x*m_data->picScale;
		mousY = mousY + m_data->listProj.at(curProj).listReg.at(m_data->count).rectRoiClick.y*m_data->picScale;
		//������λ�÷�������ź�
		QWinControl::SendWinLClick(_win, mousX, mousY);
		Sleep(rand() % 500);
		int ires = CheckPic(_srcpic, _win, curProj, m_data->count, 2);
		if (ires == -1)
		{
			return false;
		}
		else if (ires == 0)
		{
			//У��ʧ�ܣ��ظ����
			AutoCCPlay(_srcpic, _win, curProj);
		}
		else if (ires == 1)
		{
			//У��ɹ�
			m_isNeedRepeClick = false;
			//�����źź������½���ѭ��
			if (m_data->count >= m_data->listProj.at(curProj).listReg.size() - 1)
			{
				m_data->count = 0;
			}
			else
			{
				m_data->count++;
			}
			return true;
		}
	}
	return true;
}

int Qth_SystemCall::GetValue(QStringList &_datalist,int curReg,int type)
{
	_datalist.clear();
	int curPorj = m_data->curProj;
	if (curPorj < 0 || curPorj >= m_data->listProj.size())
		return -1;
	if (curReg<0|| curReg >= m_data->listProj.at(curPorj).listReg.size())
		return 1;
	if (type == 0)
	{
		_datalist << QString::number(m_data->listProj.at(curPorj).listReg.at(curReg).rectRoiMap.x)
			<< QString::number(m_data->listProj.at(curPorj).listReg.at(curReg).rectRoiMap.y)
			<< QString::number(m_data->listProj.at(curPorj).listReg.at(curReg).rectRoiMap.width)
			<< QString::number(m_data->listProj.at(curPorj).listReg.at(curReg).rectRoiMap.height)
			<< QString::fromLocal8Bit(m_data->listProj.at(curPorj).listReg.at(curReg).roiPicPathMap.data())
			<< QString::number(m_data->listProj.at(curPorj).listReg.at(curReg).mapVal)
			<< QString::number(m_data->listProj.at(curPorj).listReg.at(curReg).isAntiMap);

	}
	else if (type==2)
	{
		_datalist << QString::number(m_data->listProj.at(curPorj).listReg.at(curReg).rectRoiCheck.x)
			<< QString::number(m_data->listProj.at(curPorj).listReg.at(curReg).rectRoiCheck.y)
			<< QString::number(m_data->listProj.at(curPorj).listReg.at(curReg).rectRoiCheck.width)
			<< QString::number(m_data->listProj.at(curPorj).listReg.at(curReg).rectRoiCheck.height)
			<< QString::fromLocal8Bit(m_data->listProj.at(curPorj).listReg.at(curReg).roiPicPathCheck.data())
			<< QString::number(m_data->listProj.at(curPorj).listReg.at(curReg).checkVal)
			<< QString::number(m_data->listProj.at(curPorj).listReg.at(curReg).isAntiCheck);
	}
	_datalist << QString::number(m_data->listProj.at(curPorj).tempW)
		<< QString::number(m_data->listProj.at(curPorj).tempH);


	pArith->getValue(_datalist,false);


	if (type == 0)
	{
		//�������
		if (!arithClass::IdxIsInVect(curReg, listTemMap))
			return 2;
		if (listTemMap.at(curReg).empty())
			return 3;
		pArith->GetTemMat(listTemMap.at(curReg));
	}
	else if (type==2)
	{
		//У������
		if (!arithClass::IdxIsInVect(curReg, listTemCheck))
			return 2;
		if (listTemCheck.at(curReg).empty())
			return 3;
		pArith->GetTemMat(listTemCheck.at(curReg));
	}


	return 0;
}

int Qth_SystemCall::CheckPic(cv::Mat & srcpic, HWND win, int curProj,int curReg,int type)
{
	QWinControl::GetMat2(win, srcpic);
	if (srcpic.empty())
		return -1;
	//�����㷨���
	//��ȡ����
	int getRes = GetValue(datalist, curReg, type);
	if (getRes==-1)
	{
		emit sig_error("��ȡ��ǰ��Ŀ����");
		return -1;
	}
	else if (getRes==1)
	{
		emit sig_error("��ȡ��ǰ�������");
		return -1;
	}
	else if (getRes == 2)
	{
		emit sig_error("��ȡ��ǰģ��ͼ�����");
		return -1;
	}
	else if (getRes == 3)
	{
		emit sig_error("��ǰģ��ͼ��Ϊ��");
		return -1;
	}
	//��ȡģ��ͼƬ
	
	//�㷨���ص�Ӧ�����Ƿ���Ҫ��������
	if (!pArith->ProcessFun(srcpic, dstpic, res))
	{
		emit sig_error("�㷨����");
		return -1;
	}
	if (res.size() != 2)
	{
		emit sig_error("�㷨�������");
		return -1;
	}	

	if (res.at(0) == 1)
	{
		m_val = res.at(1).toDouble();
		return 1;
	}
	else if (res.at(0) == 0)
	{
		m_val = res.at(1).toDouble();
		return 0;
	}
	return -1;
}
