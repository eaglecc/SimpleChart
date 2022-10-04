#pragma once

#include <QtCharts/QtCharts>
QT_CHARTS_USE_NAMESPACE
#include <QtCharts/QSplineSeries>
//QtCharts������ui_simplechart.hǰ��
#include <QWidget>
#include "ui_chartdemo.h"

typedef QPointF Data;
typedef QList<Data> DataList;
typedef QList<DataList> DataTable;


class ChartDemo : public QWidget
{
	Q_OBJECT

public:
	ChartDemo(QWidget *parent = Q_NULLPTR);
	~ChartDemo();

public slots:
	void updateUI();

private:
	QChart * createAreaChart() const;
	DataTable generateRandomData(int listCount , int valueMax , int valueCount);

	void populateThemeBox();
	void populatedonghuaBox();
	void populateTuliBox();

private:
	Ui::ChartDemo ui;
	int m_listCount;
	int m_valueMax;
	int m_valueCount;
	DataTable m_dataTable;
	QChartView *m_chartView;

};
