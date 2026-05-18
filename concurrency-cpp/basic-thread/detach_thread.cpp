
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>


struct func {
    // int _i;

    // func(int i): _i(i) {}

    std::shared_ptr<int> _i_ptr;

    func(std::shared_ptr<int> i_ptr): _i_ptr(i_ptr) {}

    void operator()() {
        for (int i = 0; i < 3; i++) {
            *_i_ptr = i;
            std::cout << "_i is " << *_i_ptr << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
};

void oops() {
    auto some_local_state = std::make_shared<int>(0);
    func myfunc(some_local_state);
    std::thread functhread(myfunc);

    // 线程允许采用分离的方式在后台独自运行
    functhread.detach();
}

class thread_guard {
private:
    std::thread& _t;
public:
    explicit thread_guard(std::thread& t):_t(t){}
    ~thread_guard() {
        //join只能调用一次
        if (_t.joinable()) {
            _t.join();
        }
    }

    thread_guard(thread_guard const&) = delete;
    thread_guard& operator=(thread_guard const&) = delete;
};

void auto_guard() {
    auto some_local_state = std::make_shared<int>(0);
    func my_func(some_local_state);
    std::thread  t(my_func);
    thread_guard g(t);
    //本线程做一些事情
    std::cout << "auto guard finished " << std::endl;
}



int main() {
    
    oops();

    //防止主线程退出过快，需要停顿一下，让子线程跑起来detach
    std::this_thread::sleep_for(std::chrono::seconds(3));

    auto_guard();
}