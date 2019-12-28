#include "include/CdataStruct.h"



CdataStruct::CdataStruct()
{
}


CdataStruct::~CdataStruct()
{
}
bool CdataStruct::AddProj()
{
	SProj obj;
	listProj.push_back(obj);
	return true;
}
bool CdataStruct::RemovePorj(int _curProj)
{
	if (_curProj < 0 || _curProj >= listProj.size())
		return false;
	listProj.erase(listProj.begin() + _curProj, listProj.begin() + _curProj + 1);
	return true;
}
bool CdataStruct::DataRead()
{
	//载入数据只需要一次载入
	if (m_isRead)
		return m_isRead;
	m_fs.open("data_type.xml", cv::FileStorage::READ&& cv::FileStorage::FORMAT_XML);
	bool op;
	op = m_fs.isOpened();
	if (op)
	{
		//载入数据
		cv::FileNode node = m_fs["listProj"];
		for (auto it = node.begin(); it != node.end(); it++)
		{
			SProj ob_type;
			ob_type.Load(*it);//从迭代器中读取node的地址，将它传入load中。
			listProj.push_back(ob_type);
		}



		m_fs["curProj"] >> curProj;
		m_fs.release();
		m_isRead = true;
	}
	return m_isRead;
}
bool CdataStruct::DataWrite()
{
	//参数保存
	//int count= typeName.size();
	m_fs.open("data_type.xml", cv::FileStorage::WRITE&& cv::FileStorage::FORMAT_XML);
	bool op;
	op = m_fs.isOpened();
	if (op)
	{
		//保存时需要一个数量的数据
		//“{”是map的读取，“[”是vector的读取,此处虽然是vector容器，但保持的格式为map格式，所以用"{"比较好
		//本质上"{"和"["没有区别
		//m_fs << "TypeOfWire" << "[";//不能写入中文字符，字符之间也不能出现空格
		//std::vector<Stype>::iterator iter_listType = listType.begin();
		//for (iter_listType; iter_listType != listType.end(); iter_listType++)
		//{
		//	m_fs << "{";
		//	listType.at(iter_listType - listType.begin()).Save(m_fs);
		//	m_fs << "}";
		//}
		//m_fs << "]";

		m_fs << "G1Type" << "[";
		auto iter_listG1Type = listProj.begin();
		for (iter_listG1Type; iter_listG1Type != listProj.end(); iter_listG1Type++)
		{
			m_fs << "{";
			listProj.at(iter_listG1Type - listProj.begin()).Save(m_fs);
			m_fs << "}";
		}
		m_fs << "]";

		m_fs << "curProj" << curProj;
		m_fs.release();
		m_isWrite = true;
	}
	else
	{
		m_isWrite = false;
	}
	return m_isWrite;
}

