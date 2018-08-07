/*!
 * \file main.cpp
 * \brief
 *
 * 观察者模式及C++11变参模板
 *
 * \author
 * \version
 * \date
 *
 * \b
 * \li
 *
 * -
 * -
 * \li
 *
 * -
 * -
*/
#include <QCoreApplication>
#include <iostream>
#include <list>
#include <algorithm>
#include <mutex>
#include <string>
#include <functional>

/*!
 * \brief The IListener class
 *
 * 观察者接口
 *
 */
class IListener {

public:
    /*!
     * \brief OnPress
     * \param xpos
     * \param ypos
     */
    virtual void  OnPress(int xpos, int ypos) = 0;
    /*!
     * \brief CallBack
     * \param param1
     * \param param2
     */
    virtual void  CallBack(std::string param1, std::string param2) = 0;

};
/*!
 * \brief The Listener class
 *
 * 具体的观察者类
 *
 */
class Listener :public IListener {

public:
    Listener(std::string param) :m_name(param) {

    }
    virtual void OnPress(int xpos, int ypos) {
        std::cout << "OnPress:" << m_name << std::endl;

    }
    virtual void CallBack(std::string param1, std::string param2) {
        std::cout << "CallBack:" << m_name << std::endl;
    }
private:
    std::string m_name;///<标志观察者Identify
};
/*!
 * \brief
 */
template<class T> class DipatchBase {

public:
    /*!
     * std::bind 绑定
     * std::function 函数式
     */

//    class Test
//    {
//    public:
//        void Add(std::function<int(int, int)> fun, int a, int b)
//        {
//            int sum = fun(a, b);
//            std::cout << "sum:" << sum << std::endl;
//        }
//    };
//    class TestAdd
//    {
//    public:
//        int Add(int a,int b)
//        {
//            std::cout << "TestAdd::Add" << std::endl;
//            return a + b;
//        }
//    };
//    Test test;
//    TestAdd testAdd;
//    test.Add(std::bind(&TestAdd::Add, testAdd, std::placeholders::_1, std::placeholders::_2), 1, 2);
    template<typename FunType,typename ...Arg> void dispatch(FunType func,Arg...args){
        m_mtx.lock();
        for(auto&itor:m_listeners)
        {
           std::bind(func,itor,args...)();
        }
        m_mtx.unlock();
    }
    std::list<T*>& GetListeners() {

        return m_listeners;
    }
    void addListener(T*listener) {
        auto itor = std::find_if(m_listeners.begin(), m_listeners.end(), find_listener(listener));
        if (itor != m_listeners.end())return;
        m_listeners.push_back(listener);
    }
    void removeLister(T*listener) {
        auto itor = std::find_if(m_listeners.begin(), m_listeners.end(), find_listener(listener));
        if (itor == m_listeners.end())return;
        m_listeners.erase(itor);

    }
protected:
    std::list<T*>m_listeners;///<注册的观察者
    /*!
     * \brief The find_listener struct
     */
    struct  find_listener
    {
        find_listener(T* listener) :m_listener(listener) {}
        /*!
         * \brief operator ()
         * \param listener
         * \return false or true
         */
        bool operator()(const T* listener){
            if (listener == m_listener)return true;
            else return false;
        }
        T* m_listener;
    };

    std::mutex m_mtx;
};

///*!
// * \brief The Dipatcher class
// *
// * 发送者 public
// *
// */
//class Dipatcher :public DipatchBase<IListener>
//{
//public:
//	void DipatchOnPress(int xpos, int ypos) {

//       m_mtx.lock();
//       auto listners = GetListeners();
//       for(auto lis:listners){
//           lis->OnPress(xpos,ypos);
//       }
//       m_mtx.unlock();

//	}
//	void DipatchCallBack(std::string param1, std::string param2) {
//        m_mtx.lock();
//        auto listners=GetListeners();
//        for(auto lis:listners){
//            lis->CallBack(param1,param2);
//        }
//        m_mtx.unlock();
//	}
//};


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Listener l1("Listener1");
    Listener l2("Listener2");
    DipatchBase<IListener> dispath;
    dispath.addListener(&l1);
    dispath.addListener(&l1);
    dispath.addListener(&l2);
    dispath.removeLister(&l1);
    dispath.dispatch(&IListener::OnPress,10,10);
    dispath.dispatch(&IListener::CallBack, "st","st");
    return a.exec();
}
