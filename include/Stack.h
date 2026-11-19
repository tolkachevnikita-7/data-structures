#pragma once

#include <iostream>
using namespace std;

const int MAX_STACK_SIZE = 100000000;

template <typename T>
class TStack {
private:

    int top_i;
    size_t size;
    T* pMem;

public:
    TStack(int s = 10)
    {
        if (s <= 0)
            throw out_of_range("Stack size should be greater than zero");
        if (s >= MAX_STACK_SIZE)
            throw out_of_range("Stack size should be less than MaxSize");

        size = s;
        top_i = -1;
        pMem = new T[size];
    }

    // конструктор копирования
    TStack(const TStack& s)
    {
        size = s.size;
        top_i = s.top_i;
        pMem = new T[size];

        for (int i = 0; i <= top_i; ++i)
            pMem[i] = s.pMem[i];
    }

    // конструктор перемещения
    TStack(TStack&& s)
    {
        size = s.size;
        top_i = s.top_i;
        pMem = s.pMem;

        s.size = 0;
        s.top_i = -1;
        s.pMem = nullptr;
    }

    ~TStack()
    {
        delete[] pMem;

        pMem = nullptr;
        top_i = -1;
        size = 0;
    }

    // присваивание копирования
    TStack& operator=(const TStack& s)
    {
        if (this != &s) {

            T* newMem = new T[s.size];

            for (int i = 0; i <= s.top_i; ++i)
                newMem[i] = s.pMem[i];

            delete[] pMem;

            pMem = newMem;
            size = s.size;
            top_i = s.top_i;
        }
        return *this;
    }

    // перемещающее присваивание
    TStack& operator=(TStack&& s)
    {
        if (this != &s) {
            delete[] pMem;

            pMem = s.pMem;
            size = s.size;
            top_i = s.top_i;

            s.pMem = nullptr;
            s.size = 0;
            s.top_i = -1;
        }
        return *this;
    }

    bool operator==(const TStack& s) const
    {
        if (size != s.size)  return false;
        if (top_i != s.top_i) return false;

        for (int i = 0; i <= top_i; ++i)
            if (!(pMem[i] == s.pMem[i])) return false;

        return true;
    }

    bool operator!=(const TStack& s) const
    {
        return !(*this == s);
    }

    bool IsFull()  const
    {
        return top_i == size - 1;
    }

    bool IsEmpty() const
    {
        return top_i == -1;
    }

    size_t GetSize() const
    {
        return static_cast<size_t>(top_i + 1);
    }

    void push(const T& el)
    {
        if (IsFull()) throw out_of_range("Stack is full");

        pMem[++top_i] = el;
    }

    void push(T&& el)
    {
        if (IsFull()) throw out_of_range("Stack is full");

        pMem[++top_i] = static_cast<T&&>(el);
    }

    T pop()
    {
        if (IsEmpty()) throw out_of_range("Stack is empty");

        return pMem[top_i--];
    }

    T& top()
    {
        if (IsEmpty()) throw out_of_range("Stack is empty");

        return pMem[top_i];
    }
    const T& top() const
    {
        if (IsEmpty()) throw out_of_range("Stack is empty");

        return pMem[top_i];
    }

    void Clr()
    {
        top_i = -1;
    }

};