class FooBar {
    condition_variable cv;
    mutex m;
    bool alt;
    int n;
    int i;
public:
    FooBar(int n) {
        this->n = n;
        this->alt = true;
        this->i = 0;
    }

    void foo(function<void()> printFoo) {
        
        while(true) {
            unique_lock<mutex>lock(m);
            cv.wait(lock, [&]{return alt || i >= n;});
            if(i >= n) return;
        	printFoo();
            this->alt = false;
            cv.notify_all();
        }
    }

    void bar(function<void()> printBar) {
        while(true) {
            unique_lock<mutex> lock(m);
            cv.wait(lock, [&]{return !alt || i >= n;});
            if(i >= n) return;
        	printBar();
            this->alt = true;
            this->i++;
            cv.notify_all();
        }
    }
};
