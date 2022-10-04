#include "drawboard.h"
#include "qspinbox.h"
#include "qpushbutton.h"
#include "qdebug.h"
#include "qcolordialog.h"

DrawBoard::DrawBoard(QWidget *parent)
	: QMainWindow(parent)
{

	ui.setupUi(this);
	this->resize(900 , 600);
	QLabel * lab = new QLabel("线形",this);
	QComboBox *cmb = new QComboBox;
	cmb->addItem("直线");
	cmb->addItem("曲线");
	cmb->addItem("矩形");
	cmb->addItem("圆");

	ui.mainToolBar->setAllowedAreas(Qt::TopToolBarArea);
	ui.mainToolBar->addWidget(lab);
	ui.mainToolBar->addWidget(cmb);

	ui.mainToolBar->addSeparator();		//分隔符

	QLabel *lab1 = new QLabel("线宽",this);
	QSpinBox * spinbox = new QSpinBox();
	ui.mainToolBar->addWidget(lab1);
	ui.mainToolBar->addWidget(spinbox);

	ui.mainToolBar->addSeparator();
	QPushButton * color = new QPushButton("调色板");
	ui.mainToolBar->addWidget(color);

	ui.mainToolBar->addSeparator();
	QPushButton * clear = new QPushButton("清空");
	ui.mainToolBar->addWidget(clear);

	dp = new drawboardpanel();
	this->setCentralWidget(dp);

	//初始化信号槽
	qDebug() << connect(cmb , &QComboBox::currentTextChanged , dp , &drawboardpanel::setLineType);
	void (QSpinBox::*p)(int)= &QSpinBox::valueChanged;
	qDebug() << connect(spinbox, p, this , &DrawBoard::slotChangeLineWidth);
	qDebug() << connect(color, &QPushButton::clicked, [=]() {
		dp->c = QColorDialog::getColor();
	});

	qDebug() << connect(clear, &QPushButton::clicked, this, &DrawBoard::slotClere);
}


DrawBoard::~DrawBoard()
{
}

void DrawBoard::init()
{

}

void DrawBoard::slotChangeLineWidth(int lineWidth)
{
	dp->width = lineWidth;
}

void DrawBoard::slotClere()
{
	dp->pixmap->fill();
	update();
}


