#ifndef TEST_TDOUBLY_QUEUE_H
#define TEST_TDOUBLY_QUEUE_H

#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include "TDoublyQueue.h"

TEST(TDoublyQueueTest, BasicOperations) {
    TDoublyQueue<int> deque;
    EXPECT_TRUE(deque.IsEmpty());
    EXPECT_EQ(deque.Size(), 0);

    deque.PushBack(10);
    deque.PushBack(20);
    deque.PushFront(5);

    EXPECT_FALSE(deque.IsEmpty());
    EXPECT_EQ(deque.Size(), 3);
    EXPECT_EQ(deque.Front(), 5);
    EXPECT_EQ(deque.Back(), 20);

    EXPECT_EQ(deque.PopFront(), 5);
    EXPECT_EQ(deque.PopBack(), 20);

    EXPECT_EQ(deque.Size(), 1);
    EXPECT_EQ(deque.Front(), 10);
}

TEST(TDoublyQueueTest, EmptyQueueExceptions) {
    TDoublyQueue<int> deque;
    EXPECT_THROW(deque.PopFront(), std::out_of_range);
    EXPECT_THROW(deque.PopBack(), std::out_of_range);
    EXPECT_THROW(deque.Front(), std::out_of_range);
    EXPECT_THROW(deque.Back(), std::out_of_range);
    EXPECT_TRUE(deque.IsEmpty());
}

TEST(TDoublyQueueTest, CopyAndClear) {
    TDoublyQueue<std::string> deque1;
    deque1.PushBack("Apple");
    deque1.PushBack("Banana");

    TDoublyQueue<std::string> deque2 = deque1;
    EXPECT_EQ(deque2.Size(), 2);
    EXPECT_EQ(deque2.Front(), "Apple");

    deque2.PopFront();
    EXPECT_EQ(deque2.Size(), 1);
    EXPECT_EQ(deque1.Size(), 2);
    EXPECT_EQ(deque1.Front(), "Apple");

    deque1.Clear();
    EXPECT_TRUE(deque1.IsEmpty());
    EXPECT_EQ(deque1.Size(), 0);
}

#endif // TEST_TDOUBLY_QUEUE_H