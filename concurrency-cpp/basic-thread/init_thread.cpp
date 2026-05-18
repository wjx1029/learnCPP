
#include <iostream>
#include <thread>


void thread_work1(std::string str) {
    std::cout << std::this_thread::get_id() << " str is: " << str << std::endl;
}

class background_task {
public:
    void operator()(std::string str) {
        std::cout << std::this_thread::get_id() << " str is: " << str << std::endl;
    }
};

auto lambda_task = [](std::string str) {
    std::cout << std::this_thread::get_id() << " str is: " << str << std::endl;
};


int main() {
    std::string hellostr = "hello world!";
    
    std::thread t1(thread_work1, hellostr);

    std::thread t2{background_task{}, hellostr};

    std::thread t3((background_task()), hellostr);

    std::thread t4(lambda_task, hellostr);

    // 通过join，让主线程等待子线程启动运行，子线程运行结束后主线程再运行。
    t1.join();
    t2.join();
    t3.join();
    t4.join();
}