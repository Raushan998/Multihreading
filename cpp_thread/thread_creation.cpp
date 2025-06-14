#include<iostream>
#include<thread>
using namespace std;

// void fun(int x){
//     while(x --> 0){
//         cout<<x<<endl;
//     }
// }

// int main(){
//     thread t1(fun, 10);
//     t1.join();
//     return 0;
// }

// 2. Lambda Function
// Example:

// int main(){
// We can directly inject lambda at thread creation time.
//     auto fun = [](int x){
//         while(x --> 0){
//             cout<<x<<endl;
//         }
//     };
//     thread t(fun, 10);
//     t.join();
//     return 0;
// }

// 3. Functor (Function Object)

// class Base{
//     public:
//      void operator()(int x){
//         while(x-->0){
//             cout<<x<<endl;
//         }
//      }
// };

// int main(){
//     thread t(Base(), 10);
//     t.join();
//     return 0;
// }

// 4. Non-static member function

// class Base{
//     public:
//       void run(int x){
//         while(x-->0){
//             cout<<x<<endl;
//         }
//       }
// };

// int main(){
//     Base b;
//     thread t(&Base::run, &b, 10);
//     t.join();
//     return 0;
// }

// 5. Static Member Function

// class Base{
//     public:
//       static void run(int x){
//         while(x-->0){
//             cout<<x<<endl;
//         }
//       }
// };

// int main(){
//     thread t(&Base::run, 10);
//     t.join();
//     return 0;
// }