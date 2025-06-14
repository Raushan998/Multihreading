#include <iostream>
#include <thread>
#include<vector>
// #include<bits/stdc++.h>

using namespace std;
class Person{
    public:
    string name, gender;
    Person(string name, string gender){
        this->name = name;
        this->gender = gender;
    }
};

class Bathroom{
    static const int MAX_CAPACITY = 3;
    public:
       string current_gender;
       int counter = 0;
       mutex mtx;
       condition_variable cv;

       Bathroom(){
         this->current_gender = "";
         this->counter = 0;
       }
       
       void use_bathroom(Person& person) {
            enter(person);
            this_thread::sleep_for(chrono::seconds(1));
            leave(person);
        }

       void enter(Person person){
            unique_lock<mutex> lock(mtx);
            while ( counter == MAX_CAPACITY
                || ( current_gender != person.gender && !current_gender.empty() ) ){
               cv.wait(lock);
           }
           counter += 1;
           cout<<person.name<<" is "<<person.gender<<" who is using the bathroom and also the counter is "<<counter<<endl;
           current_gender = person.gender;
       }

       void leave(Person person){
          unique_lock<mutex> lock(mtx);
          counter -= 1;
          cout<<person.name<<" is "<<person.gender<<" who has left the bathroom and also the counter is "<<counter<<endl;
          if(counter == 0){
            current_gender = "";
            cv.notify_all();
          }
          else{
            cv.notify_one();
          }
       }
};

int main(){
    vector<Person> people;
    for (int i = 0; i < 100; ++i) {
        people.emplace_back(
            (i % 2 == 0 ? "Jane" : "John") + to_string(i),
            i % 2 == 0 ? "female" : "male"
        );
    }

    Bathroom bathroom;
    vector<thread> threads;
    for (int i = 0; i < 100; ++i) {
        threads.emplace_back(&Bathroom::use_bathroom, &bathroom, ref(people[i]));
    }

    for (auto& t : threads) t.join();
    return 0;
}