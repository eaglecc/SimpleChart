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
	//绘图事件
	void paintEvent(QPaintEvent *event);
	//鼠标按下事件
	void mousePressEvent(QMouseEvent *event);
	//鼠标释放事件
	void mouseReleaseEvent(QMouseEvent *event);
	//鼠标移动事件
	void mouseMoveEvent(QMouseEvent *event);
	//鼠标坐标
	QPoint startPoint;
	QPoint endPoint;
	QString lineType;

	QPixmap *pixmap;
	QPixmap *fpixmap;

	void setLineType(QString type);

	//颜色、线宽
	int width;
	QColor c;

private:
	Ui::drawboardpanel ui;
};
