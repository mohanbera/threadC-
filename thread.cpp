
// command to run a cpp file with thread inside it
// we need to specify a version >= 11 of c++

g++ -std=c++11 -pthread main.cpp

// then 

./a.out



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


// There is another way of passing the parameter without copying 
// and not sharing memory between the threads. We can use move():

#include <iostream>
#include <thread>
#include <string.h>
using namespace std;

void displayName(string name, int age){
    cout << name+" "+to_string(age) << endl;
    name += " Bera";
}

int main()
{
    string name = "Mohan";
    thread t1(&displayName, move(name), 22);
    t1.join();
    cout << "the name is "+name<< endl;
    cout << "the name length is " << name.length() << endl;
    return 0;
}

// output will be 
// Mohan 22
// the name is 
// the name length is 0

// Thread id
// We can get id information using this_thread::get_id():

int main()
{
    std::string s = "Name Surname";
    std::thread t(&thread_function, std::move(s));
    std::cout << "main thread message = " << s << std::endl;

    std::cout << "main thread id = " << std::this_thread::get_id() << std::endl;
    std::cout << "child thread id = " << t.get_id() << std::endl;

    t.join();
    return 0;
}

// output 

/*
thread function message is = Kathy Perry
main thread message =
main thread id = 1208
child thread id = 5224
*/

// How many threads?
// The thread library provides the suggestion for the number of threads:

int main()
{
    std::cout << "Number of threads = " 
              <<  std::thread::hardware_concurrency() << std::endl;
    return 0;
}

// output 
// Number of threads = 2


// lambda functions
// Since we're dealing with C11, let's take a little break for "lambda".

// We can replace the thread_function() with lambda function (anonymous function) like this:

int main()
{
    std::thread t([]()
    {
        std::cout << "thread function\n";
    }
    );
    std::cout << "main thread\n";
    t.join();     // main thread waits for t to finish
    return 0;
}

// Note that we are writing inline code and passing into another function which is a thread constructor.

// The lambda expression is a series of statements enclosed in braces, 
// prefixed with [], called lambda introducer or capture specification 
// which tells the compiler we're creating a lambda function, in our case, 
// taking no argument. So, in essence, we're using [](){} as a task, 
// and assigning it to our thread.

// if we want to access local variable inside the 
// lamda function then the variable nedd to be static other wise compile error

#include <iostream>
#include <thread>
#include <string.h>
using namespace std;


int main()
{
    // static things can be accessed within lamda funtion
    static string name = "Name Surname";

    thread t1([](){
        cout << "Hello World" + name << endl;
    });

    t1.join();
    return 0;
}

// 
