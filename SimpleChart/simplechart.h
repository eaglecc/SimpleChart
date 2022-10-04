#pragma once

#include <QtCharts/QtCharts>
QT_CHARTS_USE_NAMESPACE
#include <QtCharts/QSplineSeries>
//QtCharts������ui_simplechart.hǰ��

#include <QtWidgets/QMainWindow>
#include "ui_simplechart.h"

class SimpleChart : public QMainWindow
{
	Q_OBJECT

public:
	SimpleChart(QWidget *parent = Q_NULLPTR);

private slots:
	void on_chartButton_clicked();
	void on_sinButton_clicked();
private:
	Ui::SimpleChartClass ui;
};
