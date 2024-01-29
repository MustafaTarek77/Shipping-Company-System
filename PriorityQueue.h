#pragma once
#include "Node.h"
#include<iostream>
using namespace std;

template <class T>
class PriorityQueue 
{
private:

	Node<T>* rear;
	Node<T>* front;
public:
	PriorityQueue();
	~PriorityQueue();
	bool isEmpty();
	bool peek(T& frntEntry);
	bool enqueue(const T& newEntry, const float& pr);
	bool dequeue(T& frntEntry);
	int getcount();
	void print();
};

template <class T>
PriorityQueue<T>::PriorityQueue()
{
	rear = NULL;
	front = NULL;
}

template <class T>
PriorityQueue<T>::~PriorityQueue()
{
	T temp;
	while (dequeue(temp));
}

template <class T>
bool PriorityQueue<T>::peek(T& frntEntry)
{
	if (isEmpty())
		return false;

	frntEntry = front->getItem();
	return true;
}

template <class T>
bool PriorityQueue<T>::isEmpty()
{
	return (front == NULL);
}

template <class T>
bool PriorityQueue<T>::enqueue(const T& newEntry, const float& pr)
{
	Node<T>* newNodePtr = new Node<T>(newEntry,NULL, pr);
	if (isEmpty())
	{
		front =rear= newNodePtr;
		return true;
	}
	if (front && !front->getNext())
	{
		if (front->getpriority() < pr)
		{
			newNodePtr->setNext(front);
			front = newNodePtr;
		}
		else
		{
			front->setNext(newNodePtr);
			rear = newNodePtr;
		}
	}
	else 
	{
		bool test = true;
		Node<T>* tmp = front;
		Node<T>* prev = NULL;
		while (tmp&&test)
		{
			if (tmp->getpriority() >= pr)
			{
				prev = tmp;
				tmp = tmp->getNext();
			}
			else
				test=false;
		}
		if (tmp == NULL) 
		{
			rear->setNext(newNodePtr);
			rear = newNodePtr;
		}
		else if (tmp == front)
		{
			newNodePtr->setNext(front);
			front = newNodePtr;
		}
		else
		{
			newNodePtr->setNext(tmp);
			prev->setNext(newNodePtr);
		}
		return true;
	}
}

template <class T>
bool PriorityQueue<T>::dequeue(T& frntEntry)
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
int PriorityQueue<T>::getcount()
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
void PriorityQueue<T>::print()
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


