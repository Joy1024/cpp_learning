#include <iostream>
#include <thread>
#include <chrono>
#include <memory>


void task(){
    for (int i = 0; i < 5; ++i)
    {
        std::cout << "Task:" << i<< " is working..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
};

class Worker {
public:
    Worker(){
        std::cout << "Create Worker..." << std::endl;
        t = std::make_unique<std::jthread>(task);
    }
private:
   std::unique_ptr<std::jthread> t; // 自动合流的线程
};

int main()
{
    {
        auto w = std::make_unique<Worker>();
        std::cout << "Worker created is:" << w.get() << std::endl;
    } // leave scope of worker.
    // w.reset();
    std::cout << "Main thread finished!" << std::endl;
    return 0;
}