#include "selfielddialog.h"
#include "ui_selfielddialog.h"
#include <QDebug>

SelFieldDialog::SelFieldDialog(QStringList list, QWidget *parent) :
    source_list(list),
    QDialog(parent),
    ui(new Ui::SelFieldDialog)
{
    ui->setupUi(this);
    source_model =new QStringListModel();
    dest_model=new QStringListModel();
    proxyModel=new QSortFilterProxyModel;
    source_model->setStringList(source_list);
    dest_model->setStringList(dest_list);
    proxyModel->setSourceModel(source_model);
    proxyModel->setFilterKeyColumn(0);
    ui->surceListView->setModel(proxyModel);
    ui->destListView->setModel(dest_model);
    ui->surceListView->installEventFilter(this);

    connect(ui->surceListView->selectionModel(),&QItemSelectionModel::selectionChanged,
            this,&SelFieldDialog::updateCtrl);
    connect(ui->destListView->selectionModel(),&QItemSelectionModel::selectionChanged,
            this,&SelFieldDialog::updateCtrl);
    connect(source_model,&QStringListModel::dataChanged,this,&SelFieldDialog::updateCtrl);
    connect(dest_model,&QStringListModel::dataChanged,this,&SelFieldDialog::updateCtrl);

    setWindowIcon(QIcon(":/img/images/filter.png"));

}

SelFieldDialog::~SelFieldDialog()
{
    delete ui;
    source_model->deleteLater();
    dest_model->deleteLater();
}

QStringList SelFieldDialog::getSelField()
{
    return dest_list;
}

void SelFieldDialog::singleToDest()
{
    qDebug()<<"test singleToDest";
    QModelIndexList modelIndexList = ui->surceListView->selectionModel()->selectedIndexes();

    if(modelIndexList.count()>1)
        return;

    foreach (QModelIndex modelIndex, modelIndexList)
    {
        QString data=source_model->data(modelIndex,Qt::DisplayRole).toString();
        dest_list.append(data);
        dest_model->setStringList(dest_list);
        source_list.removeOne(data);
        source_model->setStringList(source_list);
    }
    ui->surceListView->selectionModel()->clear();
    updateCtrl();
}

void SelFieldDialog::singleToSource()
{
    qDebug()<<"test singleToSource";
    QModelIndexList modelIndexList = ui->destListView->selectionModel()->selectedIndexes();

    if(modelIndexList.count()>1)
        return;

    foreach (QModelIndex modelIndex, modelIndexList)
    {
        QString data=dest_model->data(modelIndex,Qt::DisplayRole).toString();
        source_list.append(data);
        source_model->setStringList(source_list);
        dest_list.removeOne(data);
        dest_model->setStringList(dest_list);
    }
    ui->destListView->selectionModel()->clear();
    updateCtrl();
}

void SelFieldDialog::multiToDest()
{
    qDebug()<<"test multiToDest";
    QModelIndexList modelIndexList = ui->surceListView->selectionModel()->selectedIndexes();

    foreach (QModelIndex modelIndex, modelIndexList)
    {
        QString data=source_model->data(modelIndex,Qt::DisplayRole).toString();
        dest_list.append(data);
        source_list.removeOne(data);
    }
    dest_model->setStringList(dest_list);
    source_model->setStringList(source_list);
    ui->surceListView->selectionModel()->clear();
    updateCtrl();
}

void SelFieldDialog::multiToSource()
{
    qDebug()<<"test multiToSource";
    QModelIndexList modelIndexList = ui->destListView->selectionModel()->selectedIndexes();
    QString data;
    foreach (QModelIndex modelIndex, modelIndexList)
    {
        data=dest_model->data(modelIndex,Qt::DisplayRole).toString();
        source_list.append(data);
        dest_list.removeOne(data);
    }
     source_model->setStringList(source_list);
     dest_model->setStringList(dest_list);
     ui->destListView->selectionModel()->clear();
     updateCtrl();
}

void SelFieldDialog::destItemUp()
{
    qDebug()<<"test destItemUp()";
    QModelIndex modelIndex=ui->destListView->currentIndex();
    if(modelIndex.row()>0){
        int upRowId=modelIndex.row()-1;
        QString temp=dest_list.at(upRowId);
        dest_list.replace(upRowId,dest_list.at(modelIndex.row()));
        dest_list.replace(modelIndex.row(),temp);
        dest_model->setStringList(dest_list);
        QModelIndex currentIndex=dest_model->index(upRowId,0);
        ui->destListView->setCurrentIndex(currentIndex);
    }
}

void SelFieldDialog::destItemDown()
{
    qDebug()<<"test destItemDown()";
    QModelIndex modelIndex=ui->destListView->currentIndex();
    if(modelIndex.row()==dest_model->rowCount()-1)
        return;
    int downRowId=modelIndex.row()+1;
    QString temp=dest_list.at(downRowId);
    dest_list.replace(downRowId,dest_list.at(modelIndex.row()));
    dest_list.replace(modelIndex.row(),temp);
    dest_model->setStringList(dest_list);
    QModelIndex currentIndex=dest_model->index(downRowId,0);
    ui->destListView->setCurrentIndex(currentIndex);
}

void SelFieldDialog::updateCtrl()
{

    qDebug()<<"test updateCtrl()";
    //update up and down button
    QModelIndex currentIndex=ui->destListView->currentIndex();
    if(dest_model->rowCount()>1){
        if(currentIndex.row()==0){
            ui->upPushButton->setEnabled(false);
            ui->downPushButton->setEnabled(true);
        }
        else if(currentIndex.row()==dest_model->rowCount()-1)
        {
            ui->upPushButton->setEnabled(true);
            ui->downPushButton->setEnabled(false);
        }else if(currentIndex.row())
        {
            ui->upPushButton->setEnabled(true);
            ui->downPushButton->setEnabled(true);
        }
    }else{
        ui->upPushButton->setEnabled(false);
        ui->downPushButton->setEnabled(false);
    }
    // update >>、 << 、>、 >
    ui->multiToDestBtn->setEnabled(false);
    ui->toDestBtn->setEnabled(false);
    ui->multiToSourceBtn->setEnabled(false);
    ui->toSourceBtn->setEnabled(false);
    int selCount=ui->surceListView->selectionModel()->selectedIndexes().count();
    if(selCount>1){
        ui->multiToDestBtn->setEnabled(true);
        ui->toDestBtn->setEnabled(false);
    }else if(selCount==1){
        ui->toDestBtn->setEnabled(true);
        ui->multiToDestBtn->setEnabled(false);
    }
    selCount=ui->destListView ->selectionModel()->selectedIndexes().count();
    if(selCount>1){
        ui->multiToSourceBtn->setEnabled(true);
        ui->toSourceBtn->setEnabled(false);
    }else if(selCount==1){
        ui->toSourceBtn->setEnabled(true);
        ui->multiToSourceBtn ->setEnabled(false);
    }
}

void SelFieldDialog::sourceFilter()
{
    qDebug()<<"source filter";
    QRegExp regExp(ui->filterLineEdit->text(), Qt::CaseInsensitive, QRegExp::Wildcard);
      proxyModel->setFilterRegExp(regExp);

}

bool SelFieldDialog::eventFilter(QObject *watched, QEvent *event)
{
    if(watched==ui->surceListView){
//        if(event->type()==QEvent::Paint){
//            qDebug()<<ui->surceListView->selectionModel()->selectedIndexes().count();
//        }

    }
    return QDialog::eventFilter(watched,event);
}
