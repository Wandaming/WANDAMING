#include "AutoPlay.h"

AutoPlay::AutoPlay(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	pQparamTem = new QParamTem(this);
	QVBoxLayout *layout=new QVBoxLayout(this);
	//layout->insertWidget(0,pQparamTem);
	layout->addWidget(pQparamTem);
	ui.frame_setReg->setLayout(layout);
}
AutoPlay::~AutoPlay()
{
	if (pQparamTem!=nullptr)
	{
		pQparamTem->deleteLater();
		pQparamTem = nullptr;
	}
}