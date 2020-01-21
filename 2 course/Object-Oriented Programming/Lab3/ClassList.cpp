#include "ClassList.h"

using namespace std;

DoublyLinkedList::DoublyLinkedList()
{
	head = NULL;
}

DoublyLinkedList::~DoublyLinkedList()
{
	clear();
}

int DoublyLinkedList::size()
{
	int count = 0;
	ListNode *tmp = head;
	while (tmp != nullptr)
	{
		count++;
		tmp = tmp->get_next();
	}

	return count;
}

bool DoublyLinkedList::empty()
{
	return head == NULL;
}

void DoublyLinkedList::clear()
{
	ListNode *tmp = head;
	ListNode *next;
	while (tmp != nullptr)
	{
		next = tmp->get_next();
		delete tmp;
		tmp = next;
	}
}

void DoublyLinkedList::push_back(const ListNode &nd)
{
	ListNode *node = new ListNode(nd.get_data());

	if (head == NULL)
	{
		head = node;
		return;
	}

	ListNode *tmp = head;

	while (tmp->get_next() != nullptr)
	{
		tmp = tmp->get_next();
	}

	tmp->set_next(node);
	node->set_prev(tmp);
}

void DoublyLinkedList::push_front(const ListNode &nd)
{
	ListNode *node = new ListNode(nd.get_data());

	node->set_next(head);

	if (head != NULL)
		head->set_prev(node);

	head = node;

}

void DoublyLinkedList::pop_back()
{

	if (head == NULL) return;

	ListNode *tmp = head;

	while (tmp->get_next() != nullptr)
	{
		tmp = tmp->get_next();
	}
	if (tmp->get_prev() != nullptr)
	{
		tmp->get_prev()->set_next(nullptr);
	}
	delete tmp;
}

void DoublyLinkedList::pop_front()
{
	if (head == NULL) return;

	ListNode *tmp = head;

	if (head->get_next() != NULL)
	{
		head->get_next()->set_prev(nullptr);
	}

	head = head->get_next();

	delete tmp;
}

ListNode *DoublyLinkedList::search_by_index(int i)
{
	ListNode *tmp = head;

	for (int n = 0; n < i; n++)
	{
		tmp = tmp->get_next();
	}

	return tmp;
}

ListNode *DoublyLinkedList::search_by_index(int i) const
{
	ListNode *tmp = head;

	for (int n = 0; n < i; n++)
	{
		tmp = tmp->get_next();
	}

	return tmp;
}

void DoublyLinkedList::swap(ListNode* a, ListNode* b)
{
	char* data = a->get_data();
	a->set_data(b->get_data());
	b->set_data(data);
}

void DoublyLinkedList::sort()
{
	if (head == NULL) return;

	for (int i = 0; i < size(); i++)
	{
		for (int j = 0; j < size() - 1; j++)
		{
			if (strcmp(search_by_index(j)->get_data(), search_by_index(j + 1)->get_data()) == 1)
			{
				swap(search_by_index(j), search_by_index(j + 1));
			}
		}
	}

}

bool DoublyLinkedList::insert_after(char *dat, const ListNode &nd)
{
	ListNode *node = new ListNode(nd.get_data());

	ListNode *tmp = head;

	while (tmp != nullptr)
	{
		if (strcmp(tmp->get_data(), dat) == 0)
		{
			node->set_next(tmp->get_next());
			tmp->get_next()->set_prev(node);
			tmp->set_next(node);
			node->set_prev(tmp);
			return true;
		}
		tmp = tmp->get_next();
	}

	if (tmp == nullptr) return false;
}

void DoublyLinkedList::insert_ord(const ListNode &nd)
{
	push_back(nd);
	sort();
}

void DoublyLinkedList::operator=(const DoublyLinkedList &nd)
{
	this->clear();

	ListNode *tmp = nd.head;

	while (tmp != nullptr)
	{
		this->push_back(*tmp);
		tmp = tmp->get_next();
	}
}

void DoublyLinkedList::merge(DoublyLinkedList &nd)
{
	assign(nd, 0, nd.size() - 1);
	sort();
}

ListNode *DoublyLinkedList::delete_node(ListNode *nd)
{
	if (nd == head)
	{
		ListNode *tmp;
		tmp = nd->get_next();
		tmp->set_prev(nullptr);

		delete nd;


		return tmp;
	}
	ListNode *prev, *next;
	prev = nd->get_prev();
	next = nd->get_next();

	if (prev != NULL) prev->set_next(nd->get_next());

	if (next != NULL) next->set_prev(nd->get_prev());

	delete nd;

	return prev;
}

void DoublyLinkedList::erase(char *dat)
{
	if (head == NULL) return;

	ListNode *tmp = head;

	while (tmp != nullptr)
	{
		bool flag = true;

		if (strcmp(tmp->get_data(), dat) == 0)
		{
			if (tmp == head)
			{
				head = delete_node(head);
				tmp = head;
				flag = false;
			}
			else
			{
				tmp = delete_node(tmp);
				flag = true;
			}
		}
		if (flag) tmp = tmp->get_next();
	}
}

void DoublyLinkedList::unique()
{
	if (head == NULL) return;

	sort();

	ListNode *tmp = head;

	while (tmp != nullptr)
	{
		ListNode *tmp2 = tmp->get_next();
		while (tmp2 != nullptr && (strcmp(tmp->get_data(), tmp2->get_data()) == 0))
		{
			ListNode* next = tmp2->get_next();
			tmp2 = delete_node(tmp2);
			tmp2 = next;
		}
		tmp = tmp->get_next();
	}
}

void DoublyLinkedList::assign(DoublyLinkedList &dl, int first, int last)
{
	ListNode* start = dl.search_by_index(first);
	ListNode* end = dl.search_by_index(last + 1);
	ListNode* next;

	while (start != end)
	{
		next = start->get_next();
		push_back(*start);
		start = delete_node(start);
		start = next;
	}
}

void DoublyLinkedList::splice(int where, const DoublyLinkedList &dl)
{
	ListNode *tmp = search_by_index(where);
	ListNode *tmp_start = dl.head;
	ListNode *tmp_dl = dl.head;

	while (tmp_dl->get_next() != nullptr)
	{
		tmp_dl = tmp_dl->get_next();
	}

	tmp_dl->set_next(tmp->get_next());
	tmp->set_prev(tmp_dl);
	tmp->set_next(tmp_start);
	tmp_start->set_prev(tmp);
}

void DoublyLinkedList::splice(int where, const DoublyLinkedList &dl, int first, int last)
{
	ListNode* tmp = search_by_index(where);
	ListNode* tmp_start = dl.search_by_index(first);
	ListNode* tmp_dl = dl.search_by_index(last);

	tmp_dl->set_next(tmp->get_next());
	tmp->set_prev(tmp_dl);
	tmp->set_next(tmp_start);
	tmp_start->set_prev(tmp);
}

void DoublyLinkedList::print()
{
	ListNode *tmp = head;
	do
	{
		std::cout << tmp->get_data() << " ";
		tmp = tmp->get_next();
	} while (tmp != NULL);
}

void DoublyLinkedList::print_bkw()
{
	ListNode *tmp = head;
	while (tmp->get_next() != NULL)
	{
		tmp = tmp->get_next();
	}

	do
	{
		std::cout << tmp->get_data() << " ";
		tmp = tmp->get_prev();
	} while (tmp != NULL);
}