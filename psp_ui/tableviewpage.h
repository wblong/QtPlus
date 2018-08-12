#ifndef TABLEVIEWPAGE_H
#define TABLEVIEWPAGE_H

#include<QTableView>
#include<QStandardItemModel>
#include<QWidget>

class TableViewPage:public QTableView
{
    Q_OBJECT
public:
   explicit TableViewPage(QWidget*parent=0);
    ~TableViewPage();
    QStandardItemModel* getModel(){return m_model;}
    int currentPage() const { return m_nCurPage; }
    int totalSize() const { return m_nTotal; }
    int currentPageSize()const{return m_nCurPageSize;}
    int lastPageSize() const { return m_nLastPageSize; }
    void getData();
    void initModel(int start=1,int end=-1);
    QStringList getHeaderList();
    void setShowHeaderList(QStringList showHeaderList);
public slots:
    void previousPage();
    void nextPage();
    void gotoPage(int index);
    int  totalPage();
    void updateModel();
private:
    int lastPageSize();
private:
    QStandardItemModel* m_model;
    //每页的开始索引
    int                 m_nStartId;
    //理论上每页的大小
    int                 m_nPageSize;
    //当前页的实际大小
    int                 m_nCurPageSize;
    //最后一页的实际大小
    int                 m_nLastPageSize;
    //总数
    int                 m_nTotal;
    //当前页
    int                 m_nCurPage;
    //总共有多少页
    int                 m_nTotalPage;
    //
    QStringList         m_data;
    //所有字段
    QStringList         m_headerList;
    //显示字段
    QStringList         m_headerShowList;
};

#endif // TABLEVIEWPAGE_H
