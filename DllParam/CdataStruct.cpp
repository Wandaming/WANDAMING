#include "include/CdataStruct.h"

#include<sstream>

CdataStruct::CdataStruct()
{
	listProj.swap(std::vector<SProj>());
}


CdataStruct::~CdataStruct()
{
}
bool CdataStruct::AddProj()
{
	SProj obj;
	obj.name = "newProj";
	listProj.push_back(obj);
	return true;
}
bool CdataStruct::RemovePorj(int _curProj)
{
	if (_curProj < 0 || _curProj >= listProj.size())
		return false;
	listProj.erase(listProj.begin() + _curProj, listProj.begin() + _curProj + 1);
	curProj--;
	return true;
}
bool CdataStruct::DataRead(std::string path)
{
	//��������ֻ��Ҫһ������
	if (m_isRead)
		return m_isRead;
	std::stringstream ss_path;
	ss_path << path << "/data_type.xml";
	m_fs.open(ss_path.str(), cv::FileStorage::READ&& cv::FileStorage::FORMAT_XML);
	ss_path.str("");
	bool op;
	op = m_fs.isOpened();
	if (op)
	{
		//��������
		cv::FileNode node = m_fs["listProj"];
		for (auto it = node.begin(); it != node.end(); it++)
		{
			SProj ob_type;
			ob_type.Load(*it);//�ӵ������ж�ȡnode�ĵ�ַ����������load�С�
			listProj.push_back(ob_type);
		}



		m_fs["curProj"] >> curProj;
		m_fs["winName"] >> winName;
		m_fs["randomTime"] >> randomTime;
		m_fs["picScale"] >> picScale;
		m_fs.release();
		m_isRead = true;
	}
	return m_isRead;
}
bool CdataStruct::DataWrite(std::string path)
{
	//��������
	//int count= typeName.size();
	std::stringstream ss_path;
	ss_path << path << "/data_type.xml";
	m_fs.open(ss_path.str(), cv::FileStorage::WRITE&& cv::FileStorage::FORMAT_XML);
	ss_path.str("");
	bool op;
	op = m_fs.isOpened();
	if (op)
	{
		//����ʱ��Ҫһ������������
		//��{����map�Ķ�ȡ����[����vector�Ķ�ȡ,�˴���Ȼ��vector�����������ֵĸ�ʽΪmap��ʽ��������"{"�ȽϺ�
		//������"{"��"["û������
		//m_fs << "TypeOfWire" << "[";//����д�������ַ����ַ�֮��Ҳ���ܳ��ֿո�
		//std::vector<Stype>::iterator iter_listType = listType.begin();
		//for (iter_listType; iter_listType != listType.end(); iter_listType++)
		//{
		//	m_fs << "{";
		//	listType.at(iter_listType - listType.begin()).Save(m_fs);
		//	m_fs << "}";
		//}
		//m_fs << "]";

		m_fs << "listProj" << "[";
		auto iter_listG1Type = listProj.begin();
		for (iter_listG1Type; iter_listG1Type != listProj.end(); iter_listG1Type++)
		{
			m_fs << "{";
			listProj.at(iter_listG1Type - listProj.begin()).Save(m_fs);
			m_fs << "}";
		}
		m_fs << "]";

		m_fs << "curProj" << curProj;
		m_fs << "winName" << winName;
		m_fs << "randomTime" << randomTime;
		m_fs << "picScale" << picScale;
		m_fs.release();
		m_isWrite = true;
	}
	else
	{
		m_isWrite = false;
	}
	return m_isWrite;
}

