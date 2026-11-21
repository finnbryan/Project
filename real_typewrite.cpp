#include <iostream>
#include <string>

//allows for slow print
#include <thread>
#include <chrono>


using namespace std;

void typewrite(const string &text, int delayMs)
{
    for (char c : text)
    {
        cout << c;
        this_thread :: sleep_for(chrono::milliseconds(delayMs));
    }
};


int main()
{
    typewrite("hello", 70);
    typewrite("you found a chest", 70);
    return 0;
}
