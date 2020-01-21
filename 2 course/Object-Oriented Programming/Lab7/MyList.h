#pragma once
#include "Iterator.h"
#include <iostream>
template <class T>
class List {

	struct ListNode {
		T data;
		ListNode * next;
		ListNode(const ListNode& lst) 
		{
			data = lst.data;
		}
		ListNode() {
			next = NULL;
		}
		ListNode(T dat) {
			data = dat;
		}
		void Print() {
			cout << data;
		}
	};

public:
	typedef ListNode node_type;
	typedef _iterator<node_type> iterator;
	//constructors / destructors
	List();
	~List();

	//methods
	iterator begin();//Returns an iterator addressing the first element 
	iterator end();//Returns an iterator that addresses the location 
   //succeeding the last element


	void clear();//Erases all the elements of a list.
	bool empty();//Tests if a list is empty.

	iterator find(const node_type & val);//Returns an iterator to the 
// first element in a list that 
//match a specified value.

	void pop_front();//Deletes the element at the beginning of a list.

	void push_front(const node_type val);//Adds an element to the beginning 
  //of a list.
	void remove(const node_type val);//Erases first element in a list that 
   //match a specified value.


	int size();//Returns the number of elements in a list.

	void splice(iterator _Where, List<T>& _Right);//Removes element from //the target list and inserts it in first
// position of the argument list.
	void	Print();//Dumps list into the screen

	iterator previous_item(const node_type &val);
private:

	node_type *head;
	iterator *first, *last;
	int len;
};

template <typename T>
List<T>::List()
{
	head = nullptr;
	first = nullptr;
	last = nullptr;
	len = 0;
}

template <typename T>
List<T>::~List()
{
	delete head;
	delete first;
	delete last;
}

template <typename T>
typename List<T>::iterator List<T>::begin()
{
	if (first == NULL)
		return NULL;
	return *first;
}

template <typename T>
typename List<T>::iterator List<T>::end()
{
	return *last;
}

template <typename T>
void List<T>::clear()
{
	while (head != NULL)
		pop_front();
}

template <typename T>
bool List<T>::empty()
{
	return len == 0;
}

template <typename T>
typename List<T>::iterator List<T>::find(const node_type & val)
{
	node_type *p = head;

	while (p != NULL)
	{
		if (p->data != val.data)
			p = p->next;
		else
			return p;
	}
}

template <typename T>
void List<T>::pop_front()
{
	if (head == NULL)
		return;

	remove(head->data);
}

template <typename T>
void List<T>::push_front(const node_type val)
{
	node_type *p = new node_type(val.data);

	p->next = NULL;

	if (head == NULL)
	{
		head = p;
		len = 1;
		head->next = NULL;
	}
	else
	{
		node_type *buff = head;
		head = p;
		head->next = buff;
		len++;
	}

	delete last;
	delete first;
	first = new iterator(head);
	node_type *end = head;
	while (end != NULL)
		end = end->next;
	last = new iterator(end);
}

template <typename T>
typename List<T>::iterator List<T>::previous_item(const node_type &val) 
{
	node_type *p = head;
	node_type *previous = p;

	while (p != NULL)
	{
		if (p->data != val.data)
		{
			previous = p;
			p = p->next;
		}
		else
			break;
	}

	return previous;
}

template <typename T>
void List<T>::remove(const node_type val)
{
	node_type *p = &(*find(val));

	node_type *p_before = &(*previous_item(val));


	if (p == p_before)
	{
		head = p->next;
		delete p;
		p = NULL;
	}
	else
	{
		p_before->next = p->next;
		delete p;
		p = NULL;
	}

	len--;

	delete last;
	delete first;
	first = new iterator(head);
	node_type *end = head;
	while (end != NULL)
		end = end->next;
	last = new iterator(end);
}

template <typename T>
int List<T>::size()
{
	return len;
}

template <typename T>
void List<T>::splice(iterator _Where, List<T>& _Right)
{
	if (_Where != NULL)
	{
		node_type buff = (*_Where).data;
		remove((*_Where).data);
		_Right.push_front(buff);
	}
	else
		cout << "Iterator == NULL(Splice)";

	return;
}

template <typename T>
void List<T>::Print()
{
	List<T>::node_type *p = head;
	while (p != NULL)
	{
		p->Print();
		p = p->next;
	}
}