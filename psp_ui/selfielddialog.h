#ifndef SELFIELDDIALOG_H
#define SELFIELDDIALOG_H

#include <QDialog>
#include <QStringListModel>
#include <QSortFilterProxyModel>
namespace Ui {
class SelFieldDialog;
}

class SelFieldDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelFieldDialog(QStringList list,QWidget *parent = 0);
    ~SelFieldDialog();
public:
    QStringList getSelField();

private:
    Ui::SelFieldDialog *ui;
protected slots:

    void singleToDest();
    void singleToSource();
    void multiToDest();
    void multiToSource();
    void destItemUp();
    void destItemDown();
    void updateCtrl();
    //!过滤字段
    void sourceFilter();
    bool eventFilter(QObject *watched, QEvent *event);
private:
    //!源字段
    QStringListModel*source_model;
    QStringListModel*dest_model;
    QStringList source_list;
    QStringList dest_list;
    //!过滤模型
    QSortFilterProxyModel *proxyModel;
};

#endif // SELFIELDDIALOG_H
