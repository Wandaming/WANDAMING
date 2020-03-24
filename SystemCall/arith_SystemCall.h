#pragma once
#include <arithClass.h>
class arith_SystemCall :
	public arithClass
{
public:
	arith_SystemCall();
	~arith_SystemCall();
	//��ȡ�����б�
	bool getValue(QStringList _listVal, bool _isDebug);
	//����覴õ���Ŀ
	bool ProcessFun(const cv::Mat &srcpic, cv::Mat &dstpic, std::vector<QVariant> &qvRes);

	void GetTemMatList(const std::vector<cv::Mat> &listTem);
	void GetTemMat(const cv::Mat &Tem);
private:
	bool m_isDebug = false;

	cv::Mat temPic;
	//roi����
	int roiX;
	int roiY;
	int roiW;
	int roiH;

	//Ŀ��ͼ��Ŀ��
	int temPicW;
	int temPicH;

	//ģ��ͼƬ��λ��
	std::string tempath;
	//ƥ�����ֵ
	double templateThVal = 0.1;
	//�Ƿ�ȡ��
	bool isAnti = false;

	void templatePic(const cv::Mat &srcpic, const cv::Mat &temPic, std::vector<QVariant> &qvRes);
	void templatePic2(const cv::Mat &srcpic, const cv::Mat &temPic, std::vector<QVariant> &qvRes);
};

