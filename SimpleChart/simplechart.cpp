#include "simplechart.h"


SimpleChart::SimpleChart(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

}

void SimpleChart::on_chartButton_clicked()
{
	QSplineSeries *series = new QSplineSeries();
	series->setName("spline");
	series->append(1, 2);
	series->append(2, 5);
	series->append(3, 6);
	series->append(4, 8);
	series->append(5, 2);

	QChart *chart = new QChart();
	chart->addSeries(series);//�������
	chart->setTitle("Simple spline chart example");//����
	chart->createDefaultAxes();//����ϵ
	chart->axes(Qt::Vertical).first()->setRange(0, 10);//����ϵ��Χ

	ui.testchart->setChart(chart);

	//����2
   //QChartView *chartView = new QChartView(chart);
   //chartView->setRenderHint(QPainter::Antialiasing);
   //this->setCentralWidget(chartView);

}

void SimpleChart::on_sinButton_clicked()
{
	//ֱ������δ���ڴ�����
	QSplineSeries *LineSeries = new QSplineSeries();  //QSplineSeries ƽ������  QLineSeries����
	for (double x = 0; x < 10; x += 0.1)
	{
		LineSeries->append(x, sin(x));
	}
	QChart *chart = new QChart();
	chart->addSeries(LineSeries);
	chart->legend()->hide();
	chart->createDefaultAxes();
	chart->setTheme(QChart::ChartThemeDark);

	QChartView *view = new QChartView(chart);  //������ͼ��ֱ����һ����������
	view->resize(600, 200);  //
	view->setWindowTitle("sin");
	view->setRenderHint(QPainter::Antialiasing);
	view->show();// show();
    
}

