#include <iostream>
#include<vector>
#include <thread>
using namespace std;

void helloWorld(){
    cout<<"HelloWorld"<<endl;
}

int main(){
    // cout<<this_thread::get_id()<<endl;
    int n = thread::hardware_concurrency();
    cout<<"Hardware Concurrency = "<<n<<endl;
    vector<thread> threads;
    for(int i=0;i<5;i++){
        threads.push_back(thread(helloWorld));
    }
    for(int i=0;i<5;i++){
        threads[i].join();
    }
    return 0;
}






