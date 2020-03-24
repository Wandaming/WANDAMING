#pragma once
#include <arithClass.h>
class arith_SystemCall :
	public arithClass
{
public:
	arith_SystemCall();
	~arith_SystemCall();
	//获取参数列表
	bool getValue(QStringList _listVal, bool _isDebug);
	//返回瑕疵的数目
	bool ProcessFun(const cv::Mat &srcpic, cv::Mat &dstpic, std::vector<QVariant> &qvRes);

	void GetTemMatList(const std::vector<cv::Mat> &listTem);
	void GetTemMat(const cv::Mat &Tem);
private:
	bool m_isDebug = false;

	cv::Mat temPic;
	//roi参数
	int roiX;
	int roiY;
	int roiW;
	int roiH;

	//目标图像的宽高
	int temPicW;
	int temPicH;

	//模板图片的位置
	std::string tempath;
	//匹配的阈值
	double templateThVal = 0.1;
	//是否取反
	bool isAnti = false;

	void templatePic(const cv::Mat &srcpic, const cv::Mat &temPic, std::vector<QVariant> &qvRes);
	void templatePic2(const cv::Mat &srcpic, const cv::Mat &temPic, std::vector<QVariant> &qvRes);
};

