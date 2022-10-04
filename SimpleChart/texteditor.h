#pragma once

#include <QWidget>
#include "ui_texteditor.h"

class textEditor : public QWidget
{
	Q_OBJECT

public:
	textEditor(QWidget *parent = Q_NULLPTR);
	~textEditor();

private:
	Ui::textEditor ui;
};
