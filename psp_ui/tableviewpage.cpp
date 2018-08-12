#include "tableviewpage.h"
#include<QFile>
#include<QTextStream>
#include<QStringList>
#define PAGSIZE 50
//! pagesize , filename
TableViewPage::TableViewPage(QWidget *parent):
    QTableView(parent)
  , m_nStartId(0)
  , m_nPageSize(PAGSIZE)
  , m_nCurPageSize(0)
  , m_nTotal(0)
  , m_nCurPage(1)
  , m_nTotalPage(0)

{
    getData();
    m_model=new QStandardItemModel();
    initModel();
    m_nTotal=m_model->rowCount();
    m_nTotalPage=totalPage();
    m_nLastPageSize=lastPageSize();
    updateModel();
    this->setModel(m_model);
}

TableViewPage::~TableViewPage()
{

}

void TableViewPage::getData()
{
    QFile file("data.txt");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream ts(&file);
        while(!ts.atEnd()){
            QString str=ts.readLine();
            m_data.append(str);
        }
        file.close();
    }
    //读取全部的字段,首次加载所有列
    m_headerShowList= m_headerList=m_data.at(0).split(",",QString::KeepEmptyParts);
}

void TableViewPage::initModel(int start,int end)
{
    int row_count=m_data.size();
    if(start<1)
        start=1;
    if(end>row_count||end<0)
        end=row_count;

    if(row_count>0){
        m_model->clear();
        m_model->setRowCount(end-start);
        m_model->setHorizontalHeaderLabels(m_headerShowList);

        QStandardItem *item;
        QStringList templist;
        int col;
        for(int i=start;i<end;++i){
            QString linestr=m_data.at(i);
            templist=linestr.split(',',QString::KeepEmptyParts);
            col=0;
            for(int j=0;j<templist.size();++j){

                if(m_headerShowList.contains(m_headerList.at(j))){

                    item=new QStandardItem(templist.at(j));
                    m_model->setItem(i-start,col,item);
                    ++col;
                }
            }
        }
    }
}

QStringList TableViewPage::getHeaderList()
{
    return m_headerList;
}

void TableViewPage::setShowHeaderList(QStringList showHeaderList)
{
    m_headerShowList=showHeaderList;
    updateModel();
}

void TableViewPage::previousPage()
{
    if(m_nStartId <= 1 || m_nTotal <= 0)
        return;

    m_nCurPage--;
    this->updateModel();
}

void TableViewPage::nextPage()
{
    if( m_nCurPage >= m_nTotalPage || m_nTotal <= 0)
        return;

    m_nCurPage++;
    this->updateModel();
}

void TableViewPage::gotoPage(int index)
{
    if(  index <= 0 || index > m_nTotalPage || m_nTotalPage <= 0 || index == m_nCurPage)
        return;

    m_nCurPage = index;
    this->updateModel();
}

int TableViewPage::totalPage()
{
    m_nTotalPage = m_nTotal / m_nPageSize;
    m_nTotalPage = (m_nTotal % m_nPageSize) > 0 ? (m_nTotalPage + 1) : m_nTotalPage;
    return m_nTotalPage;
}

void TableViewPage::updateModel()
{
    m_nStartId = (m_nCurPage-1) * m_nPageSize+1;
    int end=m_nStartId+m_nPageSize;
    initModel(m_nStartId,end);
    m_nCurPageSize = m_model->rowCount();
}

int TableViewPage::lastPageSize()
{
    m_nLastPageSize = (m_nTotal % m_nPageSize) == 0 ? m_nPageSize : (m_nTotal % m_nPageSize);
    return m_nLastPageSize;
}
