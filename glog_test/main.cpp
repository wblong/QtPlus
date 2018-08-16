#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include "log.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QDir dir;
    QString currentDir=dir.currentPath();
    qDebug()<<currentDir;
    dir.mkpath(currentDir+"/log");
    log_init(argv[0],"log/wbl_",1);
    log_printf(google::GLOG_INFO,"INFO...");
    log_printf(google::GLOG_WARNING,"WARINING...");
    log_printf(google::GLOG_ERROR,"ERROR...");
//    log_printf(google::GLOG_FATAL,"FATAL...");
    return a.exec();
}
