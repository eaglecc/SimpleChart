#pragma once

#include <QWidget>
#include "ui_studentmanager.h"

class StudentManager : public QWidget
{
	Q_OBJECT

public:
	StudentManager(QWidget *parent = Q_NULLPTR);
	~StudentManager();

private:
	Ui::StudentManager ui;
};
