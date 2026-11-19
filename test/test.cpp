#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <gtest/gtest.h>
#include "Stack.h"
#include "BracketsSolver.h"
#include <string>
#include "Queue.h"

TEST(StackTest, Initialization) 
{
    TStack<int> st(5);

    EXPECT_TRUE(st.IsEmpty());
    EXPECT_FALSE(st.IsFull());
    EXPECT_EQ(st.GetSize(), 0);
}

TEST(StackTest, PushAndSize) 
{
    TStack<int> st(3);
    st.push(10);
    st.push(20);

    EXPECT_EQ(st.GetSize(), 2);
    EXPECT_EQ(st.top(), 20); 
}

TEST(StackTest, PopLIFO) 
{
    TStack<int> st(3);
    st.push(1);
    st.push(2);
    st.push(3);

    EXPECT_EQ(st.pop(), 3);
    EXPECT_EQ(st.pop(), 2);
    EXPECT_EQ(st.pop(), 1);
    EXPECT_TRUE(st.IsEmpty());
}


TEST(StackTest, OverflowThrows) 
{
    TStack<int> st(2);
    st.push(1);
    st.push(2);

    EXPECT_TRUE(st.IsFull());
    EXPECT_THROW(st.push(3), std::out_of_range);
}

TEST(StackTest, UnderflowThrows) 
{
    TStack<int> st(2);

    EXPECT_TRUE(st.IsEmpty());
    EXPECT_THROW(st.pop(), std::out_of_range);
    EXPECT_THROW(st.top(), std::out_of_range);
}

TEST(StackTest, StringType) 
{
    TStack<std::string> st(2);
    st.push("Hello");
    st.push("World");

    EXPECT_EQ(st.pop(), "World");
    EXPECT_EQ(st.pop(), "Hello");
}

TEST(StackTest, CopyConstructorDeepCopy) 
{
    TStack<int> st1(3);
    st1.push(10);
    st1.push(20);

    TStack<int> st2(st1); 

    EXPECT_EQ(st2.GetSize(), 2);
    EXPECT_EQ(st2.top(), 20);

    st1.pop();
    st1.push(30);

    EXPECT_EQ(st2.GetSize(), 2);
    EXPECT_EQ(st2.top(), 20);
}

TEST(StackTest, CopyAssignment) 
{
    TStack<int> st1(3);
    st1.push(1);

    TStack<int> st2(5);
    st2.push(100);
    st2.push(200);

    st2 = st1;

    EXPECT_EQ(st2.GetSize(), 1);
    EXPECT_EQ(st2.top(), 1);

    st2 = st2;
    EXPECT_EQ(st2.GetSize(), 1);
}

TEST(StackTest, MoveConstructor) 
{
    TStack<int> st1(3);
    st1.push(10);
    st1.push(20);

    TStack<int> st2(std::move(st1));

    EXPECT_EQ(st2.GetSize(), 2);
    EXPECT_EQ(st2.top(), 20);

    EXPECT_EQ(st1.GetSize(), 0);
    EXPECT_TRUE(st1.IsEmpty());
}

TEST(StackTest, MoveAssignment) 
{
    TStack<int> st1(3);
    st1.push(10);

    TStack<int> st2(5);
    st2.push(100);

    st2 = std::move(st1);

    EXPECT_EQ(st2.GetSize(), 1);
    EXPECT_EQ(st2.top(), 10);

    EXPECT_TRUE(st1.IsEmpty());
    EXPECT_EQ(st1.GetSize(), 0);
}

//--------------------------------------------------------

TEST(BracketsTest, ValidSequences) 
{
    EXPECT_EQ(Brackets::Solve("(){}[]"), 0);
    EXPECT_EQ(Brackets::Solve("([{}])"), 0);
    EXPECT_EQ(Brackets::Solve(""), 0);
    EXPECT_EQ(Brackets::Solve("a + (b * c) - {d}"), 0);
}

TEST(BracketsTest, InvalidSequences) 
{
    EXPECT_EQ(Brackets::Solve("(]"), 1);

    EXPECT_EQ(Brackets::Solve("(()"), 1);

    EXPECT_EQ(Brackets::Solve("((("), 3);

    EXPECT_EQ(Brackets::Solve("())"), 1);

    EXPECT_EQ(Brackets::Solve(")("), 2);

}

//-------------------------------------------------
TEST(QueueTest, Initialization) 
{
    TQueue<int> q(5);

    EXPECT_TRUE(q.IsEmpty());
    EXPECT_EQ(q.GetSize(), 0);
}

TEST(QueueTest, PushAndPop) 
{
    TQueue<int> q(3);

    q.push(10);
    q.push(20);

    EXPECT_EQ(q.GetSize(), 2);
    EXPECT_EQ(q.front(), 10);
    EXPECT_EQ(q.back(), 20);

    EXPECT_EQ(q.pop(), 10);
    EXPECT_EQ(q.pop(), 20);
    EXPECT_TRUE(q.IsEmpty());
}

TEST(QueueTest, EmptyThrows) 
{
    TQueue<int> q(2);

    EXPECT_THROW(q.pop(), std::out_of_range);
    EXPECT_THROW(q.front(), std::out_of_range);
    EXPECT_THROW(q.back(), std::out_of_range);
}

TEST(QueueTest, ClearQueue) 
{
    TQueue<int> q(3);

    q.push(1);
    q.push(2);
    q.Clr();

    EXPECT_TRUE(q.IsEmpty());
    EXPECT_EQ(q.GetSize(), 0);

    q.push(3);
    EXPECT_EQ(q.pop(), 3);
}

TEST(QueueTest, StringType) 
{
    TQueue<std::string> q(2);

    q.push("Hello");
    q.push("World");

    EXPECT_EQ(q.pop(), "Hello");
    EXPECT_EQ(q.pop(), "World");
}

TEST(QueueTest, CircularWrapAround) 
{
    TQueue<int> q(3); 

    q.push(1);
    q.push(2);
    q.pop(); 

    q.push(3); 
    q.push(4); 

    EXPECT_EQ(q.pop(), 2);
    EXPECT_EQ(q.pop(), 3);
    EXPECT_EQ(q.pop(), 4);
}

TEST(QueueTest, MassivePushAndPop) 
{
    TQueue<int> q(2);
    const int N = 100000;

    for (int i = 0; i < N; ++i) {
        q.push(i);
    }
    EXPECT_EQ(q.GetSize(), N);

    for (int i = 0; i < N; ++i) {
        EXPECT_EQ(q.pop(), i);
    }
    EXPECT_TRUE(q.IsEmpty());
}

TEST(QueueTest, PushPopPingPong) {
    TQueue<int> q(10); 
    int push_val = 0;  
    int expected_pop = 0; 

    for (int i = 0; i < 100000; ++i) 
    {
        q.push(push_val++);
        q.push(push_val++);

        EXPECT_EQ(q.pop(), expected_pop++);

        q.push(push_val++);
        EXPECT_EQ(q.pop(), expected_pop++);
    }
}