#include <QCoreApplication>
#include <iostream>
#include <thread>

class CCallBack
{
public:
    CCallBack(int d,bool bRun):_data(d),_bRun(bRun){}
public:
    typedef void(*pFun)(void*param);

//    static void TextPrint(void*param){
//        CCallBack *cb=(CCallBack*)param;
//        std::cout<<"Static CallBack Function of a class with funtype"<<std::endl;
//        std::cout<<cb->_data<<std::endl;
//    }

    static void ForText(CCallBack::pFun pFun1,void*param){
        CCallBack*cb=(CCallBack*)param;
        while (cb->_bRun) {
           pFun1(param);
        }
    }
public:
    int _data;
    bool _bRun;
};

class Invoke
{
public:
    Invoke() {

    }
    static void TextPrint(void*para){
        CCallBack*cb=(CCallBack*)para;
        std::cout<<"Static CallBack Function of a class with funtype"<<std::endl;
        std::cout<<cb->_data<<std::endl;
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CCallBack cb(10,true);
   //ForText(Invoke::TextPrint,&cb);
    std::thread *pThread=new std::thread(CCallBack::ForText,Invoke::TextPrint,&cb);
    pThread->join();

    return a.exec();
}
