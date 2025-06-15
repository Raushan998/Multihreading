#include<iostream>
#include<thread>
#include<chrono>
using namespace std;

void run(int count){
    while(count --> 0)
        cout<<"Hello World"<<endl;
    this_thread::sleep_for(chrono::seconds(5));
}

// int main(){
//     thread t1(run, 10);
//     cout<<"Main Function()"<<endl;
//     t1.join();
//     if(t1.joinable()) // checks whether the thread is joinable or not if it joinable then only join it.
//        t1.join();
//     // t1.join();
//     cout<<"Main After()"<<endl;
//     return 0;
// }


// Detach 
// This is used to detach the thread from the main thread.
// Always check before detaching the thread whether it is joinable or not otherwise it will end up in double detaching and 
// double detach() will result into program termination.
// If we detach thread and main function is returning then the detached thread execution is suspended.


int main(){
    thread t1(run, 10);
    cout<<"Main Function()"<<endl;
    if(t1.joinable())
       t1.detach();
    cout<<"Main After()"<<endl;
    this_thread::sleep_for(chrono::seconds(5));
    return 0;
}