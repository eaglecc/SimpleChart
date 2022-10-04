#include "drawboardpanel.h"

drawboardpanel::drawboardpanel(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//Ĭ������
	lineType = QString("ֱ��");
	c = Qt::yellow;
	width = 1;
	this->resize(900 , 600);

	pixmap = new QPixmap(this->size());
	fpixmap = new QPixmap(this->size());
	pixmap->fill(Qt::white);
	fpixmap->fill(Qt::white);
}

drawboardpanel::~drawboardpanel()
{
}

void drawboardpanel::paintEvent(QPaintEvent * event)
{
	QPainter p(this);
	p.drawPixmap(0,0,*pixmap);
}

void drawboardpanel::mousePressEvent(QMouseEvent * event)
{
	startPoint = event->pos();
	*fpixmap = *pixmap;
}

void drawboardpanel::mouseReleaseEvent(QMouseEvent * event)
{
	//*pixmap = *fpixmap;
	//endPoint = event->pos();
	//QPainter p(pixmap);
	//p.drawLine(startPoint, endPoint);
	//update();
}

void drawboardpanel::mouseMoveEvent(QMouseEvent * event)
{
	//����λͼ
	if (this->lineType != QString("����")) {
		*pixmap = *fpixmap; 
	}
	endPoint = event->pos();
	QPainter p(pixmap);
	p.setPen(QPen(this->c,this->width));

	if (lineType == QString("ֱ��"))
	{
		p.drawLine(startPoint, endPoint);
	}
	else if (lineType == QString("����"))
	{
		p.drawLine(startPoint, endPoint);
		startPoint = endPoint;
	}
	else if (this->lineType == QString("����"))
	{
		p.drawRect(QRect(startPoint, endPoint));
	}
	else if (this->lineType == QString("Բ"))
	{
		p.drawEllipse(QRect(startPoint, endPoint));
	}

	update();
}

void drawboardpanel::setLineType(QString type)
{
	this->lineType = type;
}
