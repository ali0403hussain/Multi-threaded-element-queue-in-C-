\mainpage Multi-threaded element queue in C++
1. Develop a class from scratch to queue a finite number of elements. This class will be used for
multi-threaded communication as follows:
- Reading thread pops elements while writing thread pushes elements.
- If the queue is empty, reading thread will block and wait for the next element.
- If the queue is full, writing thread will block and wait for another thread to remove an item.
Extra: The reading/writing threads should optionally block for a certain period of time. If the
action is successful within this time, true is returned, otherwise false.
The class interface should look like this:
```ruby
    class Queue<T> {
    Queue(int size) {...}
    void Push(T element) {...}
    T Pop() {...}
    int Count() {...} // Amount of elements stored now
    int Size() {...} // Max number of elements
    }
```
As an example implement the following in main():
```ruby
    New Queue<int>(2)
```
```bash
| Writing Thread | Queue | Reading Thread       |
|----------------|-------|----------------------|
| Push(1)        |   1   |                      |
|                |       | Pop() -> 1           |
| Push(2)        |   2   |                      |
| Push(3)        | 2,3   |                      |
| Push(4)//blocks| 2,3   |                      |
|                |  3    | Pop() -> 2           |
| //Released     |  3,4  |                      |
|                |  4    | Pop() -> 3           |
|                |       | Pop() -> 4           |
|                |       | Pop()//Blocks        |
| Push(5)        | 5     |                      |
|                |       | Pop() -> 5//Release  |
```

## How to Run Solution
Run Makefile in linux

### Files Tree
```bash
├── cmake
│   ├── addlibUseFetch.cmake
│   ├── sanitizers.cmake
│   └── warnings.cmake
├── docs
│   ├── Doxyfile
│   └── Readme.md
├── external
│   └── googletest
│       ├── googletest-build
│       ├── googletest-src
│       └── googletest-subbuild
├── src
│   ├── CMakeLists.txt
│   ├── app
│   │   ├── CMakeLists.txt
│   │   └── main.cpp
│   └── lib
│       ├── CMakeLists.txt
│       ├── inc
│       │   └── Queue.h
│       └── queue
│           ├── CMakeLists.txt
│           └── Queue.cpp
└── test
│   ├── CMakeLists.txt    
│   └── Test.cpp   
│             
├── CMakeLists.txt
└── Makefile
```