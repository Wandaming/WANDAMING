#include "arith_SystemCall.h"
#include<atomic>

extern std::atomic_bool g_isStop;
arith_SystemCall::arith_SystemCall()
{
}


arith_SystemCall::~arith_SystemCall()
{
}

bool arith_SystemCall::getValue(QStringList _listVal, bool _isDebug)
{
	roiX = _listVal.at(0).toInt();
	roiY = _listVal.at(1).toInt();
	roiW = _listVal.at(2).toInt();
	roiH = _listVal.at(3).toInt();
	tempath = _listVal.at(4).toLocal8Bit().toStdString();
	templateThVal= _listVal.at(5).toDouble();
	isAnti= _listVal.at(6).toInt();

	temPicW= _listVal.at(7).toInt();
	temPicH= _listVal.at(8).toInt();


	return true;
}

bool arith_SystemCall::ProcessFun(const cv::Mat & srcpic, cv::Mat & dstpic, std::vector<QVariant>& qvRes)
{
	//清空信息列表
	//初始化窗口
	cv::destroyAllWindows();
	qvRes.swap(std::vector<QVariant>(2));//将结果列表清空
	//将输入的图像与目标图像进行比较，将输入图像的大小转变为目标图像的大小
	//选择需要进行匹配的roi，使用matTemplate进行匹配，如果所得结果大于某个值
	//则说明匹配成功，否则失败，输出结果
	if (srcpic.empty())
		return false;
	cv::Mat Img;
	if (srcpic.type() == CV_8UC4)
	{
		cv::cvtColor(srcpic, Img, cv::COLOR_BGRA2BGR);
	}
	else
	{
		Img = srcpic.clone();
	}

	cv::Rect roi = cv::Rect(roiX, roiY, roiW, roiH);
	if(Img.cols!= temPicW|| Img.rows!= temPicH)
		cv::resize(Img, Img,cv::Size(temPicW,temPicH));

	if (!RectIsInPic(roi, Img))
		return false;
	cv::Mat roiPic = Img(roi);


	if (temPic.empty())
		return false;
	//templatePic(roiPic, temPic, qvRes);
	templatePic2(roiPic, temPic, qvRes);
	return true;
}

void arith_SystemCall::GetTemMatList(const std::vector<cv::Mat>& listTem)
{
}

void arith_SystemCall::GetTemMat(const cv::Mat & Tem)
{
	temPic = Tem;
}


void arith_SystemCall::templatePic(const cv::Mat & srcpic, const cv::Mat & tempic, std::vector<QVariant>& qvRes)
{

	//步骤三：匹配，最后一个参数为匹配方式，共有6种，详细请查阅函数介绍
	cv::Mat dstImg/* = cv::Mat(1, 1, CV_32FC1)*/;
	//cv::namedWindow("srcpic", 0);
	//cv::imshow("srcpic", srcpic);
	//cv::namedWindow("tempic", 0);
	//cv::imshow("tempic", tempic);
	//cv::waitKey(0);
	cv::matchTemplate(srcpic, tempic, dstImg, 1);
	//步骤五：获取最大或最小匹配系数
	//首先是从得到的 输出矩阵中得到 最大或最小值（平方差匹配方式是越小越好，所以在这种方式下，找到最小位置）
	//找矩阵的最小位置的函数是 minMaxLoc函数
	cv::Point minPoint;
	cv::Point maxPoint;
	double minVal = 0;
	double maxVal = 0;
	cv::minMaxLoc(dstImg, &minVal, &maxVal, &minPoint, &maxPoint);
	
	if (!isAnti)
	{
		if (minVal <= templateThVal)
		{
			qvRes.at(0) = 1;
		}
		else
		{
			qvRes.at(0) = 0;
		}
	}
	else
	{
		if (minVal <= templateThVal)
		{
			qvRes.at(0) = 0;
		}
		else
		{
			qvRes.at(0) = 1;
		}
	}
	qvRes.at(1) = minVal;

}

void arith_SystemCall::templatePic2(const cv::Mat & srcpic, const cv::Mat & temPic, std::vector<QVariant>& qvRes)
{
	cv::Mat screen64, template64;
	cv::Mat screenPic64, templatePic64;
	cv::resize(srcpic, screenPic64, cv::Size(8, 8), 0, 0, cv::INTER_NEAREST);
	cv::resize(temPic, templatePic64, cv::Size(8, 8), 0, 0, cv::INTER_NEAREST);
	if(screenPic64.channels() == 3)
		cv::cvtColor(screenPic64, screen64, CV_BGR2GRAY);
	if(templatePic64.channels() == 3)
		cv::cvtColor(templatePic64, template64, CV_BGR2GRAY);

	int iAvg1 = 0, iAvg2 = 0;
	int arr1[64], arr2[64];



	for (int i = 0; i < 8; i++)
	{
		uchar* data1 = screen64.ptr<uchar>(i);
		uchar* data2 = template64.ptr<uchar>(i);

		int tmp = i * 8;

		for(int j = 0;j < 8;j++)
		{
			int tmp1 = tmp + j;

			arr1[tmp1] = data1[j] * 4 / 4;
			arr2[tmp1] = data2[j] * 4 / 4;

			iAvg1 += arr1[tmp1];
			iAvg2 += arr2[tmp1];
		}
	}

	iAvg1 /= 64;
	iAvg2 /= 64;

	for(int i= 0;i<64;i++)
	{
		arr1[i] = (arr1[i] >= iAvg1) ? 1 : 0;
		arr2[i] = (arr2[i] >= iAvg2) ? 1 : 0;
	}

	volatile int ll = 0;


	for(int i=0;i<64;i++)
	{
		if(arr1[i] == arr2[i])
		{
			ll++;
		}
	}
	//double a= (ll) / 64.0;
	//if(a>rate)
	//{
	//	return true;
	//}

	///*screen64.release();
	//template64.release();
	//screenPic64.release();
	//templatePic64.release();*/
	//return false;

	double minVal = (ll) / 64.0;
	//大于匹配阈值时，代表两个图像时相似的

	if (!isAnti)
	{
		if (minVal >= templateThVal)
		{
			qvRes.at(0) = 1;
		}
		else
		{
			qvRes.at(0) = 0;
		}
	}
	else
	{
		if (minVal >= templateThVal)
		{
			qvRes.at(0) = 0;
		}
		else
		{
			qvRes.at(0) = 1;
		}
	}
	qvRes.at(1) = minVal;

}
