
///////////////Basic thread and join with main thread //////
#include <iostream>
#include <thread>
using namespace std;
  
// create a function
void display(){
    long long num = 0;
    for(int i=0;i<1000000000;i++){
        num+= i%2 == 0 ? i : 0;
    }
    cout << num << endl;
}
  
int main()
{
    thread t1(display);
    thread t2(display);
    t1.join();
    //t2.join();

    cout << "From Main Thread" << endl;
    return 0;
}

////////////////////////////////////////