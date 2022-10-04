#include "simplechart.h"
#include <QtWidgets/QApplication>
#include "main.h"
#include "chartdemo.h"
#include "texteditor1.h"
#include "drawboard.h"


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//SimpleChart w;
	//w.show();
	//ChartDemo c;
	//c.show();
	//textEditor1 editor;
	//editor.show();

	//»æÍ¼°å
	DrawBoard c;
	c.show();
	return a.exec();
}
