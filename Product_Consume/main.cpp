#include <QCoreApplication>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

static bool more=true;

bool more_data_to_prepare(){
    return more;
}

struct data_chunk{
    char m_data='q';
    data_chunk(char c):m_data(c){}
};

data_chunk prepare_data(){
    std::cout<<"prepare_data preparing data ..."<<std::endl;
    char c='q';
    std::cin>>c;
    if(c=='q')
        more=false;
    return data_chunk(c);
}

void process_data(data_chunk&data){
    std::cout<<"process_data thread processing data: "<<data.m_data<<std::endl;
}

bool is_last_data(data_chunk&data){
    if(data.m_data=='q'){
        return true;
    }

    return false;
}

std::mutex mtx;
std::queue<data_chunk>data_queue;
std::condition_variable data_cond;

void data_prepare_thread(){
    while(more_data_to_prepare()){
        std::cout<<"data_prepare_thread start to prepare ..."<<std::endl;
        data_chunk data=prepare_data();
        std::lock_guard<std::mutex>guard(mtx);
        data_queue.push(data);
        std::cout<<"data_parepare_thread prepared data , and notify one..."<<std::endl;
        data_cond.notify_one();
    }
}
void data_process_thread(){
    while(true){
        std::cout<<"data_process_thread start to process ..."<<std::endl;
        std::unique_lock<std::mutex>lck(mtx);
        data_cond.wait(lck,[](){return !data_queue.empty();});
        data_chunk data=data_queue.front();
        data_queue.pop();
        lck.unlock();
        std::cout << "data_processing_thread process data ..." << std::endl;
        process_data(data);
        if(is_last_data(data))
            break;
    }
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    std::thread prepare(data_prepare_thread);
    std::thread process(data_process_thread);
    prepare.join();
    process.join();
    return a.exec();
}
