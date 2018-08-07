#include "mainwindow.h"
#include<QMenu>
#include<QMenuBar>
#include<QAction>
#include<QToolBar>
#include<QIcon>
#include<QTextEdit>
#include<QFile>
#include<QFileDialog>
#include<QTextStream>

void MainWindow::openfile()
{
    QString path=QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                ".",
                tr("Text Files(*.txt);;Init Files(*.ini)"));
    if(!path.isEmpty()){
        QFile file(path);
        if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
            return;
        }
        QTextStream in(&file);
        textEdit->setText(in.readAll());
        file.close();
    }

}

void MainWindow::savefile()
{
    QString path=QFileDialog::getSaveFileName(
                this,
                tr("Save File"),
                ".",
                tr("Text Files(*.txt);;init File(*.ini)"));
    if(!path.isEmpty()){
        QFile file(path);
        if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
            return;
        QTextStream out(&file);
        out<<textEdit->toPlainText();
        file.close();
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QMenuBar *menubar=menuBar();
    QMenu*file=menubar->addMenu("&File");
    QMenu*help=menubar->addMenu("&Help");

    QAction*open=new QAction(QIcon(":/action/images/fileopen.png"),"&Open",this);
    file->addAction(open);
    QAction*save=new QAction(QIcon(":/action/images/filesave.png"),"&Save",this);
    file->addAction(save);

    QToolBar *toolbar=addToolBar("Toolbar");
    toolbar->addAction(open);
    toolbar->addAction(save);

    textEdit=new QTextEdit();
    setCentralWidget(textEdit);
    //Qt4和Qt5的区别
    connect(open,SIGNAL(triggered()),this,SLOT(openfile()));
    connect(open,&QAction::triggered,this,&MainWindow::savefile);
}

MainWindow::~MainWindow()
{
    textEdit->deleteLater();
}
