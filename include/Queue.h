#pragma once

#include <iostream>
#include <stdexcept>
#include <utility>
#include "..//include/tmatrix.h"


template <typename T>
class TQueue {
private:
    TDynamicVector<T> data; 
    size_t head;           
    size_t tail;            
    size_t count;           

public:
    TQueue(size_t initial_capacity = 10): data(initial_capacity), head(0), tail(0), count(0) {}

    bool IsEmpty() const 
    {
        return count == 0;
    }

    size_t GetSize() const 
    {
        return count;
    }

    void push(const T& el) 
    {
        if (count == data.size())
            Resize(data.size() * 2);

        data[tail] = el;
        tail = (tail + 1) % data.size();
        count++;
    }

    void push(T&& el) 
    {
        if (count == data.size())
            Resize(data.size() * 2);
       
        data[tail] = static_cast<T&&>(el);
        tail = (tail + 1) % data.size();
        count++;
    }

    T pop() 
    {
        if (IsEmpty()) 
            throw out_of_range("Queue is empty");
        
        T res = data[head];
        head = (head + 1) % data.size();
        count--;

        return res;
    }

    T& front() 
    {
        if (IsEmpty())
            throw out_of_range("Queue is empty");

        return data[head];
    }

    T& back() 
    {
        if (IsEmpty())
            throw out_of_range("Queue is empty");

        return data[(tail == 0 ? data.size() : tail) - 1];
    }

    void Clr() 
    {
        head = 0;
        tail = 0;
        count = 0;
    }

private:
    void Resize(size_t newCapacity) 
    {
        TDynamicVector<T> newData(newCapacity);

        for (size_t i = 0; i < count; ++i) {
            newData[i] = data[(head + i) % data.size()];
        }

        data = static_cast<TDynamicVector<T>&&>(newData); 
        head = 0;
        tail = count;
    }
};