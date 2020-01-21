#pragma once
#pragma warning (disable : 4996)
#include <cstring>

class ListNode {

	char *data;

	ListNode *prev;

	ListNode *next;

public:

	ListNode();//default constructor

	ListNode(char *_data);

	~ListNode(void);

	ListNode *get_prev();

	ListNode *get_next();

	void set_prev(ListNode *ptr);

	void set_next(ListNode *ptr);

	char *get_data();

	char *get_data() const;

	void set_data(char *data);

};
