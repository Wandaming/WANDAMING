#include "arith_yuchuli.h"



arith_yuchuli::arith_yuchuli()
{
}


arith_yuchuli::~arith_yuchuli()
{
}

bool arith_yuchuli::getValue(QStringList _listVal, bool _isDebug)
{

	return true;
}

bool arith_yuchuli::ProcessFun(const cv::Mat & srcpic, cv::Mat & dstpic, std::vector<QVariant>& qvRes)
{
	//对图像做反二值化
	qvRes.swap(std::vector<QVariant>(1));
	cv::Mat img; 
	int aaa = srcpic.type();
	if (srcpic.type() == CV_8UC1)
	{
		img = srcpic.clone();
	}
	else if (srcpic.type() == CV_8UC3)
	{
		cv::cvtColor(srcpic, img, cv::COLOR_BGR2GRAY);
	}
	else if (srcpic.type() == CV_8UC4)
	{
		cv::cvtColor(srcpic, img, cv::COLOR_BGRA2GRAY);
	}
	cv::Mat midpic;
	cv::threshold(img, midpic, 2, 255, 1);

	//寻找最大的轮廓
	std::vector<std::vector<cv::Point>> contAll;
	cv::findContours(midpic, contAll, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
	if (contAll.size() == 0)
	{
		dstpic = srcpic.clone();
		qvRes.at(0).setValue(1);
		return true;
	}
	//寻找右下角的点
	int contId = 0;
	bool isMubiao = false;
	for (int i = 0; i < contAll.size(); i++)
	{
		isMubiao = false;
		for (int j = 0; j < contAll.at(i).size(); j++)
		{
			if (contAll.at(i).at(j).x == midpic.cols - 1 && contAll.at(i).at(j).y == midpic.rows - 1)
			{
				isMubiao = true;
				contId = i;
				break;
			}
		}
		if (isMubiao)
		{
			break;
		}
	}
	cv::Mat mask = cv::Mat(midpic.size(), midpic.type());
	mask = 255;
	cv::drawContours(mask, contAll, contId, cv::Scalar(0), -1);
	contAll.swap(std::vector<std::vector<cv::Point>>());

	cv::findContours(mask, contAll, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
	if (contAll.size() != 1)
		return true;
	cv::Rect roi = cv::boundingRect(contAll.at(0));
	dstpic = srcpic(roi).clone();
	double wscale = (double)srcpic.cols / dstpic.cols;
	double hscale = (double)srcpic.rows / dstpic.rows;
	qvRes.at(0).setValue((wscale + hscale) / 2);
	int a = 0;
	return true;
}

//void arith_yuchuli::GetTemMat(const cv::Mat & tem)
//{
//}
//
//void arith_yuchuli::GetTemMatList(const std::vector<cv::Mat>& listTem)
//{
//}
