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
	QLabel * lab = new QLabel("����",this);
	QComboBox *cmb = new QComboBox;
	cmb->addItem("ֱ��");
	cmb->addItem("����");
	cmb->addItem("����");
	cmb->addItem("Բ");

	ui.mainToolBar->setAllowedAreas(Qt::TopToolBarArea);
	ui.mainToolBar->addWidget(lab);
	ui.mainToolBar->addWidget(cmb);

	ui.mainToolBar->addSeparator();		//�ָ���

	QLabel *lab1 = new QLabel("�߿�",this);
	QSpinBox * spinbox = new QSpinBox();
	ui.mainToolBar->addWidget(lab1);
	ui.mainToolBar->addWidget(spinbox);

	ui.mainToolBar->addSeparator();
	QPushButton * color = new QPushButton("��ɫ��");
	ui.mainToolBar->addWidget(color);

	ui.mainToolBar->addSeparator();
	QPushButton * clear = new QPushButton("���");
	ui.mainToolBar->addWidget(clear);

	dp = new drawboardpanel();
	this->setCentralWidget(dp);

	//��ʼ���źŲ�
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


