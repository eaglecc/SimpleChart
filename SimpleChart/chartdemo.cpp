#include "chartdemo.h"
#include "qlineseries.h"
#include "qareaseries.h"


ChartDemo::ChartDemo(QWidget *parent)
	: QWidget(parent),
	m_listCount(3),
	m_valueCount(7),
	m_valueMax(10),
	m_dataTable(generateRandomData(m_listCount, m_valueMax, m_valueCount))

{
	ui.setupUi(this);
	populateThemeBox();
	populatedonghuaBox();
	populateTuliBox();
	
	//QChart * chart = createAreaChart();
	//ui.chart->setChart(chart);
	m_chartView = new QChartView(createAreaChart());
	ui.gridLayout->addWidget(m_chartView , 1 , 0);

	ui.checkBox->setChecked(true);
	updateUI();
	connect(ui.themeBox , SIGNAL(currentIndexChanged(int)) , this , SLOT(updateUI()));
	connect(ui.donghuaBox , SIGNAL(currentIndexChanged(int)) , this , SLOT(updateUI()));
	connect(ui.tuliBox , SIGNAL(currentIndexChanged(int)) , this , SLOT(updateUI()));
	connect(ui.checkBox , SIGNAL(toggled(bool)) , this , SLOT(updateUI()));
}

ChartDemo::~ChartDemo()
{
}

QChart * ChartDemo::createAreaChart() const
{
	QChart *chart = new QChart();
	chart->setTitle("Area Chart");
	QLineSeries * lowSeries = nullptr;
	int nameIndex = 0;
	for (int i = 0; i < m_dataTable.count() ; i++)
	{
		QLineSeries * upperSeries = new QLineSeries(chart);
		for (int j = 0; j < m_dataTable[i].count(); j++)
		{
			Data data = m_dataTable[i].at(j);
			if (lowSeries) {
				const auto &points = lowSeries->points();
				upperSeries->append(QPointF(j, points[i].y() + data.y()));
			}
			else
			{
				upperSeries->append(QPointF(j,data.y()));
			}
		}
		QAreaSeries * area = new QAreaSeries(upperSeries , lowSeries);
		area->setName("name" + QString::number(nameIndex));
		nameIndex++;
		chart->addSeries(area);
		lowSeries = upperSeries;

	}

	chart->createDefaultAxes();
	return chart;
}

DataTable ChartDemo::generateRandomData(int listCount, int valueMax, int valueCount)
{
	DataTable dataTable;
	for (int i = 0; i < listCount; i++)
	{
		DataList dataList;
		qreal yValue(0);
		for (int j = 0; j < valueCount; j++)
		{
			yValue += QRandomGenerator::global()->bounded(1.5);
			QPointF value(j , yValue);
			dataList << Data(value);

		}

		dataTable << dataList;
	}
	return dataTable;
	
}

void ChartDemo::populateThemeBox()
{
	ui.themeBox->addItem("light" , QChart::ChartThemeLight);
	ui.themeBox->addItem("Blue Cerulean" , QChart::ChartThemeBlueCerulean);
	ui.themeBox->addItem("Dark" , QChart::ChartThemeDark);
	ui.themeBox->addItem("Brown Sand" , QChart::ChartThemeBrownSand);
	ui.themeBox->addItem("Blue NCS" , QChart::ChartThemeBlueNcs);
	ui.themeBox->addItem("High Contrast" , QChart::ChartThemeHighContrast);
	ui.themeBox->addItem("BlueIcy" , QChart::ChartThemeBlueIcy);
	ui.themeBox->addItem("Qt" , QChart::ChartThemeQt);
}

void ChartDemo::populatedonghuaBox()
{
	ui.donghuaBox->addItem("NoAnimation",QChart::NoAnimation);
	ui.donghuaBox->addItem("GridAxisAnimations",QChart::GridAxisAnimations);
	ui.donghuaBox->addItem("SeriesAnimations",QChart::SeriesAnimations);
	ui.donghuaBox->addItem("AllAnimations",QChart::AllAnimations);
}

void ChartDemo::populateTuliBox()
{
	ui.tuliBox->addItem("No Legend" , 0);
	ui.tuliBox->addItem("Top" , Qt::AlignTop);
	ui.tuliBox->addItem("Bottom" , Qt::AlignBottom);
	ui.tuliBox->addItem("Left", Qt::AlignLeft);
	ui.tuliBox->addItem("Right" , Qt::AlignRight);

}

void ChartDemo::updateUI()
{
	//¿¹¾â³Ý
	bool checked = ui.checkBox->isChecked();
	m_chartView->setRenderHint(QPainter::Antialiasing , checked);
	//Ö÷Ìâ
	QChart::ChartTheme theme = static_cast<QChart::ChartTheme>(
		ui.themeBox->itemData(ui.themeBox->currentIndex()).toInt());
	m_chartView->chart()->setTheme(theme);
	//¶¯»­
	QChart::AnimationOptions options(
		ui.donghuaBox->itemData(ui.donghuaBox->currentIndex()).toInt());
	m_chartView->chart()->setAnimationOptions(options);
	//Í¼Àý
	Qt::Alignment alignment(
		ui.tuliBox->itemData(ui.tuliBox->currentIndex()).toInt());

	if (!alignment)
	{
		m_chartView->chart()->legend()->hide();
	}
	else
	{
		m_chartView->chart()->legend()->setAlignment(alignment);
		m_chartView->chart()->legend()->show();
	}
}