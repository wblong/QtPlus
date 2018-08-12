#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "tableviewpage.h"
#include <QMainWindow>
QT_BEGIN_NAMESPACE
class QTableView;
class QStandardItemModel;
class QAction;
class QMenu;
class QToolBar;
class QComboBox;
class QLabel;
class QToolButton;
QT_END_NAMESPACE

#define FixedRowCount 6
#define FixedColumnCount 6
#define PAGE_SIZE 100

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBars();
    //!更新控件状态
    void updateCtrl();

protected:
    void setupMenu();
private slots:
    void openfile();
    void openFileDlg();
    void gotoPage(int index);
    void nextPage();
    void prevPage();
private:
    TableViewPage* m_view;
    //!QAction
    QAction*openAction;
    QAction*fieldAction;
    //!QTooBar
    QToolButton* prePageBtn;
    QToolButton* nextPageBtn;
    QToolButton* fieldSelBtn;
    QToolBar*pageTool;
    QLabel*gotoPageLbl;
    QComboBox*gotoPageBox;
    //!QStatusBar
    QLabel*msgTotalLbl;
    QLabel*msgPageLbl;
};

#endif // MAINWINDOW_H
