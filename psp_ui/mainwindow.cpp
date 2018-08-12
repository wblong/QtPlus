#include "mainwindow.h"
#include <QTableView>
#include <QMenuBar>
#include <QToolBar>
#include <QComboBox>
#include <QLabel>
#include <QStatusBar>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QCoreApplication>
#include <QTextStream>
#include <QToolButton>
#include <QDebug>
#include "selfielddialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createActions();
    createToolBars();
    createMenus();
    createStatusBars();

    m_view=new TableViewPage;
    updateCtrl();
    QStringList pages;
    int totalPage=m_view->totalPage();
    for(int i=1;i<=totalPage;++i)
        pages.append(QString("%1").arg(i));
    gotoPageBox->addItems(pages);


    setCentralWidget(m_view);
    setGeometry(50,50,1000,600);
    setWindowIcon(QIcon(":/img/images/table.png"));
    setWindowTitle(tr("page view"));
}

MainWindow::~MainWindow()
{

    m_view->deleteLater();
    openAction->deleteLater();
    fieldAction->deleteLater();
}

void MainWindow::createActions()
{

}

void MainWindow::createMenus()
{

}

void MainWindow::createToolBars()
{
    pageTool=addToolBar(tr("Page"));

    prePageBtn=new QToolButton;
    prePageBtn->setText(tr("Pre Page"));
    prePageBtn->setIcon(QIcon(":/img/images/pre_page.png"));
    prePageBtn->setToolTip(tr("Pre Page"));
    connect(prePageBtn,SIGNAL(clicked(bool)),this,SLOT(prevPage()));
    pageTool->addWidget(prePageBtn);

    nextPageBtn=new QToolButton;
    nextPageBtn->setText(tr("Next Page"));
    nextPageBtn->setIcon(QIcon(":img/images/next_page.png"));
    nextPageBtn->setToolTip(tr("Next Page"));
    connect(nextPageBtn,SIGNAL(clicked(bool)),this,SLOT(nextPage()));
    pageTool->addWidget(nextPageBtn);

    gotoPageLbl=new QLabel(tr("Goto Page:"));
    gotoPageLbl->setPixmap(QPixmap(":/img/images/goto_page.png"));
    pageTool->addWidget(gotoPageLbl);
    gotoPageBox=new QComboBox;
    connect(gotoPageBox,SIGNAL(currentIndexChanged(int)),this,SLOT(gotoPage(int)));
    pageTool->addWidget(gotoPageBox);

    fieldSelBtn=new QToolButton;
    fieldSelBtn->setText(tr("Filter"));
    fieldSelBtn->setIcon(QIcon(":img/images/filter.png"));
    fieldSelBtn->setToolTip(tr("Filter"));
    pageTool->addWidget(fieldSelBtn);
    connect(fieldSelBtn,&QToolButton::clicked,this,&MainWindow::openFileDlg);
}

void MainWindow::createStatusBars()
{
    msgTotalLbl=new QLabel(tr("Total:  "));
    msgPageLbl=new QLabel(tr("Page: 0/0"));
    statusBar()->addWidget(msgTotalLbl);
    statusBar()->addWidget(msgPageLbl);
}

void MainWindow::updateCtrl()
{
    int total=m_view->totalSize();
    int curPageSize=m_view->currentPageSize();
    //msgTotalLbl->setLineWidth(250);
    msgTotalLbl->setText(tr("Total:  %1/%2 ").arg(curPageSize).arg(total));

    int curPage=m_view->currentPage();
    int totalPage=m_view->totalPage();
   // msgPageLbl->setLineWidth(250);
    msgPageLbl->setText(tr("Page:  %1/%2 ").arg(curPage).arg(totalPage));

    nextPageBtn->setEnabled(true);
    prePageBtn->setEnabled(true);

    if (curPage >= totalPage)
        nextPageBtn->setEnabled(false);
    else if( curPage <= 1)
        prePageBtn->setEnabled(false);
    else
        ;
}
void MainWindow::setupMenu()
{
    QMenuBar*menuBar=this->menuBar();
    QMenu*file=menuBar->addMenu(tr("&File"));
    openAction=new QAction(tr("&open..."),this);
    file->addAction(openAction);
    connect(openAction,SIGNAL(triggered(bool)),this,SLOT(openfile()));
    fieldAction=new QAction(tr("&field"),this);
    file->addAction(fieldAction);
    connect(fieldAction,SIGNAL(triggered(bool)),this,SLOT(openFileDlg()));

}

void MainWindow::openfile()
{
    QString curr_path=QCoreApplication::applicationDirPath();
   //int ret=QMessageBox::information(this,tr("info"),tr("openfile"),QMessageBox::Ok);
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"),
                                                    curr_path,
                                                    tr("Data File(*.txt *.md);;All File(*.*)"));
    if(fileName.isEmpty())
        return;

    QStringList templist;
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream ts(&file);
        while(!ts.atEnd()){
            QString str=ts.readLine();
            templist.append(str);
        }
        file.close();

    }
}

void MainWindow::openFileDlg()
{
    QStringList list=m_view->getHeaderList();
    SelFieldDialog selFieldDlg(list);
    int i=0;
    if(QDialog::Accepted== selFieldDlg.exec()){
        //Model列修改
        QStringList resList=selFieldDlg.getSelField();
        m_view->setShowHeaderList(resList);

    }
}

void MainWindow::gotoPage(int index)
{
    index++;
    m_view->gotoPage(index);
    updateCtrl();
}

void MainWindow::nextPage()
{
    m_view->nextPage();
    updateCtrl();
}

void MainWindow::prevPage()
{
    m_view->previousPage();
    updateCtrl();
}
