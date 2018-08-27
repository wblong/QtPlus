#include <QCoreApplication>
#include <iostream>
#include <vector>
#include <chrono>

#include"threadpool.h"

void func(){
    std::this_thread::sleep_for(std::chrono::microseconds(100));
    std::cout<<"Work thread ID:"<<std::this_thread::get_id()<<std::endl;
    //std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//   ThreadPool pool(4);

//   std::vector< std::future<int> > results;

//   for(int i = 0; i < 8; ++i) {
//       results.emplace_back(
//           pool.enqueue([i] {
//               std::cout << "hello " << i << std::endl;
//               //std::this_thread::sleep_for(std::chrono::seconds(1));
//               std::this_thread::sleep_for(std::chrono::milliseconds(10));
//               std::cout << "world " << i << std::endl;
//               return i*i;
//           })
//       );
//   }


//   for(auto && result: results)
//       std::cout << result.get() << ' ';
//   std::cout << std::endl;

//    ThreadPool pool(4);

//    auto result=pool.enqueue([](int answer){
//        return answer;
//    },42);

//    std::cout<<result.get()<<std::endl;
    std::cout<<std::thread::hardware_concurrency()<<std::endl;
    ThreadPool pool(2);
    while (true) {
        pool.enqueue(func);
    }
    return a.exec();
}
