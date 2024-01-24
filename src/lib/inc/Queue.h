#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <mutex>
#include <condition_variable>

/*! Queue Class: Using Circular Queue */
template <typename T> class Queue{
    private:
        T *ptrQueue ;                                    //Pointer to Queue Elements
        int queue_size;                                  //Size of Queue
        int front;                                       //Front for Pop
        int rear;                                        //Rear for Push
        int current_size;                                //For number of elements in queue

        std::mutex Mutex;                
        std::condition_variable new_queue_notify;

        bool IsQueueEmpty();                            //Private method for checking Queue Empty
        bool IsQueueFull();                             //Private method for checking Queue Full
    public:
        const int timeout {1000};
        const int queue_default_size {5};
        
        Queue();                                        //No-args constructor
        Queue(const int size);                          //Single Argument Constructor
        Queue(const Queue &source);                     //Copy Constructor
        Queue(Queue &&source);                          //Move Constructor
        bool Push(T elements);                          //Method For pushing elements
        bool Pop(T& element_args);                      //Method for Pop elements from Queue
        int Count() const;                              //Method for counting size of elements in Queue
        int Size() const;                               //Method for getting size of Queue
        ~Queue();                                       //Destructor
};

#endif