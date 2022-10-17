#include "connectionpool.h"

#include <QDebug>
#include <QtSql>
#include <QString>
#include <QThread>
#include <QCoreApplication>

// ��ȡ���ݿ�����
QSqlDatabase ConnectionPool::openConnection(const QString &connectionName) {
    // 1. �������ӵ�ȫ��: �����̵߳ĵ�ַ�ʹ�������� connectionName����Ϊͬһ���߳̿������봴��������ݿ�����
    // 2. ��������Ѿ����ڣ������������������´���
    //    2.1 ��������ǰ�������ݿ⣬������ӶϿ����������½������� (����: �ر����ݿ⼸���Ӻ����������ٴη������ݿ�)
    // 3. ������Ӳ����ڣ��򴴽�����
    // 4. �߳̽���ʱ���ͷ��ڴ��߳��д��������ݿ�����

    // [1] �������ӵ�ȫ��: �����̵߳ĵ�ַ�ʹ�������� connectionName����Ϊͬһ���߳̿������봴��������ݿ�����
    QString baseConnectionName = "conn_" + QString::number(quint64(QThread::currentThread()), 16);
    QString fullConnectionName = baseConnectionName + connectionName;

    if (QSqlDatabase::contains(fullConnectionName)) {
        // [2] ��������Ѿ����ڣ������������������´���
        QSqlDatabase existingDb = QSqlDatabase::database(fullConnectionName);

        // [2.1] ��������ǰ�������ݿ⣬������ӶϿ����������½������� (����: �ر����ݿ⼸���Ӻ����������ٴη������ݿ�)
        QSqlQuery query("SELECT 1", existingDb);

        if (query.lastError().type() != QSqlError::NoError && !existingDb.open()) {
            qDebug().noquote() << "Open datatabase error:" << existingDb.lastError().text();
            return QSqlDatabase();
        }

        return existingDb;
    }
    else {
        // [3] ������Ӳ����ڣ��򴴽�����
        if (qApp != nullptr) {
            // [4] �߳̽���ʱ���ͷ��ڴ��߳��д��������ݿ�����
            QObject::connect(QThread::currentThread(), &QThread::finished, qApp, [fullConnectionName] {
                if (QSqlDatabase::contains(fullConnectionName)) {
                    QSqlDatabase::removeDatabase(fullConnectionName);
                    qDebug().noquote() << QString("Connection deleted: %1").arg(fullConnectionName);
                }
            });
        }

        return createConnection(fullConnectionName);
    }
}

// �������ݿ�����
QSqlDatabase ConnectionPool::createConnection(const QString &connectionName) {
    static int sn = 0;

    // ����һ���µ����ݿ�����
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", connectionName);
    db.setHostName("localhost");         //������
    db.setPort(3306);                    //�˿�
    db.setDatabaseName("student_sign_sys_db");          //���ݿ���
    db.setUserName("root");              //�û���
    db.setPassword("root");            //����
    if (db.open()) {
        qDebug().noquote() << QString("Connection created: %1, sn: %2").arg(connectionName).arg(++sn);
        return db;
    }
    else {
        qDebug().noquote() << "Create connection error:" << db.lastError().text();
        return QSqlDatabase();
    }
}