#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

std::mutex mtx;
std::condition_variable cv;
std::queue<int> data_queue;

const int MAX_SIZE = 10;

void producer() {
    for (int i = 0; i < 20; ++i) {
        std::unique_lock<std::mutex> lock(mtx);

        // 如果队列已满，等待消费者消费
        cv.wait(lock, [] { return data_queue.size() < MAX_SIZE; });

        // 生产数据
        std::this_thread::sleep_for(std::chrono::seconds(1));
        data_queue.push(i);
        std::cout << "Produced: " << i << std::endl;

        // 通知消费者
        cv.notify_one();
    }
}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);

        // 如果队列为空，等待生产者生产
        cv.wait(lock, [] { return !data_queue.empty(); });

        // 消费数据
        std::this_thread::sleep_for(std::chrono::seconds(1));
        int data = data_queue.front();
        data_queue.pop();
        std::cout << "Consumed: " << data << std::endl;

        // 通知生产者
        cv.notify_one();

        if (data == 19) break; // 结束条件
    }
}

int main() {
    std::thread prod(producer);
    std::thread cons(consumer);

    prod.join();
    cons.join();

    return 0;
}