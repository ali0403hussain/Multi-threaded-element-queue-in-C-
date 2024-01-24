#include <iostream>
#include <thread>
#include <chrono>
#include <gtest/gtest.h>

#include "Queue.h"

/**
 * @brief TEST for handling Queue size
 * 
 */
TEST(QueueTest, QueueSize)
{
    //!Testing -ive Queue size
    Queue<int> que1(-2);
    EXPECT_EQ(que1.Size(), que1.queue_default_size);

    //!Testing 0 Queue size
    Queue<int> que2(0);
    EXPECT_EQ(que2.Size(), que2.queue_default_size);

    //!Testing +ive Queue size
    Queue<int> que3(10);
    EXPECT_EQ(que3.Size(), 10);
}

/**
 * @brief Test for Handling Data
 * 
 */
TEST(QueueTest, PushPop)
{
    int elementPop, elementPush;

    //!Testing Push and Pop over Int Range i.e -2147483648 to 2147483647
    Queue<int> que4(10);

    elementPush = -2147483648;
    EXPECT_EQ(que4.Push(elementPush), true);
    EXPECT_EQ(que4.Pop(elementPop), true);
    EXPECT_EQ(elementPop, elementPush);

    elementPush = -20000;
    EXPECT_EQ(que4.Push(elementPush), true);
    EXPECT_EQ(que4.Pop(elementPop), true);
    EXPECT_EQ(elementPop, elementPush);

    elementPush = -1;
    EXPECT_EQ(que4.Push(elementPush), true);
    EXPECT_EQ(que4.Pop(elementPop), true);
    EXPECT_EQ(elementPop, elementPush);

    elementPush = 0;
    EXPECT_EQ(que4.Push(elementPush), true);
    EXPECT_EQ(que4.Pop(elementPop), true);
    EXPECT_EQ(elementPop, elementPush);

    elementPush = 1;
    EXPECT_EQ(que4.Push(elementPush), true);
    EXPECT_EQ(que4.Pop(elementPop), true);
    EXPECT_EQ(elementPop, elementPush);

    elementPush = 20000;
    EXPECT_EQ(que4.Push(elementPush), true);
    EXPECT_EQ(que4.Pop(elementPop), true);
    EXPECT_EQ(elementPop, elementPush);

    elementPush = 2147483647;
    EXPECT_EQ(que4.Push(elementPush), true);
    EXPECT_EQ(que4.Pop(elementPop), true);
    EXPECT_EQ(elementPop, elementPush);
}

/**
 * @brief Test for checking Full Queue Timeout
 * 
 */
TEST(QueueTest, QueueFullTimeout)
{
    int elementPush;

    Queue<int> que5(1);

    elementPush = 1;
    EXPECT_EQ(que5.Push(elementPush), true);

    elementPush = 2;
    bool status;

    auto start = std::chrono::high_resolution_clock::now();
    status = que5.Push(elementPush);
    auto end = std::chrono::high_resolution_clock::now();

    EXPECT_FALSE(status);
    EXPECT_EQ(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(), que5.timeout);
}

/**
 * @brief Test for checking Empty Queue Timeout
 * 
 */
TEST(QueueTest, QueueEmptyTimeout)
{
    int elementPop;

    Queue<int> que6(4);

    bool status;

    auto start = std::chrono::high_resolution_clock::now();
    status = que6.Pop(elementPop);
    auto end = std::chrono::high_resolution_clock::now();

    EXPECT_FALSE(status);
    EXPECT_EQ(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(), que6.timeout);
}

/**
 * @brief Test for checking Queue Thread Synchronization
 * 
 */
TEST(QueueTest, QueueThreadSynchronization)
{
    Queue<int> queS(2);
    int arrelementPush[] {1,2,3,4,5}, elementPop;
    bool status;
    int alterPush {0}, alterPop {0};

    std::thread Writer([&]() {
        status = queS.Push(arrelementPush[alterPush++]);
        status = queS.Push(arrelementPush[alterPush++]);
        status = queS.Push(arrelementPush[alterPush++]);
        status = queS.Push(arrelementPush[alterPush++]);
        EXPECT_TRUE(status);
        status = queS.Push(arrelementPush[alterPush]);
    });

    std::thread Reader([&]() {
        status = queS.Pop(elementPop);
        EXPECT_EQ(elementPop, arrelementPush[alterPop++]);
        status = queS.Pop(elementPop);
        EXPECT_EQ(elementPop, arrelementPush[alterPop++]);
        status = queS.Pop(elementPop);
        EXPECT_EQ(elementPop, arrelementPush[alterPop++]);
        status = queS.Pop(elementPop);
        EXPECT_EQ(elementPop, arrelementPush[alterPop++]);
        status = queS.Pop(elementPop);
        EXPECT_TRUE(status);
        EXPECT_EQ(elementPop, arrelementPush[alterPop]);
    });

    Writer.join();
    Reader.join();
}