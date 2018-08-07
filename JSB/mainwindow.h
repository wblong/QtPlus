#ifndef MAINWINDOW_H
#define MAINWINDOW_H
class QTextEdit;

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private slots:
    void openfile();
    void savefile();
private:
    QTextEdit*textEdit;
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
