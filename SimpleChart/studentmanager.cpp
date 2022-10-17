#include "studentmanager.h"



StudentManager::StudentManager(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
    qDebug() << QSqlDatabase::drivers();
    //QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");  //连接的MYSQL的数据库驱动
    //db.setHostName("localhost");         //主机名
    //db.setPort(3306);                    //端口
    //db.setDatabaseName("student_sign_sys_db");          //数据库名
    //db.setUserName("root");              //用户名
    //db.setPassword("root");            //密码
    //db.open();
    
    
    //使用数据库连接池连接
    db = ConnectionPool::openConnection();
    //测试连接
    if (!db.open())
    {
        qDebug() << "不能连接";
    }
    else
    {
        qDebug() << "连接成功";
        //加载表格数据
        LoadToTable("select sno,sname from stu");
        //加载班级信息
        ShowAsClass();
        //按学号显示
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
    //设置行数
    ui.tableWidget->setRowCount(query.size());
    //设置每行内容
    int i = 0;
    while (query.next())
    {
        QCheckBox *box = new QCheckBox("未签到");
        //初始化，实现查询数据库，签到已经存在的学生信息
        QSqlQuery sql(db);
        sql.exec(QString("select sign_time from stu_sign where sno = %1 and date(sign_time)=current_date")
            .arg(query.value(0).toString()));
        sql.next();
        //查询的结果不为0，修改为已签到
        if (sql.size())
        {
            box->setText("已签到");
            box->setChecked(true);
            box->setDisabled(true);
            ui.tableWidget->setItem(i,3,new QTableWidgetItem(sql.value(0).toString()));
        }
        
        ui.tableWidget->setItem(i, 0, new QTableWidgetItem(query.value(0).toString()));
        ui.tableWidget->setItem(i, 1, new QTableWidgetItem(query.value(1).toString()));
        ui.tableWidget->setCellWidget(i, 2, box);
        QString num = query.value(0).toString();
        connect(box, &QCheckBox::clicked, [=]() {
            box->setText("已签到");
            box->setDisabled(true);
            //签到时间
            ui.tableWidget->setItem(i, 3, new QTableWidgetItem(QDateTime::currentDateTime().toString()));
            //将记录插入到数据库中
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
    ui.comboBox->addItem("全部班级");
    while (q.next())
    {
        ui.comboBox->addItem(q.value(0).toString());
    }
    connect(ui.comboBox, &QComboBox::currentTextChanged, [=](QString text) {
        if (text == "全部班级")
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
            QMessageBox::information(this, "warning", "请输入学号");
            return;
        }
        if (LoadToTable(QString("select sno,sname from stu where sno =%1").arg(sno)) == false)
        {
            QMessageBox::information(this, "warning", "查无此人");
            return;
        }
    });
}
