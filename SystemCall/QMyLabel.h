#pragma once

#include <QLabel>
#include <opencv2/opencv.hpp>

class  QMyLabel : public QLabel
{
	Q_OBJECT

public:
	QMyLabel(QWidget *parent=nullptr);
	~QMyLabel();
	void SetRect(QRect, cv::Rect=cv::Rect(-1,-1,0,0));
	QColor color;
	QPoint curPt;
	bool bShowColor = false;
private:
	QRect m_rect;
	cv::Rect m_matRect;
protected:
	void paintEvent(QPaintEvent *);//ÖØ»­ÊÂ¼þ
};
