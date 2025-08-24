#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

class Foo {
private:
    std::mutex mtx;
    std::condition_variable cv;
    int state = 0; // 0: first, 1: second, 2: third

public:
    Foo() {}

    void first(std::function<void()> printFirst) {
        std::unique_lock<std::mutex> lock(mtx);
        printFirst();
        state = 1;
        cv.notify_all(); // Notify second()
    }

    void second(std::function<void()> printSecond) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]{ return state == 1; }); // Wait for first()
        printSecond();
        state = 2;
        cv.notify_all(); // Notify third()
    }

    void third(std::function<void()> printThird) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]{ return state == 2; }); // Wait for second()
        printThird();
    }
};
