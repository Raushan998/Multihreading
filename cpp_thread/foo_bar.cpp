#include <iostream>
#include <thread>
#include <functional>
using namespace std;

class FooBar {
private:
    int n;
    bool foo_turn = true;
    mutex mtx;
    condition_variable cv;
public:
    FooBar(int n_) : n(n_) {}

    void foo(function<void()> printFoo) {
        for (int i = 0; i < n; i++) {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [this]{return foo_turn;});
        	printFoo();
            foo_turn=false;
            lock.unlock();
            cv.notify_all();
        }
    }

    void bar(function<void()> printBar) {
        for (int i = 0; i < n; i++) {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [this] {return !foo_turn;});
        	printBar();
            foo_turn=true;
            lock.unlock();
            cv.notify_all();
        }
    }
    void printFoo() { 
        cout << "Foo\n"; 
    }
    void printBar() { 
        cout << "Bar\n"; 
    }
};

int main() {
    FooBar fb(5);

    auto cbFoo = function<void()>([&fb](){ fb.printFoo(); });
    auto cbBar = function<void()>([&fb](){ fb.printBar(); });

    thread t1(&FooBar::foo, &fb, cbFoo);
    thread t2(&FooBar::bar, &fb, cbBar);

    t1.join();
    t2.join();
    return 0;
}