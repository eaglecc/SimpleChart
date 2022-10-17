#include "studentmanager.h"



StudentManager::StudentManager(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
    qDebug() << QSqlDatabase::drivers();
    //QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");  //���ӵ�MYSQL�����ݿ�����
    //db.setHostName("localhost");         //������
    //db.setPort(3306);                    //�˿�
    //db.setDatabaseName("student_sign_sys_db");          //���ݿ���
    //db.setUserName("root");              //�û���
    //db.setPassword("root");            //����
    //db.open();
    
    
    //ʹ�����ݿ����ӳ�����
    db = ConnectionPool::openConnection();
    //��������
    if (!db.open())
    {
        qDebug() << "��������";
    }
    else
    {
        qDebug() << "���ӳɹ�";
        //���ر������
        LoadToTable("select sno,sname from stu");
        //���ذ༶��Ϣ
        ShowAsClass();
        //��ѧ����ʾ
        ShowAsNo();
    }

}

StudentManager::~StudentManager()
{
}

bool StudentManager::LoadToTable(QString sql)
{
    QSqlQuery query(db);
    query.exec(sql);
    if (query.size() == 0)
    {
        return false;
    }
    //��������
    ui.tableWidget->setRowCount(query.size());
    //����ÿ������
    int i = 0;
    while (query.next())
    {
        QCheckBox *box = new QCheckBox("δǩ��");
        //��ʼ����ʵ�ֲ�ѯ���ݿ⣬ǩ���Ѿ����ڵ�ѧ����Ϣ
        QSqlQuery sql(db);
        sql.exec(QString("select sign_time from stu_sign where sno = %1 and date(sign_time)=current_date")
            .arg(query.value(0).toString()));
        sql.next();
        //��ѯ�Ľ����Ϊ0���޸�Ϊ��ǩ��
        if (sql.size())
        {
            box->setText("��ǩ��");
            box->setChecked(true);
            box->setDisabled(true);
            ui.tableWidget->setItem(i,3,new QTableWidgetItem(sql.value(0).toString()));
        }
        
        ui.tableWidget->setItem(i, 0, new QTableWidgetItem(query.value(0).toString()));
        ui.tableWidget->setItem(i, 1, new QTableWidgetItem(query.value(1).toString()));
        ui.tableWidget->setCellWidget(i, 2, box);
        QString num = query.value(0).toString();
        connect(box, &QCheckBox::clicked, [=]() {
            box->setText("��ǩ��");
            box->setDisabled(true);
            //ǩ��ʱ��
            ui.tableWidget->setItem(i, 3, new QTableWidgetItem(QDateTime::currentDateTime().toString()));
            //����¼���뵽���ݿ���
            QSqlQuery s(db);
            s.exec(QString("insert into stu_sign values(%1,now())").arg(num));
        });
        i++;
    }
    return true;
}

void StudentManager::ShowAsClass()
{
    QSqlQuery q(db);
    q.exec("select distinct clazz from stu");
    ui.comboBox->addItem("ȫ���༶");
    while (q.next())
    {
        ui.comboBox->addItem(q.value(0).toString());
    }
    connect(ui.comboBox, &QComboBox::currentTextChanged, [=](QString text) {
        if (text == "ȫ���༶")
        {
            LoadToTable("select sno,sname from stu");
        }
        else
        {
            LoadToTable(QString("select sno,sname from stu where clazz='%1'").arg(text));
        }
    });
}

void StudentManager::ShowAsNo()
{
    connect(ui.pushButton, &QPushButton::clicked, [=]() {
        QString sno = ui.lineEdit->text();
        //LoadToTable(QString("select sno,sname from stu where sno =%1").arg(sno));
        if (sno == "")
        {
            QMessageBox::information(this, "warning", "������ѧ��");
            return;
        }
        if (LoadToTable(QString("select sno,sname from stu where sno =%1").arg(sno)) == false)
        {
            QMessageBox::information(this, "warning", "���޴���");
            return;
        }
    });
}
