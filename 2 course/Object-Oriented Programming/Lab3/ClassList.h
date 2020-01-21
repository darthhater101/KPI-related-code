#include "ClassNode.h"
#include <iostream>
#include <cstdlib>

class DoublyLinkedList {

	ListNode *head;

public:

	DoublyLinkedList(void);

	~DoublyLinkedList(void);

	int size();

	bool empty();

	void clear();

	void push_back(const ListNode &);

	void push_front(const ListNode &);

	void pop_front();

	void pop_back();

	void insert_ord(const ListNode &);

	void sort();

	bool insert_after(char *dat, const ListNode &nd);

	void operator=(const DoublyLinkedList &);

	void merge(DoublyLinkedList &);

	void erase(char *dat);

	void unique();

	void assign(DoublyLinkedList &dl, int first, int last);

	void splice(int where, const DoublyLinkedList &dl);

	void splice(int where, const DoublyLinkedList &dl, int first, int last);

	void print();

	void print_bkw();

private:

	ListNode *search_by_index(int i);
	ListNode *search_by_index(int i) const;
	ListNode *delete_node(ListNode *nd);
	void swap(ListNode* a, ListNode* b);
};
