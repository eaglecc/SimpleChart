#pragma once
#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

#include <QWidget>
#include "ui_studentmanager.h"


class StudentManager : public QWidget
{
	Q_OBJECT

public:
	StudentManager(QWidget *parent = Q_NULLPTR);
	~StudentManager();
    //加载表格数据
    bool LoadToTable(QString sql);
    //按照班级显示
    void ShowAsClass();
    //按照学号显示
    void ShowAsNo();

private:
	Ui::StudentManager ui;
};
