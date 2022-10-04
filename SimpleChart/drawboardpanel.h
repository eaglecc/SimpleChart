#pragma once
#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

#include <QWidget>
#include <QPoint>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QColor>

#include "ui_drawboardpanel.h"


class drawboardpanel : public QWidget
{
	Q_OBJECT

public:
	drawboardpanel(QWidget *parent = Q_NULLPTR);
	~drawboardpanel();
	//��ͼ�¼�
	void paintEvent(QPaintEvent *event);
	//��갴���¼�
	void mousePressEvent(QMouseEvent *event);
	//����ͷ��¼�
	void mouseReleaseEvent(QMouseEvent *event);
	//����ƶ��¼�
	void mouseMoveEvent(QMouseEvent *event);
	//�������
	QPoint startPoint;
	QPoint endPoint;
	QString lineType;

	QPixmap *pixmap;
	QPixmap *fpixmap;

	void setLineType(QString type);

	//��ɫ���߿�
	int width;
	QColor c;

private:
	Ui::drawboardpanel ui;
};
