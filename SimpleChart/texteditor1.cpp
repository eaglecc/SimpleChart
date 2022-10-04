#include "texteditor1.h"
#include "qdebug.h"
#include "qfiledialog.h"
#include "qfile.h"

textEditor1::textEditor1(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->resize(900,600);
	tcf = new QTextCharFormat();

	//创建菜单栏
	createMenu();
	
	//创建工具栏
	createToolBar();

	//初始化信号槽
	initConnect();
	
	//状态栏
	QStatusBar *statusBar = this->statusBar();
	QLabel * timeLabel = new QLabel("时间：");
	statusBar->addWidget(timeLabel);

	//浮动窗口
	QDockWidget *dock = new QDockWidget();
	this->addDockWidget(Qt::TopDockWidgetArea,dock);

	//文本控件
	textedit = new QTextEdit();
	this->setCentralWidget(textedit);

}

textEditor1::~textEditor1()
{
}


//菜单栏
void textEditor1::createMenu() 
{
	QMenuBar * menu = this->menuBar();
	QMenu * fileMenu = menu->addMenu("文件");
	QMenu * editMenu = menu->addMenu("编辑");
    newfile = fileMenu->addAction(QIcon(":/SimpleChart/Resources/grape.ico"), QString("新建"));
    openfile = fileMenu->addAction(QIcon(":/SimpleChart/Resources/lime.ico"), "打开");
    savefile = fileMenu->addAction(QIcon(":/SimpleChart/Resources/Snow Apple.ico"), "保存");
}

//工具栏
void textEditor1::createToolBar() {
	QToolBar *toolBar = this->addToolBar("tool");
	toolBar->addAction(newfile);
	toolBar->addSeparator();	//分割线
	toolBar->addAction(openfile);
	toolBar->addSeparator();
	toolBar->addAction(savefile);
	toolBar->addSeparator();

	//提示字体
	QLabel * fontType = new QLabel("字体：");
	toolBar->addWidget(fontType);
	//字体选择框
	fontBox = new QFontComboBox();
	toolBar->addWidget(fontBox);
	//设置字号
	QLabel * fontSizeLabel = new QLabel("字号");
	toolBar->addWidget(fontSizeLabel);
	fontSizeBox = new QComboBox();
	toolBar->addWidget(fontSizeBox);
	int size = 1;
	while (size <= 72)
	{
		fontSizeBox->addItem(QString::number(size));
		size++;
	}
	//加粗按钮
	boldBtn = new QToolButton();
	boldBtn->setText("B");
	toolBar->addWidget(boldBtn);
	//斜体按钮
	ItlicBtn = new QToolButton();
	ItlicBtn->setText("I");
	toolBar->addWidget(ItlicBtn);
}

void textEditor1::initConnect()
{
	qDebug() << connect(fontBox, &QFontComboBox::currentFontChanged, this, &textEditor1::setFont);
	
	//解决参数类型不匹配问题
	void (QComboBox::*p)(int)= &QComboBox::currentIndexChanged;
	qDebug() << connect(fontSizeBox , p , this, &textEditor1::setFontSize);
	//qDebug() << connect(fontSizeBox, QOverload<int>::of(&QComboBox::currentIndexChanged)
	//	, this, &textEditor1::setFontSize);
	connect(boldBtn , &QToolButton::clicked , this ,&textEditor1::setFontBlod);
	connect(ItlicBtn , &QToolButton::clicked, this , &textEditor1::setFontItlic);	
	connect(savefile , &QAction::triggered , this , &textEditor1::setSave);
	connect(openfile , &QAction::triggered , this , &textEditor1::setOpenFile);
	connect(newfile , &QAction::triggered , this , &textEditor1::setNewFile);
}

void textEditor1::setFont(const QFont &font)
{
	//textedit->setFont(font);
	//设置局部字体更改
	tcf->setFont(font);
	textedit->mergeCurrentCharFormat(*tcf);		//合并当前选中的字体
}

void textEditor1::setFontSize(int index)
{
	//更改字号
	tcf->setFontPointSize((qreal)index);
	textedit->mergeCurrentCharFormat(*tcf);		//合并当前选中的字体
}

void textEditor1::setFontBlod()
{
	//字体加粗
	if (textedit->fontWeight() > QFont::Normal )
	{
		tcf->setFontWeight(QFont::Normal);
	}
	else
	{
		tcf->setFontWeight(QFont::Bold);
	}
	textedit->mergeCurrentCharFormat(*tcf);
}

void textEditor1::setFontItlic()
{
	//斜体字
	if (textedit->fontItalic() == QFont::StyleNormal)
	{
		tcf->setFontItalic(true);
	}
	else if (textedit->fontItalic() == QFont::StyleItalic)
	{
		tcf->setFontItalic(false);
	}
	textedit->mergeCurrentCharFormat(*tcf);
}

void textEditor1::setSave()
{
	//保存文件  需要模态对话框
	/*
	QDialog *dialog = new QDialog();
	dialog->show();*/
	QString filename = QFileDialog::getSaveFileName();
	QFile f(filename);
	if (f.open(QIODevice::ReadWrite))
	{
		QTextStream fin(&f);
		fin << textedit->toPlainText();
	}
	else
	{
		QMessageBox msgBox;
		msgBox.setText("保存失败！");
		msgBox.exec();
	}
}

void textEditor1::setOpenFile()
{
	//打开文件
	QString filename = QFileDialog::getOpenFileName();
	QFile f(filename);
	if (f.open(QIODevice::ReadWrite))
	{
		QTextStream fout(&f);
		textedit->setText(fout.readAll());
		this->setWindowTitle(filename);
	}
	else
	{
		QMessageBox msgBox;
		msgBox.setText("打开失败！");
		msgBox.exec();
	}
}

void textEditor1::setNewFile()
{
	//新建文件

	QMessageBox msgBox;
	msgBox.setText("将要新建一个文件。");
	msgBox.setInformativeText("Do you want to save your changes?");
	msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Save);
	int ret = msgBox.exec();
	switch (ret) {
	case QMessageBox::Save:
		// Save was clicked
		setSave();
		break;
	case QMessageBox::Discard:
		// Don't Save was clicked
		break;
	case QMessageBox::Cancel:
		// Cancel was clicked
		break;
	default:
		// should never be reached
		break;
	}
	textedit->clear();
}
