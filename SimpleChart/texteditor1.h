#pragma once
#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

#include <QMainWindow>
#include <QFont>
#include <QTextEdit>
#include <QFontComboBox>
#include "ui_texteditor1.h"
#include <QMenuBar>
#include <QToolBar>
#include <QIcon>
#include <QLabel>
#include <QComboBox>
#include <QToolButton>
#include <QStatusBar>
#include <QDockWidget>
#include <QTextCharFormat>
#include <QDialog>
#include <QMessageBox>

class textEditor1 : public QMainWindow
{
	Q_OBJECT

public:
	textEditor1(QWidget *parent = Q_NULLPTR);
	~textEditor1();
	void createMenu();
	void createToolBar();
	void initConnect();
	QAction * newfile;
	QAction * openfile;
	QAction * savefile;
	QTextEdit * textedit;
	QFontComboBox * fontBox;
	QComboBox * fontSizeBox;
	QTextCharFormat * tcf;
	QToolButton * boldBtn;
	QToolButton * ItlicBtn;

public slots:
	void setFont(const QFont &font);
	void setFontSize(int index);
	void setFontBlod();
	void setFontItlic();
	void setSave();
	void setOpenFile();
	void setNewFile();

private:
	Ui::textEditor1 ui;
};
