class ZeroEvenOdd {
    condition_variable cv;
    mutex m;
    bool z;
    int n;
    int i;
public:
    ZeroEvenOdd(int n) {
        this->n = n;
        this->i = 1;
        this->z = true;
    }

    void zero(function<void(int)> printNumber) {
        while (true) {
            unique_lock<mutex> lock(m);
            cv.wait(lock, [&]{ return z || i > n; });
            if (i > n) break;
            printNumber(0);
            z = false;
            cv.notify_all();
        }
    }

    void even(function<void(int)> printNumber) {
        while (true) {
            unique_lock<mutex> lock(m);
            cv.wait(lock, [&]{ return (!z && i % 2 == 0) || i > n; });
            if (i > n) break;
            printNumber(i);
            i++;
            z = true;
            cv.notify_all();
        }
    }

    void odd(function<void(int)> printNumber) {
        while (true) {
            unique_lock<mutex> lock(m);
            cv.wait(lock, [&]{ return (!z && i % 2 == 1) || i > n; });
            if (i > n) break;
            printNumber(i);
            i++;
            z = true;
            cv.notify_all();
        }
    }
};
