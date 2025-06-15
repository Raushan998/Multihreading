#include <iostream>
#include <thread>
#include <chrono>
#include <future>

using namespace std;
typedef unsigned long long ull;

ull calculate_odd_sum(ull start, ull end){
    ull sum = 0;
    while(start != end){
        if(start % 2 != 0){
            sum += start;
        }
        start++;
    }
    return sum;
}

ull calculate_even_sum(ull start, ull end){
    ull sum = 0;
    while(start != end){
        if(start % 2 == 0){
            sum += start;
        }
        start++;
    }
    return sum;
}

int main(){
    ull start = 0, end = 100000;

    // Create promises and futures
    promise<ull> oddPromise, evenPromise;
    future<ull> oddFuture = oddPromise.get_future();
    future<ull> evenFuture = evenPromise.get_future();

    auto startTime = chrono::high_resolution_clock::now();

    // Launch threads
    thread t1([&]() {
        oddPromise.set_value(calculate_odd_sum(start, end));
    });

    thread t2([&]() {
        evenPromise.set_value(calculate_even_sum(start, end));
    });

    // Wait for results
    ull oddSum = oddFuture.get();
    ull evenSum = evenFuture.get();

    t1.join();
    t2.join();

    auto stopTime = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stopTime - startTime);

    cout << "Odd Sum = " << oddSum << endl;
    cout << "Even Sum = " << evenSum << endl;
    cout << "Time taken = " << duration.count() << " ms" << endl;
    return 0;
}
