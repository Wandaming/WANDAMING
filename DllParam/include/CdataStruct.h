#pragma once
#include<opencv2/opencv.hpp>
#include<algorithm>
struct SReg
{
	//矩形相对于与模板图像的位置
	//矩形中roi的保存路径
	std::string name="";
	std::string roiPicPath="";
	cv::Rect rectRoi=cv::Rect(0,0,0,0);

	
	void Save(cv::FileStorage &fs)
	{
		fs << "name" << name;
		fs << "roiPicPath" << roiPicPath;
		fs << "rectRoi" << rectRoi;
	}
	void Load(cv::FileNode &node)
	{
		node["name"] >> name;
		node["roiPicPath"] >> roiPicPath;
		node["rectRoi"] >> rectRoi;
	}

};

struct SProj
{
	//各个区域的信息
	//当前区域
	//模板图像的保存路径

	std::string name="";
	std::vector<SReg> listReg;
	int curReg = -1;
	std::string temPicPath="";

	void Save(cv::FileStorage &fs)
	{
		fs << "name" << name;
		fs << "curReg" << curReg;
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
	}
	void Load(cv::FileNode &node)
	{
		node["name"] >> name;
		node["curReg"] >> curReg;
		node["temPicPath"] >> temPicPath;
		for (auto it=node["listReg"].begin();it!=node["listReg"].end();it++)
		{
			SReg obj;
			obj.Load(*it);
			listReg.push_back(obj);
		}
	}

	bool AddReg()
	{
		SReg obj;
		listReg.push_back(obj);
		return true;
	}
	bool RemoveReg(int _curReg)
	{
		if (_curReg < 0 || _curReg >= listReg.size())
			return false;
		listReg.erase(listReg.begin() + _curReg, listReg.begin() + _curReg + 1);
		return true;
	}



	bool MoveUp(int _curReg)
	{
		if (_curReg <= 1)
			return false;
		reverse(listReg.begin() + _curReg - 1, listReg.begin() + _curReg);
		return true;
	}
	bool MoveDown(int _curReg)
	{
		if (_curReg >= listReg.size() - 1)
			return false;
		reverse(listReg.begin() + _curReg, listReg.begin() + _curReg +1);
		return true;
	}
	bool InsertReg(int _curReg,SReg obj)
	{
		if (_curReg < 0 || _curReg >= listReg.size())
			return false;
		listReg.insert(listReg.begin() + _curReg, obj);
		return true;
	}


};


class CdataStruct
{
public:
	CdataStruct();
	~CdataStruct();
	std::vector<SProj> listProj;
	int curProj = -1;

	bool DataRead();
	bool DataWrite();

	cv::FileStorage m_fs;
	bool m_isRead = false;
	bool m_isWrite = false;

	bool AddProj();
	bool RemovePorj(int _curProj);


};

