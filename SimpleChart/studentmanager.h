#pragma once
#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

#include <QWidget>
#include "ui_studentmanager.h"
#include "connectionpool.h"
#include <QtSql/QSqlDatabase>	// �������ݿ�
#include <QtSql/QSqlError>		// ���ݿ�����ʧ�ܴ�ӡ�������
#include <QtSql/QSqlQuery>		// ���ݿ��������ɾ�Ĳ飩
#include <QMessageBox>
#include <QVariantList>			// �����������Դ洢�κ����͵�����
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

    //���ر������
    bool LoadToTable(QString sql);
    //���հ༶��ʾ
    void ShowAsClass();
    //����ѧ����ʾ
    void ShowAsNo();

    QSqlDatabase db;

private:
	Ui::StudentManager ui;
};
