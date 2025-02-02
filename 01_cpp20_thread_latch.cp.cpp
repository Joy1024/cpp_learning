#include <iostream>
#include <latch>
#include <thread>
#include <vector>

constexpr int n = 3;

std::latch latch(n); // 等待 3 个线程

void worker(int id)
{
    std::cout << "Thread " << id << " is working..." << std::endl;
    latch.arrive_and_wait(); // 到达并等待
    std::cout << "Thread " << id << " finished!" << std::endl;
}

int main()
{
    std::vector<std::thread> threads;
    for (int i = 0; i < n; ++i)
    {
        threads.emplace_back(worker, i);
    }

    for (auto &t : threads)
    {
        t.join();
    }

    return 0;
}