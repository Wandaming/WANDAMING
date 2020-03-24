#include "QDialog_setting.h"
#include<qmessagebox.h>
#include<qdatetime.h>
#include<sstream>
#include<qscrollbar.h>
#include<QWinControl.h>
#include<arithClass.h>
#include<arith_yuchuli.h>
QDialog_setting::QDialog_setting(CdataStruct *_data,QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	m_data = _data;

	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowMinMaxButtonsHint;
	flags |= Qt::WindowCloseButtonHint;
	setWindowFlags(flags);


	pQparamTem = new QParamTem(this);
	//layout->insertWidget(0,pQparamTem);
	ui.vLayout_param->addWidget(pQparamTem);
	connect(pQparamTem, &QParamTem::sig_projClicked,this, &QDialog_setting::on_projClicked);
	connect(pQparamTem, &QParamTem::sig_regClicked, this, &QDialog_setting::on_regClicked);
	connect(pQparamTem, &QParamTem::sig_pbSetClicked, this, &QDialog_setting::on_setClicked);


	lab_pic = new QMyLabel(this);
	lab_pic->resize(ui.sA_pic->size());
	lab_pic->setStyleSheet("background-color: rgb(200, 200, 200);");
	ui.sA_pic->setWidget(lab_pic);
	IniWindow();
}

QDialog_setting::~QDialog_setting()
{
	if (pQparamTem != nullptr)
	{
		pQparamTem->deleteLater();
		pQparamTem = nullptr;
	}

}

void QDialog_setting::IniWindow()
{
	if (m_data == nullptr)
		return;
	pQparamTem->getData(m_data);
}

bool QDialog_setting::ptIsInLab(QPoint &pt, QMyLabel *lab)
{
	bool isInlab = true;
	if (pt.x() < 0)
	{
		pt.setX(0);
		isInlab = false;
	}
	else if (pt.x()> lab->size().width()-1)
	{
		pt.setX(lab->size().width() - 1);
		isInlab = false;
	}

	if (pt.y() < 0)
	{
		pt.setY(0);
		isInlab = false;
	}
	else if (pt.y() > lab->size().height() - 1)
	{
		pt.setY(lab->size().height() - 1);
		isInlab = false;
	}

	return isInlab;
}

