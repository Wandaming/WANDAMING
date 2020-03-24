#include "QMyLabel.h"
#include<qpainter.h>
QMyLabel::QMyLabel(QWidget *parent)
	: QLabel(parent)
{
}

QMyLabel::~QMyLabel()
{
}

void QMyLabel::SetRect(QRect srcRect, cv::Rect matRect)
{
	m_rect = srcRect;
	m_matRect = matRect;
	update();
}


void QMyLabel::paintEvent(QPaintEvent *event)
{
	QLabel::paintEvent(event);

	QPainter p(this);
	p.setPen(QPen(QColor(0, 0, 255), 1));
	if (m_rect.width() > 0 & m_rect.height() > 0)
	{
		//p.setPen(pen);
		//p.setBrush(brush);
		p.drawRect(m_rect);
		QString str = QString::number(m_matRect.x) + "," + QString::number(m_matRect.y) + "," +
			QString::number(m_matRect.width) + "," + QString::number(m_matRect.height);
		p.drawText(QPoint(m_rect.x(), m_rect.y()), str);
	}

	if (bShowColor)
	{
		QString str = QString::number(color.red()) + "," + QString::number(color.green()) + "," +
			QString::number(color.blue());
		p.drawText(QPoint(curPt.x(), curPt.y()), str);
	}

}
