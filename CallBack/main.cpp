#include <QCoreApplication>
#include <iostream>

typedef void(__stdcall*DownloadCallback)(const char*pUrl,bool bOK);

void DownloadFile(const char*pURL,DownloadCallback callback){
    std::cout<<"Downloading: "<<pURL<<std::endl;
    callback(pURL,true);
}
void __stdcall cb(const char*pURL,bool ok){
    std::cout<<"OnDownload Finished! "<<std::endl;
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    DownloadFile("www.baidu.com",cb);
    return a.exec();
}
