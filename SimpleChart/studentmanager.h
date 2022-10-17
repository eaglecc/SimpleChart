#pragma once
#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

#include <QWidget>
#include "ui_studentmanager.h"
#include "connectionpool.h"
#include <QtSql/QSqlDatabase>	// 连接数据库
#include <QtSql/QSqlError>		// 数据库连接失败打印报错语句
#include <QtSql/QSqlQuery>		// 数据库操作（增删改查）
#include <QMessageBox>
#include <QVariantList>			// 泛型链表，可以存储任何类型的数据
#include <QDebug>
#include <QCheckBox>
#include <QDateTime>
#include <QMessageBox>

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

    QSqlDatabase db;

private:
	Ui::StudentManager ui;
};
