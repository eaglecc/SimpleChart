#include "simplechart.h"
#include <QtWidgets/QApplication>
#include "main.h"
#include "chartdemo.h"
#include "texteditor1.h"
#include "drawboard.h"
#include "studentmanager.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QChartͼ����
    //SimpleChart w;
    //w.show();
    //ChartDemo c;
    //c.show();
    //�ı��༭��
    //textEditor1 editor;
    //editor.show();

    //��ͼ��
    //DrawBoard c;
    //c.show();
    //ѧ��ǩ��ϵͳ
    StudentManager s;
    s.show();

    return a.exec();
}