#include "include/QWinControl.h"
#include<qmessagebox.h>
#include<QScreen>
#include<QPixmap>
#include<qguiapplication.h>
#include<arithClass.h>
#include<qdebug.h>
QWinControl::QWinControl(QObject *parent)
	: QObject(parent)
{
}

QWinControl::~QWinControl()
{
}
void QWinControl::GetMat(HWND hWnd,cv::Mat &srcpic)
{
	//extern int m_windowFlag;
	HDC hDC = ::GetWindowDC(hWnd);
	HDC hMemDC = ::CreateCompatibleDC(hDC);
	RECT rc;
	::GetWindowRect(hWnd, &rc);
	BITMAP bitmap = { 0 };
	HBITMAP hBitmap = ::CreateCompatibleBitmap(hDC, rc.right - rc.left, rc.bottom - rc.top);
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hMemDC, hBitmap);

	//::BitBlt(hMemDC,0,0,rc.right-rc.left,rc.bottom-rc.top,hDC,0,0,SRCCOPY);
	::PrintWindow(hWnd, hMemDC, 0);//获取截图

	::GetObject(hBitmap, sizeof(BITMAP), &bitmap);//猜测这个地方，图片已经赋值给bitmap完毕了

	/*将bitmap格式图片转换为IplImage，便于处理*/
	int depth = (bitmap.bmBitsPixel == 1) ? IPL_DEPTH_1U : IPL_DEPTH_8U;
	int nChannels = (bitmap.bmBitsPixel == 1) ? 1 : bitmap.bmBitsPixel / 8;
	IplImage* img = cvCreateImage(cvSize(bitmap.bmWidth, bitmap.bmHeight), depth, nChannels);
	BYTE *pBuffer = new BYTE[bitmap.bmHeight*bitmap.bmWidth*nChannels];
	GetBitmapBits(hBitmap, bitmap.bmHeight*bitmap.bmWidth*nChannels, pBuffer);
	memcpy(img->imageData, pBuffer, bitmap.bmHeight*bitmap.bmWidth*nChannels);
	delete[]pBuffer;
	IplImage *dst = cvCreateImage(cvGetSize(img), img->depth, 3);
	cvCvtColor(img, dst, CV_BGRA2BGR);
	cvReleaseImage(&img);

	::SelectObject(hMemDC, hOldBmp);
	::DeleteObject(hBitmap);
	::DeleteObject(hMemDC);
	::ReleaseDC(hWnd, hDC);

	//if (1 == m_windowFlag)
	//{
	//	cv::Mat returnPic = cv::cvarrToMat(dst, true)(cv::Rect(0, 18, 856, 538));
	//	cvReleaseImage(&dst);
	//	return returnPic;
	//}
	//else
	{
		srcpic = cv::cvarrToMat(dst, true);
		cvReleaseImage(&dst);
	}
}

void QWinControl::GetMat2(HWND hWnd, cv::Mat & _srcpic)
{
	QScreen *screen = QGuiApplication::primaryScreen();
	int winId = (WId)hWnd;
	QPixmap pixmap = screen->grabWindow(winId);//videoWidget->winId()这是你要截图的控件的winID，主窗口为0
	//pixmap.save("D:/Qt5screen.jpg", "jpg");
	_srcpic=arithClass::QImage2cvMat(pixmap.toImage());
}

HWND QWinControl::GetWinHWND(QString winname)
{
	return ::FindWindowW(NULL, winname.toStdWString().c_str());

}



void QWinControl::SendWinLClick(HWND win, int moveX,int moveY)
{
	if (win == nullptr)
		return;
	LPARAM frightPoint = MAKELPARAM(moveX, moveY);

	::SendMessage(win, WM_LBUTTONDOWN, MK_LBUTTON, frightPoint);
	::SendMessage(win, WM_LBUTTONUP, NULL, frightPoint);
	//Sleep(200);
	//SendMessage(win, WM_LBUTTONDOWN, MK_LBUTTON, MAKELONG(moveX, moveY));
	//SendMessage(win, WM_LBUTTONUP, NULL, MAKELONG(moveX, moveY));

	//QWidget *gameWindow = QWidget::find((WId)win);
	//if (gameWindow == nullptr)
	//	return;
	//qDebug() << (QString)(gameWindow->windowTitle());

	//QPoint *pos = new QPoint(moveX, moveY);
	//QMouseEvent *clickEvent = new QMouseEvent(QEvent::MouseButtonPress, *pos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
	//QApplication::sendEvent(gameWindow, clickEvent);
}
