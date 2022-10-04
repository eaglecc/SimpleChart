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

	//�����˵���
	createMenu();
	
	//����������
	createToolBar();

	//��ʼ���źŲ�
	initConnect();
	
	//״̬��
	QStatusBar *statusBar = this->statusBar();
	QLabel * timeLabel = new QLabel("ʱ�䣺");
	statusBar->addWidget(timeLabel);

	//��������
	QDockWidget *dock = new QDockWidget();
	this->addDockWidget(Qt::TopDockWidgetArea,dock);

	//�ı��ؼ�
	textedit = new QTextEdit();
	this->setCentralWidget(textedit);

}

textEditor1::~textEditor1()
{
}


//�˵���
void textEditor1::createMenu() 
{
	QMenuBar * menu = this->menuBar();
	QMenu * fileMenu = menu->addMenu("�ļ�");
	QMenu * editMenu = menu->addMenu("�༭");
    newfile = fileMenu->addAction(QIcon(":/SimpleChart/Resources/grape.ico"), QString("�½�"));
    openfile = fileMenu->addAction(QIcon(":/SimpleChart/Resources/lime.ico"), "��");
    savefile = fileMenu->addAction(QIcon(":/SimpleChart/Resources/Snow Apple.ico"), "����");
}

//������
void textEditor1::createToolBar() {
	QToolBar *toolBar = this->addToolBar("tool");
	toolBar->addAction(newfile);
	toolBar->addSeparator();	//�ָ���
	toolBar->addAction(openfile);
	toolBar->addSeparator();
	toolBar->addAction(savefile);
	toolBar->addSeparator();

	//��ʾ����
	QLabel * fontType = new QLabel("���壺");
	toolBar->addWidget(fontType);
	//����ѡ���
	fontBox = new QFontComboBox();
	toolBar->addWidget(fontBox);
	//�����ֺ�
	QLabel * fontSizeLabel = new QLabel("�ֺ�");
	toolBar->addWidget(fontSizeLabel);
	fontSizeBox = new QComboBox();
	toolBar->addWidget(fontSizeBox);
	int size = 1;
	while (size <= 72)
	{
		fontSizeBox->addItem(QString::number(size));
		size++;
	}
	//�Ӵְ�ť
	boldBtn = new QToolButton();
	boldBtn->setText("B");
	toolBar->addWidget(boldBtn);
	//б�尴ť
	ItlicBtn = new QToolButton();
	ItlicBtn->setText("I");
	toolBar->addWidget(ItlicBtn);
}

void textEditor1::initConnect()
{
	qDebug() << connect(fontBox, &QFontComboBox::currentFontChanged, this, &textEditor1::setFont);
	
	//����������Ͳ�ƥ������
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
	//���þֲ��������
	tcf->setFont(font);
	textedit->mergeCurrentCharFormat(*tcf);		//�ϲ���ǰѡ�е�����
}

void textEditor1::setFontSize(int index)
{
	//�����ֺ�
	tcf->setFontPointSize((qreal)index);
	textedit->mergeCurrentCharFormat(*tcf);		//�ϲ���ǰѡ�е�����
}

void textEditor1::setFontBlod()
{
	//����Ӵ�
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
	//б����
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
	//�����ļ�  ��Ҫģ̬�Ի���
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
		msgBox.setText("����ʧ�ܣ�");
		msgBox.exec();
	}
}

void textEditor1::setOpenFile()
{
	//���ļ�
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
		msgBox.setText("��ʧ�ܣ�");
		msgBox.exec();
	}
}

void textEditor1::setNewFile()
{
	//�½��ļ�

	QMessageBox msgBox;
	msgBox.setText("��Ҫ�½�һ���ļ���");
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
