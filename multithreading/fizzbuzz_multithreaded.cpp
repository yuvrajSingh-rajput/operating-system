class FizzBuzz {
    condition_variable cv;
    mutex m;
    int n;
    int i;
public:
    FizzBuzz(int n) {
        this->n = n;
        this->i = 1;
    }

    void fizz(function<void()> printFizz) {
        while (true) {
            unique_lock<mutex> lock(m);
            cv.wait(lock, [&]{ return (i > n) || (i % 3 == 0 && i % 5 != 0); });
            if (i > n) return;
            printFizz();
            i++;
            cv.notify_all();
        }
    }

    void buzz(function<void()> printBuzz) {
        while (true) {
            unique_lock<mutex> lock(m);
            cv.wait(lock, [&]{ return (i > n) || (i % 5 == 0 && i % 3 != 0); });
            if (i > n) return;
            printBuzz();
            i++;
            cv.notify_all();
        }
    }

    void fizzbuzz(function<void()> printFizzBuzz) {
        while (true) {
            unique_lock<mutex> lock(m);
            cv.wait(lock, [&]{ return (i > n) || (i % 15 == 0); });
            if (i > n) return;
            printFizzBuzz();
            i++;
            cv.notify_all();
        }
    }

    void number(function<void(int)> printNumber) {
        while (true) {
            unique_lock<mutex> lock(m);
            cv.wait(lock, [&]{ return (i > n) || (i % 3 != 0 && i % 5 != 0); });
            if (i > n) return;
            printNumber(i);
            i++;
            cv.notify_all();
        }
    }
};
