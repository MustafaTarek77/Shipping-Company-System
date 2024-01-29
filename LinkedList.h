#include"Node.h"
#include<iostream>
using namespace std;
class Main;

template<class T>
class LinkedList {
private:
	Node<T>* Head;
public:
	LinkedList() {
		Head = nullptr;

	}
	bool isEmpty() 
	{
		if (Head == NULL)
			return true;
		else 
			return false;
	}
	void insertfirst(const T& newvalue) 
	{
		Node<T>* tmp = new Node<T>;
		tmp->setItem(newvalue);
		tmp->setNext(Head);
		Head = tmp;
	}

	void display() 
	{
		if (isEmpty())
			return;
		Node<T>* tmp = Head;
		if (tmp && !tmp->getNext())
		{
			cout << tmp->getItem();
			return;
		}
		while (tmp && tmp->getNext())
		{
			cout <<tmp->getItem()<< ",";
			tmp = tmp->getNext();
		}
		cout << tmp->getItem();
	}
	int count(const T& data)
	{
		Node<T>* tmp = Head;
		int count = 0;
		while (tmp) {
			if (tmp->getItem() == data)
				count++;
			tmp = tmp->getNext();
		}
		return count;
	}

	T search(T value)
	{
		Node<T>* tmp = Head;
		while (tmp)
		{
			if (*(tmp->getItem()) == value)
				return tmp->getItem();
			tmp = tmp->getNext();
		}
		return nullptr;
	}

	void insertbefore(const T& item, const T& newvalue) 
	{
		if (isFound(item)) {
			Node<T>* ptr = new Node(newvalue);
			Node<T>* tmp = Head;
			while (tmp && tmp->getNext() != item) {
				tmp = tmp->getNext();
			}
			ptr->setNext(tmp);
			tmp->setNext(ptr);
		}
	}
	void insertend(const T& newvalue)
	{
		if (isEmpty())
			insertfirst(newvalue);
		else 
		{
			Node<T>* ptr = Head;
			while (ptr->getNext()) 
			{
				ptr = ptr->getNext();
			}
			Node<T>* newnode = new Node<T>(newvalue);
			ptr->setNext(newnode);
			newnode->setNext(NULL);
		}
	}

	bool Remove(const T& item)
	{
		if (isEmpty())
			return false;
		Node<T>* deleteptr = Head;
		if (Head->getItem() == item) 
		{
			Head = Head->getNext();
			delete deleteptr;
			return true;
		}
		else
		{
			Node<T>* prev = NULL;
			while (deleteptr->getItem() != item) 
			{
				prev = deleteptr;
				deleteptr = deleteptr->getNext();
			}
			prev->setNext(deleteptr->getNext());
			delete deleteptr;
			return true;
		}
		return false;
	}

	T RemoveFirst()
	{
		if (isEmpty())
			return NULL;
		Node<T>* deleteptr = Head;
		Head = Head->getNext();
		T item = deleteptr->getItem();
		delete deleteptr;
		return item;
	}

	T Peek()
	{
		if (isEmpty())
			return NULL;
		return Head->getItem();
	}

	int getcount()
	{
		Node<T>* tmp = Head;
		int count = 0;
		while (tmp) {
			count++;
			tmp = tmp->getNext();
		}
		return count;
	}

};