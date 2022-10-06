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
    //QChart图表案例
    //SimpleChart w;
    //w.show();
    //ChartDemo c;
    //c.show();
    //文本编辑器
    //textEditor1 editor;
    //editor.show();

    //绘图板
    //DrawBoard c;
    //c.show();
    //学生签到系统
    StudentManager s;
    s.show();

    return a.exec();
}