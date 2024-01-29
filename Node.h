#pragma once

template < class T>
class Node
{
private:
	T data;
    float priority;
	Node<T>* next;
public:
	Node()
	{
		next = nullptr;
		priority = 0;
	}
	Node(const T& item)
	{
		data = item;
		next = nullptr;
		priority = 0;
	}
	Node(const T& item, Node<T>* ptr)
	{
		data = item;
		next = ptr;
		priority = 0;
	}
	Node(const T& item, Node<T>* ptr,int p)
	{
		data = item;
		next = ptr;
		priority = p;
	}
	void setItem(const T& item)
	{
		data = item;
	}
	void setpriority(float p)
	{
		priority = p;
	}
	void setNext(Node<T>* ptr)
	{
		next = ptr;
	}
	T getItem()
	{
		return data;
	}
	Node<T>* getNext()
	{
		return next;
	}
	float getpriority()
	{
		return priority;
	}
};


