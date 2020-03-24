#pragma once
#include <arithClass.h>
class arith_yuchuli :
	public arithClass
{
public:
	arith_yuchuli();
	~arith_yuchuli();
	//获取参数列表
	bool getValue(QStringList _listVal, bool _isDebug);
	//返回瑕疵的数目
	bool ProcessFun(const cv::Mat &srcpic, cv::Mat &dstpic, std::vector<QVariant> &qvRes);
	//void GetTemMatList(const std::vector<cv::Mat> &listTem);
 //   void GetTemMat(const cv::Mat &tem);
private:
	bool m_debug = false;
};

