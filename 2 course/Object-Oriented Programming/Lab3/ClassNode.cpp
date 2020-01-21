#include "ClassNode.h"
#include <iostream>

ListNode::ListNode()
{
	data = nullptr;
	prev = nullptr;
	next = nullptr;
}

ListNode::ListNode(char *_data)
{
	data = new char[strlen(_data) + 1];
	strcpy(data, _data);

	prev = nullptr;
	next = nullptr;
}

ListNode::~ListNode()
{
	if (data != nullptr) 
	{
		delete[] data;
	}
	
	data = nullptr;
	prev = nullptr;
	next = nullptr;
}

ListNode *ListNode::get_next()
{
	return next;
}

ListNode *ListNode::get_prev()
{
	return prev;
}

char *ListNode::get_data()
{
	char* _data = new char[strlen(data) + 1];
	strcpy(_data, data);
	return _data;
}

char *ListNode::get_data() const
{
	return data;
}

void ListNode::set_prev(ListNode *ptr)
{
	prev = ptr;
}

void ListNode::set_next(ListNode *ptr)
{
	next = ptr;
}

void ListNode::set_data(char *_data)
{
	data = new char[strlen(_data) + 1];
	strcpy(data, _data);
}