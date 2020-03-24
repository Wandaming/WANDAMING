#pragma once
#include<opencv2/opencv.hpp>
#include<algorithm>
#include "../dllparam_global.h"
//每个节点的内容
struct SReg
{
	//矩形相对于与模板图像的位置
	//矩形中roi的保存路径
	std::string name="";
	//检测参数
	std::string roiPicPathMap="";
	cv::Rect rectRoiMap = cv::Rect(-1, -1, 0, 0);
	double mapVal = 0.8;
	bool isAntiMap = false;
	//点击参数
	cv::Rect rectRoiClick = cv::Rect(-1, -1, 0, 0);
	bool isNotClick = false;
	//校验参数
	std::string roiPicPathCheck = "";
	cv::Rect rectRoiCheck = cv::Rect(-1, -1, 0, 0);
	double checkVal = 0.8;
	bool isAntiCheck = true;

	//检测到目标对象是否需要鸣笛
	bool isNeedBlow = false;

	void Save(cv::FileStorage &fs)
	{
		fs << "name" << name;
		//检测参数
		fs << "roiPicPathMap" << roiPicPathMap;
		fs << "rectRoiMap" << rectRoiMap;
		fs << "mapVal" << mapVal;
		fs << "isAntiMap" << isAntiMap;
		//点击参数
		fs << "rectRoiClick" << rectRoiClick;
		fs << "isNotClick" << isNotClick;
		//检验参数
		fs << "roiPicPathCheck" << roiPicPathCheck;
		fs << "rectRoiCheck" << rectRoiCheck;
		fs << "checkVal" << checkVal;
		fs << "isAntiCheck" << isAntiCheck;
		//是否需要鸣笛
		fs << "isNeedBlow" << isNeedBlow;
	}
	void Load(cv::FileNode &node)
	{
		node["name"] >> name;
		//检测参数
		node["roiPicPathMap"] >> roiPicPathMap;
		node["rectRoiMap"] >> rectRoiMap;
		node["mapVal"] >> mapVal;
		node["isAntiMap"] >> isAntiMap;
		//点击参数
		node["rectRoiClick"] >> rectRoiClick;
		node["isNotClick"] >> isNotClick;
		//校验参数
		node["roiPicPathCheck"] >> roiPicPathCheck;
		node["rectRoiCheck"] >> rectRoiCheck;
		node["checkVal"] >> checkVal;
		node["isAntiCheck"] >> isAntiCheck;
		//是否需要名都
		node["isNeedBlow"] >> isNeedBlow;
	}

};


//项目
struct SProj
{
	//各个区域的信息
	//当前区域
	//模板图像的保存路径

	std::string name="";
	//区域检测列表
	std::vector<SReg> listReg;//子节点
	int curReg = -1;
	int checkTimesTh = 200;//检测次数的阈值

	//项目特征检测列表
	//每一个区域都需要优先检测一下列表
	std::vector<SReg> listOther;
	int curOther = -1;

	std::string temPicPath="";
	int tempH;
	int tempW;

	void Save(cv::FileStorage &fs)
	{
		fs << "name" << name;
		fs << "curReg" << curReg;
		fs << "checkTimesTh" << checkTimesTh;
		fs << "temPicPath" << temPicPath;
		fs << "listReg" << "[";//不能写入中文字符，字符之间也不能出现空格
		auto iter_list_pro = listReg.begin();
		for (iter_list_pro; iter_list_pro != listReg.end(); iter_list_pro++)
		{
			fs << "{";
			listReg.at(iter_list_pro - listReg.begin()).Save(fs);
			fs << "}";
		}
		fs << "]";

		fs << "listOther" << "[";
		iter_list_pro = listOther.begin();
		for (iter_list_pro; iter_list_pro != listOther.end(); iter_list_pro++)
		{
			fs << "{";
			listOther.at(iter_list_pro - listOther.begin()).Save(fs);
			fs << "}";
		}
		fs << "]";
		fs << "curOther" << curOther;
		fs << "tempH" << tempH;
		fs << "tempW" << tempW;

	}
	void Load(cv::FileNode &node)
	{
		node["name"] >> name;
		node["curReg"] >> curReg;
		node["checkTimesTh"] >> checkTimesTh;
		node["temPicPath"] >> temPicPath;
		for (auto it=node["listReg"].begin();it!=node["listReg"].end();it++)
		{
			SReg obj;
			obj.Load(*it);
			listReg.push_back(obj);
		}

		for (auto it = node["listOther"].begin(); it != node["listOther"].end(); it++)
		{
			SReg obj;
			obj.Load(*it);
			listOther.push_back(obj);
		}
		node["curOther"] >> curOther;

		node["tempH"] >> tempH;
		node["tempW"] >> tempW;
	}

	bool AddReg()
	{
		SReg obj;
		obj.name = "newReg";
		listReg.push_back(obj);
		return true;
	}
	bool RemoveReg(int _curReg)
	{
		if (_curReg < 0 || _curReg >= listReg.size())
			return false;
		listReg.erase(listReg.begin() + _curReg, listReg.begin() + _curReg + 1);
		curReg--;
		return true;
	}



	bool MoveUp(int _curReg)
	{
		if (_curReg < 1|| _curReg>= listReg.size())
			return false;
		SReg obj = listReg.at(_curReg);
		listReg.at(_curReg) = listReg.at(_curReg - 1);
		listReg.at(_curReg - 1) = obj;
		curReg--;
		return true;
	}
	bool MoveDown(int _curReg)
	{
		if (_curReg<0||_curReg >= listReg.size() - 1)
			return false;
		SReg obj = listReg.at(_curReg);
		listReg.at(_curReg) = listReg.at(_curReg + 1);
		listReg.at(_curReg + 1) = obj;
		curReg++;
		return true;
	}
	bool InsertReg(int _curReg)
	{
		if (_curReg < 0 || _curReg >= listReg.size())
			return false;
		SReg obj;
		obj.name = "newReg";
		listReg.insert(listReg.begin() + _curReg, obj);
		return true;
	}


};


class DLLPARAM_EXPORT CdataStruct
{
public:
	CdataStruct();
	~CdataStruct();
	std::vector<SProj> listProj;
	int curProj = -1;
	int randomTime = 500;//毫秒
	double picScale = 0;

	int count = 0;//计数用

	std::string winName = "";

	bool DataRead(std::string);
	bool DataWrite(std::string);

	cv::FileStorage m_fs;
	bool m_isRead = false;
	bool m_isWrite = false;

	bool AddProj();
	bool RemovePorj(int _curProj);


};

