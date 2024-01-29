#pragma once

template<class T>
class QueueADT
{
public:
    virtual bool isEmpty() = 0;
    virtual bool enqueue(const T& item) = 0;
    virtual bool dequeue(T& item) = 0;
    virtual bool peek(T& item) = 0;
    virtual ~QueueADT()
    {}
};
