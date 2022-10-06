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
    //���ر������
    bool LoadToTable(QString sql);
    //���հ༶��ʾ
    void ShowAsClass();
    //����ѧ����ʾ
    void ShowAsNo();

private:
	Ui::StudentManager ui;
};
