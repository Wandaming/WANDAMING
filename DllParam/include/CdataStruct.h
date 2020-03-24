#pragma once
#include<opencv2/opencv.hpp>
#include<algorithm>
#include "../dllparam_global.h"
//ÿ���ڵ������
struct SReg
{
	//�����������ģ��ͼ���λ��
	//������roi�ı���·��
	std::string name="";
	//������
	std::string roiPicPathMap="";
	cv::Rect rectRoiMap = cv::Rect(-1, -1, 0, 0);
	double mapVal = 0.8;
	bool isAntiMap = false;
	//�������
	cv::Rect rectRoiClick = cv::Rect(-1, -1, 0, 0);
	bool isNotClick = false;
	//У�����
	std::string roiPicPathCheck = "";
	cv::Rect rectRoiCheck = cv::Rect(-1, -1, 0, 0);
	double checkVal = 0.8;
	bool isAntiCheck = true;

	//��⵽Ŀ������Ƿ���Ҫ����
	bool isNeedBlow = false;

	void Save(cv::FileStorage &fs)
	{
		fs << "name" << name;
		//������
		fs << "roiPicPathMap" << roiPicPathMap;
		fs << "rectRoiMap" << rectRoiMap;
		fs << "mapVal" << mapVal;
		fs << "isAntiMap" << isAntiMap;
		//�������
		fs << "rectRoiClick" << rectRoiClick;
		fs << "isNotClick" << isNotClick;
		//�������
		fs << "roiPicPathCheck" << roiPicPathCheck;
		fs << "rectRoiCheck" << rectRoiCheck;
		fs << "checkVal" << checkVal;
		fs << "isAntiCheck" << isAntiCheck;
		//�Ƿ���Ҫ����
		fs << "isNeedBlow" << isNeedBlow;
	}
	void Load(cv::FileNode &node)
	{
		node["name"] >> name;
		//������
		node["roiPicPathMap"] >> roiPicPathMap;
		node["rectRoiMap"] >> rectRoiMap;
		node["mapVal"] >> mapVal;
		node["isAntiMap"] >> isAntiMap;
		//�������
		node["rectRoiClick"] >> rectRoiClick;
		node["isNotClick"] >> isNotClick;
		//У�����
		node["roiPicPathCheck"] >> roiPicPathCheck;
		node["rectRoiCheck"] >> rectRoiCheck;
		node["checkVal"] >> checkVal;
		node["isAntiCheck"] >> isAntiCheck;
		//�Ƿ���Ҫ����
		node["isNeedBlow"] >> isNeedBlow;
	}

};


//��Ŀ
struct SProj
{
	//�����������Ϣ
	//��ǰ����
	//ģ��ͼ��ı���·��

	std::string name="";
	//�������б�
	std::vector<SReg> listReg;//�ӽڵ�
	int curReg = -1;
	int checkTimesTh = 200;//����������ֵ

	//��Ŀ��������б�
	//ÿһ��������Ҫ���ȼ��һ���б�
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
		fs << "listReg" << "[";//����д�������ַ����ַ�֮��Ҳ���ܳ��ֿո�
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
	int randomTime = 500;//����
	double picScale = 0;

	int count = 0;//������

	std::string winName = "";

	bool DataRead(std::string);
	bool DataWrite(std::string);

	cv::FileStorage m_fs;
	bool m_isRead = false;
	bool m_isWrite = false;

	bool AddProj();
	bool RemovePorj(int _curProj);


};