void QDialog_setting::RenewPic()
{
	//原图像拷贝一份，showpic
	//在showpic上依次画出相应的图像
	int curProg, curReg;
	if (CheckCurData(curProg, curReg))
	{
		m_showPic = m_srcpic.clone();
		cv::Rect rec;
		for (int i = 0; i < m_data->listProj.at(curProg).listReg.size(); i++)
		{
			//检测区域绿色
			rec = m_data->listProj.at(curProg).listReg.at(i).rectRoiMap;
			if (!arithClass::RectIsInPic(rec, m_showPic))
				continue;
			if (i == curReg)
			{
				cv::rectangle(m_showPic, rec, cv::Scalar(0, 255, 0), 2);
			}
			else
			{
				cv::rectangle(m_showPic, rec, cv::Scalar(255, 0, 0), 2);
			}
			

			//点击区域黄色
			rec = m_data->listProj.at(curProg).listReg.at(i).rectRoiClick;
			if (!arithClass::RectIsInPic(rec, m_showPic))
				continue;
			if (i == curReg)
			{
				cv::rectangle(m_showPic, rec, cv::Scalar(0, 255, 255), 2);
			}
			else
			{
				cv::rectangle(m_showPic, rec, cv::Scalar(255, 0, 0), 2);
			}

			//校验区域红色
			rec = m_data->listProj.at(curProg).listReg.at(i).rectRoiCheck;
			if (!arithClass::RectIsInPic(rec, m_showPic))
				continue;
			if (i == curReg)
			{
				cv::rectangle(m_showPic, rec, cv::Scalar(0, 0, 255), 2);
			}
			else
			{
				cv::rectangle(m_showPic, rec, cv::Scalar(255, 0, 0), 2);
			}
			
		}
	}
	if (!m_showPic.empty())
	{
		//先缩放m_showPic
		//arithClass::draw_changedPic(lab_pic, m_showPic,m_showPic, picScale);
		bool isCheck = ui.ckB_adjReg->isChecked();
		if (isCheck)
		{
			//适应窗口
			lab_pic->clear();
			lab_pic->resize(ui.sA_pic->size());
			picScale = arithClass::draw_pic(lab_pic, m_showPic);

		}
		else
		{
			lab_pic->clear();
			arithClass::draw_oriPic(lab_pic, m_showPic);
			picScale = 1;
		}

	}
		
}
bool QDialog_setting::CheckCurData(int & curProj, int & curReg, bool isNeedCheckReg)
{
	curProj = m_data->curProj;
	if (curProj < 0 || curProj >= m_data->listProj.size())
		return false;
	if (isNeedCheckReg)
	{
		curReg = m_data->listProj.at(curProj).curReg;
		if (curReg < 0 || curReg >= m_data->listProj.at(curProj).listReg.size())
			return false;
	}
	return true;
}
void QDialog_setting::on_ckB_adjReg_clicked()
{
	bool isChecked = ui.ckB_adjReg->isChecked();
	if (isChecked)
	{
		//适应窗口
		lab_pic->clear();
		lab_pic->resize(ui.sA_pic->size());
		picScale=arithClass::draw_pic(lab_pic, m_showPic);
	}
	else
	{
		lab_pic->clear();
		arithClass::draw_oriPic(lab_pic, m_showPic);
		picScale = 1;
	}
}
void QDialog_setting::on_projClicked()
{
	RenewPic();
}
void QDialog_setting::on_regClicked()
{
	RenewPic();
}
void QDialog_setting::on_setClicked(int curProj,int curReg,int pbType)
{
	drawRecType = pbType;
	m_isSetRoi = true;
}
void QDialog_setting::on_pB_sendClick_clicked()
{
	int sendX = ui.lE_x->text().toInt();
	int sendY = ui.lE_y->text().toInt();
	if (pWnd != nullptr)
	{
		QWinControl::SendWinLClick(pWnd,sendX, sendY);
	}
	else
	{
		QMessageBox::information(this, tr("提示"), tr("窗口句柄为空"), 0);
	}

}
void QDialog_setting::on_pB_grab_clicked()
{
	QString a = QString::fromLocal8Bit(m_data->winName.data());
	//HWND pWnd = ::FindWindowW(NULL, a.toStdWString().c_str());
	pWnd = QWinControl::GetWinHWND(a);
	if (pWnd == NULL)
	{
		QMessageBox::information(this, tr("提示"), tr("获取窗口失败"), 0);
		return;
	}
	QWinControl::GetMat2(pWnd, m_srcpic);
	//cv::namedWindow("srcpic", 1);
	//cv::imshow("srcpic", m_srcpic);

	//4通道转换成3通道
	if (m_srcpic.type() == CV_8UC4)
	{
		cv::cvtColor(m_srcpic, m_srcpic, cv::COLOR_BGRA2BGR);
	}

	//预处理
	//寻找图片缩少的比例系数
	arith_yuchuli ari;
	cv::Mat dstpic;
	std::vector<QVariant> res;
	ari.ProcessFun(m_srcpic, dstpic, res);
	if (res.size() != 1)
	{
		QMessageBox::information(this, tr("提示"), tr("预处理出错"), 0);
	}
	m_data->picScale = res.at(0).toDouble();
	//if (!dstpic.empty())
	//{
	//	cv::namedWindow("dstpic", 1);
	//	cv::imshow("dstpic", dstpic);
	//}
	if (m_srcpic.empty())
	{
		QDateTime time = QDateTime::currentDateTime();
		QString ss = time.toString("yyyy_mm_dd hh:mm:ss.zzz ") + tr("获取图片失败");
		QMessageBox::information(this, tr("提示"), tr("获取图片失败"), 0);
		//ui.textBrowser->append(ss);
		return;
	}

	//显示图片
	m_showPic = m_srcpic.clone();
	RenewPic();

}



void QDialog_setting::mousePressEvent(QMouseEvent * event)
{
	if (m_showPic.empty())
		return;
	lab2this = lab_pic->mapTo(this, lab_pic->pos());
	lab2this = lab2this- lab_pic->pos();
	mous2lab1 = event->pos() - lab2this;//鼠标点击时相对于lab的坐标,点击的位置
	//button返回事件按钮，buttons：返回按钮状态
	if (event->button() == Qt::LeftButton)
	{
		//获取坐标
		//目的是获取鼠标点击时相对于图像的坐标

		//判断点击的点是否在lab外
		ptIsInLab(mous2lab1,lab_pic);
		//用pic的size来推出位置
		
		int pty, ptx;
		if ((lab_pic->size().width() - m_showPic.cols)/2 > 0)
		{
			ptx = (lab_pic->size().width() - m_showPic.cols) / 2;
		}
		else
		{
			ptx = 0;
		}
		if ((lab_pic->size().height() - m_showPic.rows) / 2 > 0)
		{
			pty = (lab_pic->size().height() - m_showPic.rows) / 2;
		}
		else
		{
			pty = 0;
		}
		pic2lab.setX(ptx);
		pic2lab.setY(pty);
		mous2pic1 = mous2lab1 - pic2lab;

	}
	else if (event->button() == Qt::RightButton)
	{
		//移动图片
		//判断点是否在lab内
		//获取两个滚动条的位置
		Hvalue = ui.sA_pic->horizontalScrollBar()->value();
		Vvalue = ui.sA_pic->verticalScrollBar()->value();
		if (!ptIsInLab(mous2lab1, lab_pic))
		{
			isMoveLab = false;
		}
		else
		{
			isMoveLab = true;
		}
	}

}

