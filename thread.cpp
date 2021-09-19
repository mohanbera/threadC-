
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

////////////// thread alone without main, daemon process ///

int main()
{
    thread t1(display);

    // We can make a new thread to run free to become a daemon process.
    t1.detach();

    cout << "From Main Thread" << endl;
    return 0;
}

// Once a thread detached, we cannot force it to join with 
//the main thread again. So, the following line of the code 
// is an error and the program will crash.

int main()
{
    std::thread t(&thread_function);
    std::cout << "main thread\n";
    // t.join();
    t.detach();
    t.join();   // Error
    return 0;
}

// Once detached, the thread should live that way forever.

// We can keep the code from crashing by checking using joinable(). Because it's not joinable,
//  the join() function won't be called, and the program runs without crash.

int main()
{
    std::thread t(&thread_function);
    std::cout << "main thread\n";
    // t.join();
    if(t.joinable()) 
        t.join(); 
    return 0;
}

#include <iostream>
#include <thread>
#include <string.h>
using namespace std;

void displayName(string name, int age){
    cout << name+" "+to_string(age) << endl;
    name += " Surname";
}

// Here is an example of passing parameter to a thread. In this case, we're just passing a string:

int main()
{
    string name = "Name";
    thread t1(&displayName, name, 22);
    t1.join();
    cout << name << endl;
    return 0;
}


// If we want to pass the string as a ref, we may want to try this:
// normal pass by reference does not work

#include <iostream>
#include <thread>
#include <string.h>
using namespace std;

void displayName(string& name, int age){
    cout << name+" "+to_string(age) << endl;
    name += " Surname";
}

int main()
{
    string name = "Name";
    thread t1(&displayName, ref(name), 22);
    t1.join();
    cout << name << endl;
    return 0;
}



