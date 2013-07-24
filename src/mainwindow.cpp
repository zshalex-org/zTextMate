#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "plistdocument.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainToolBar->hide();
    ui->textEdit->setBackground(QColor("#200020"));

//    PListDocument doc;

//    qDebug() << doc.load("Amy.tmTheme");
//    QVariant v = doc.getValue("settings");
//    PListArray list = v.value<PListArray>();

//    qDebug() << list.at(0) << doc.getValue(list.at(0),"settings.background");
//    << doc.root();
}

MainWindow::~MainWindow()
{
    delete ui;
}
