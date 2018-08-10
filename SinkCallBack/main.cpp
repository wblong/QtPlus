#include <QCoreApplication>
#include <iostream>

class IDownload{
   public:
    virtual void OnDownloadFile(const char* pUrl,bool OK)=0;
};

class MyDownload{
public:
    MyDownload(IDownload*sink):_sink(sink){

    }
    void DownloadFile(const char*pUrl,bool OK){
        if(_sink!=nullptr){
            _sink->OnDownloadFile(pUrl,OK);
        }
    }
private:
    IDownload*_sink;
};

class MyDownLoadFile:public IDownload{
    virtual void OnDownloadFile(const char*pUrl,bool OK){
        std::cout<<"Downloading"<<pUrl<<std::endl;

    }
  public:
    void download(){
        MyDownload down(this);
        down.DownloadFile("www.baidu.com",true);
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MyDownLoadFile dow;
    dow.download();
    return a.exec();
}
