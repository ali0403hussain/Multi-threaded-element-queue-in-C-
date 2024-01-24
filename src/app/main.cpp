#include <iostream>
#include <thread>
#include "Queue.h"

using namespace std;

int main()
{
    Queue<int> queue(2);
    int pop_element;

    // Writing thread
    thread writingThread([&]() {
        if(queue.Push(1))
            cout << "Element Push : 1\n";
        if(queue.Push(2))
            cout << "Element Push : 2\n";
        if(queue.Push(3))
            cout << "Element Push : 3\n";
        if(queue.Push(4))
            cout << "Element Push : 4\n";
        if(queue.Push(5))
            cout << "Element Push : 5\n";
    });

    thread readingThread([&]() {
        if(queue.Pop(pop_element))
            cout << "Element Pop :" << pop_element <<endl;
        if(queue.Pop(pop_element))
            cout << "Element Pop :" << pop_element <<endl;
        if(queue.Pop(pop_element))
            cout << "Element Pop :" << pop_element <<endl;
        if(queue.Pop(pop_element))
            cout << "Element Pop :" << pop_element <<endl;
        if(queue.Pop(pop_element))
            cout << "Element Pop :" << pop_element <<endl;
        if(queue.Pop(pop_element))
            cout << "Element Pop :" << pop_element <<endl;
    });

    writingThread.join();
    readingThread.join();

    return 0;
}