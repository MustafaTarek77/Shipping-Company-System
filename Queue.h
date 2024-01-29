#pragma once
#include "Node.h"
#include "QueueADT.h"
#include<iostream>
using namespace std;

template <class T>
class Queue :public QueueADT<T>
{
private:

	Node<T>* rear;
	Node<T>* front;
public:
	Queue();
	~Queue();
	bool isEmpty();
	bool peek(T& frntEntry);
	bool enqueue(const T& newEntry);
	bool dequeue(T& frntEntry);
	int getcount();
	void print();
};

template <class T>
Queue<T>::Queue()
{
	rear = nullptr;
	front = nullptr;
}

template <class T>
Queue<T>::~Queue()
{
	T temp;
	while (dequeue(temp));
}

template <class T>
bool Queue<T>::peek(T& frntEntry)
{
	if (isEmpty())
		return false;

	frntEntry = front->getItem();
	return true;

}

template <class T>
bool Queue<T>::isEmpty()
{
	return (front == nullptr);
}

template <class T>
bool Queue<T>::enqueue(const T& newEntry)
{
	Node<T>* newNodePtr = new Node<T>(newEntry);
	if (isEmpty())
		front = newNodePtr;
	else
		rear->setNext(newNodePtr);
	rear = newNodePtr;
	return true;
}

template <class T>
bool Queue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = front;
	frntEntry = front->getItem();
	front = front->getNext();
	if (nodeToDeletePtr == rear)
		rear = nullptr;
	delete nodeToDeletePtr;
	return true;
}

template<class T>
int Queue<T>::getcount()
{
	int count = 0;
	Node<T>* ptr = front;
	while (ptr)
	{
		count++;
		ptr = ptr->getNext();
	}
	return count;
}

template<class T>
void Queue<T>::print()
{
	if (isEmpty())
		return;
	Node<T>* tmp = front;
	if (tmp && !tmp->getNext())
	{
		cout << tmp->getItem();
		return;
	}
	while (tmp && tmp->getNext())
	{
		cout << tmp->getItem() << ",";
		tmp = tmp->getNext();
	}
	cout << tmp->getItem();
}