void QDialog_setting::mouseReleaseEvent(QMouseEvent * event)
{
	if (m_showPic.empty())
		return;
	if (event->button() == Qt::LeftButton)
	{
		mous2lab2 = event->pos() - lab2this;
		ptIsInLab(mous2lab2, lab_pic);


		if (m_isSetRoi)
		{
			m_isSetRoi = false;
			//将其转换到图像坐标中
			mous2pic2 = mous2lab2 - pic2lab;
			cv::Rect roi = cv::Rect(mous2pic1.x(), mous2pic1.y(),( mous2pic2.x()- mous2pic1.x()),( mous2pic2.y() - mous2pic1.y()));
			
			if (arithClass::RectIsInPic(roi, m_showPic))
			{
				int curProj, curReg;
				if (CheckCurData(curProj, curReg))
				{
					std::stringstream ss;
					if (drawRecType == 0)
					{
						//检测区域
						m_data->listProj.at(curProj).listReg.at(curReg).rectRoiMap = roi;
						//将这个roi保存到tem文件中
						ss << QCoreApplication::applicationDirPath().toLocal8Bit().toStdString();
						ss << "/temPic/"
							<< curProj
							<< "_"
							<< curReg
							<< "_"
							<< drawRecType
							<< ".bmp";
						cv::Mat rotpic = m_srcpic(roi).clone();
						bool isSavePic = cv::imwrite(ss.str(), rotpic);
						if (isSavePic)
						{
							m_data->listProj.at(curProj).listReg.at(curReg).roiPicPathMap = ss.str();
							QMessageBox::information(this, tr("提示"), tr("保存roi成功"), 0);
						}
						else
						{
							QMessageBox::information(this, tr("提示"), tr("保存roi失败"), 0);
						}
						

					}
					else if (drawRecType == 1)
					{
						//点击区域
						m_data->listProj.at(curProj).listReg.at(curReg).rectRoiClick = roi;
						//不需要保存图片
					}
					else if (drawRecType==2)
					{
						//校验区域
						m_data->listProj.at(curProj).listReg.at(curReg).rectRoiCheck = roi;
						//保存图片
						ss << QCoreApplication::applicationDirPath().toLocal8Bit().toStdString();
						ss << "/temPic/"
							<< curProj
							<< "_"
							<< curReg
							<< "_"
							<< drawRecType
							<< ".bmp";
						cv::Mat rotpic = m_srcpic(roi).clone();
						bool isSavePic = cv::imwrite(ss.str(), rotpic);
						if (isSavePic)
						{
							m_data->listProj.at(curProj).listReg.at(curReg).roiPicPathCheck = ss.str();
							QMessageBox::information(this, tr("提示"), tr("保存roi成功"), 0);
						}
						else
						{
							QMessageBox::information(this, tr("提示"), tr("保存roi失败"), 0);
						}
					}
					m_data->listProj.at(curProj).tempW = m_srcpic.cols;
					m_data->listProj.at(curProj).tempH = m_srcpic.rows;

					RenewPic();
					ss.str("");
				}
			}

		}
		m_rect2lab = QRect(-1, -1, 0, 0);
		lab_pic->SetRect(m_rect2lab);


	}
	else if (event->button() == Qt::RightButton)
	{
		isMoveLab = false;
	}
}

void QDialog_setting::mouseMoveEvent(QMouseEvent * event)
{
	if (m_showPic.empty())
		return;
	if (event->buttons() == Qt::LeftButton)
	{
		//求出鼠标相当于与图片的坐标
		QPoint mous2lab = event->pos() - lab2this;
		ptIsInLab(mous2lab, lab_pic);
		//QPoint curPt = ui.labelShow->pos();
		m_rect2lab = QRect(mous2lab1.x(), mous2lab1.y(),
			mous2lab.x() - mous2lab1.x(), mous2lab.y() - mous2lab1.y());

		QPoint mous2pic = mous2lab - pic2lab;
		cv::Rect matrect = cv::Rect(mous2pic1.x(), mous2pic1.y(), (mous2pic.x() - mous2pic1.x()), (mous2pic.y() - mous2pic1.y()));
		lab_pic->SetRect(m_rect2lab, matrect);

	}
	else if (event->buttons() == Qt::RightButton)
	{
		if (isMoveLab)
		{
			QPoint mous2lab = event->pos() - lab2this;
			//lab_pic->move(lab2this + mous2lab - mous2lab1);
			//lab_pic->move(mous2lab - mous2lab1);

			//求出鼠标移动的矢量
			QPoint mousMove = mous2lab - mous2lab1;
			ui.sA_pic->horizontalScrollBar()->setValue(Hvalue - mousMove.x());
			ui.sA_pic->verticalScrollBar()->setValue(Vvalue - mousMove.y());

		}
	}
}

void QDialog_setting::resizeEvent(QResizeEvent * event)
{
	bool isChecked = ui.ckB_adjReg->isChecked();
	lab_pic->clear();
	lab_pic->resize(ui.sA_pic->size());
	if (isChecked)
	{
		picScale=arithClass::draw_pic(lab_pic, m_showPic);
	}
	else
	{
		picScale = 1;
		arithClass::draw_oriPic(lab_pic, m_showPic);
	}
}
