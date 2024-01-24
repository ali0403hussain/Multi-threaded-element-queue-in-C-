#include <iostream>
#include <chrono>
#include "Queue.h"

/**
 * @brief Queue object No-args Constructor
 * 
 * @tparam T 
 */
template <typename T>
Queue<T>::Queue()
:queue_size{queue_default_size}, 
ptrQueue{nullptr}                                          
{
    ptrQueue = new T[queue_size];                    //Creating memory for elements of type T in heap
    front = -1;                                      //Initialize front rear point with -1 it means no items are pushed yet.
    rear = -1;
    current_size = 0;
}

/**
 * @brief Queue object Oveloaded Constrcutor
 * 
 * @tparam T 
 * @param size_arg 
 */
template <typename T>
Queue<T>::Queue(const int size_arg)
:ptrQueue{nullptr}
{
    //! Queue size cant be -ive or zero.
    if(size_arg <= 0)                           
    {
        queue_size = queue_default_size;
    }
    else
    {
        queue_size = size_arg;
    }
    
    ptrQueue = new T[queue_size];
    front =  -1;
    rear = -1;
    current_size = 0; 
}

/**
 * @brief Queue object Copy Constructor
 * 
 * @tparam T 
 * @param source 
 */
template <typename T>
Queue<T>::Queue(const Queue &source)
:ptrQueue{nullptr},
queue_size{source.queue_size},
front{source.front},
rear{source.rear},
current_size{source.current_size}
{
    this->ptrQueue = new T[source.queue_size];
    if(ptrQueue)
    {
        for(size_t alter = 0; alter < queue_size; alter++)
        {
            ptrQueue[alter] = source.ptrQueue[alter];
        }
    }
}

/**
 * @brief Queue object Move Constructor
 * 
 * @tparam T 
 * @param source 
 */
template <typename T>
Queue<T>::Queue(Queue &&source)
:ptrQueue{source.ptrQueue},
queue_size{source.queue_size},
front{source.front},
rear{source.rear},
current_size{source.current_size}
{
    source.ptrQueue = nullptr;
    source.queue_size = 0;
    source.front = 0;
    source.rear = 0;
    source.current_size = 0;
}

/**
 * @brief Push Member Method for insertion of element in queue
 * 
 * @tparam T 
 * @param element Template
 * @return bool
 */
template <typename T>
bool Queue<T>::Push(T element)
{
    std::unique_lock<std::mutex> lock(Mutex);
    
    auto queue_full = [this] { return !IsQueueFull(); };
    new_queue_notify.wait_for(lock, std::chrono::milliseconds(timeout), queue_full);

    if(IsQueueFull())                  
    {
        return false;
    }

    if(front == -1)
    {
        front = 0;
        rear = 0;
    }
    else
    {
        rear = (rear + 1) % queue_size;     //Controlling  Queue Circular
    }

    ptrQueue[rear] = element;
    current_size++;

    new_queue_notify.notify_all();

    return true;
}

/**
 * @brief Pop Member Method for deletion of element in queue
 * 
 * @tparam T
 * @param  element_args Template
 * @return bool 
 */
template <typename T>
bool Queue<T>::Pop(T& element_args)
{
    std::unique_lock<std::mutex> lock(Mutex);
    
    auto queue_empty = [this] { return !IsQueueEmpty(); };
    new_queue_notify.wait_for(lock, std::chrono::milliseconds(timeout), queue_empty);

    if(IsQueueEmpty())                   
    {
        return false;
    }

    element_args = ptrQueue[front];

    if(front == rear)
    {
        front = -1;
        rear = -1;
    }
    else
    {
        front = (front + 1) % queue_size;
    }
    
    current_size--;
    return true;
}

/**
 * @brief Count Member Method for counting total elements in Queue
 * 
 * @tparam T 
 * @return int 
 */
template <typename T>
int Queue<T>::Count() const
{
    return current_size;
}

/**
 * @brief Size Member Method for finding the size of queue
 * 
 * @tparam T 
 * @return int 
 */
template <typename T>
int Queue<T>::Size() const
{
    return queue_size;
}

/**
 * @brief Queue object Destructor
 * 
 * @tparam T 
 */
template <typename T>
Queue<T>::~Queue()
{
    delete [] ptrQueue;
}

/**
 * @brief Private Method to check if Queue is Empty or not
 * 
 * @tparam T 
 * @return bool
 */
template <typename T>
bool Queue<T>::IsQueueEmpty()
{
    if(current_size == 0)
    {
        std::cout<<"Queue is Empty\n";
        return true;
    }
    else
    {
        return false;
    }                
}

/**
 * @brief Private Method to check if Queue is Full or not
 * 
 * @tparam T 
 * @return bool
 */
template <typename T>
bool Queue<T>::IsQueueFull()
{
    if(current_size == queue_size)
    {
        std::cout<<"Queue is Full\n";
        return true;
    }
    else
    {
        return false;
    }                
}


//! Explicitly instantiate the template.
/*! because the defination is not in header file */
template class Queue<int>;
//template class Queue<long int>;
//template class Queue<float>;
//template class Queue<double>;
//template class Queue<std::string>;