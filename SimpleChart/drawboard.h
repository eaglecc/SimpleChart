#pragma once
#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

#include <QMainWindow>
#include "ui_drawboard.h"
#include <QLabel>
#include <QCombobox>
#include "drawboardpanel.h"

class DrawBoard : public QMainWindow
{
	Q_OBJECT

public:
	DrawBoard(QWidget *parent = Q_NULLPTR);
	~DrawBoard();
	void init();

	drawboardpanel *dp;

public slots:
	void slotChangeLineWidth(int lineWidth);
	void slotClere();

private:
	Ui::DrawBoard ui;
};
