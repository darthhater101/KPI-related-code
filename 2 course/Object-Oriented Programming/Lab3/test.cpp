#include "ClassList.h"

using namespace std;

int main()
{
	DoublyLinkedList *lst = new DoublyLinkedList();

	char* txt[5] = { (char*)"dat1" ,(char*)"dat2" ,(char*)"dat3" ,(char*)"dat4" ,(char*)"dat5" };

	ListNode nd;

	cout << "Lst is empty:" << lst->empty() << endl << endl;

	for (int i = 0; i < 5; i++)
	{
		nd.set_data(txt[i]);
		lst->push_back(nd);
	}
	cout << "Lst:";
	lst->print();
	cout << endl << endl;

	cout << "Lst is empty:" << lst->empty() << endl << endl;

	cout << "Print_bkw lst:";
	lst->print_bkw();
	cout << endl << endl;

	cout << "Lst size:" << lst->size() << endl << endl;

	cout << "Push_front:" << endl;

	nd.set_data(txt[3]);

	lst->push_front(nd);
	cout << "Lst:";
	lst->print();
	cout << endl << endl;;
	

	cout << "Pop_front & pop_back:" << endl;
	lst->pop_back();
	lst->pop_front();
	cout << "Lst:";
	lst->print();
	cout << endl << endl;

	cout << "Sort:" << endl;
	nd.set_data(txt[1]);
	lst->push_back(nd);
	nd.set_data(txt[3]);
	lst->push_front(nd);
	cout << "Lst:";
	lst->print();
	lst->sort();
	cout << endl;
	cout << "After sort \nLst:";
	lst->print();
	cout << endl << endl;

	nd.set_data(txt[3]);
	cout << "Insert_after(\"dat2\", nd.data = dat4):" << lst->insert_after((char*)"dat2", nd) << endl;
	cout << "Lst:";
	lst->print();
	cout << endl << endl;

	cout << "Insert_ord:" << endl;

	nd.set_data(txt[0]);
	lst->insert_ord(nd);
	cout << "Lst:";
	lst->print();
	cout << endl << endl;

	DoublyLinkedList *lst2 = new DoublyLinkedList();

	*lst2 = *lst;

	cout << "lst2 = lst" << endl;
	cout << "Lst: ";
	lst->print();
	cout << endl;
	cout << "Lst2: ";
	lst2->print();
	cout << endl;

	cout << "Change lst:";
	nd.set_data(txt[1]);
	lst->push_back(nd);
	lst->print();
	cout << endl;
	cout << "Lst2 doesn't change:";
	lst2->print();
	cout << endl << endl;

	cout << "Merge lst lst2:" << endl;
	cout << "Lst:";
	lst->print();
	cout << endl;
	cout << "Lst2:";
	lst2->print();
	cout << endl;
	lst->merge(*lst2);
	cout << "Final lst:";
	lst->print();
	cout << endl << endl;

	cout << "Erase dat3:" << endl;
	cout << "Lst:";
	lst->print();
	cout << endl;
	lst->erase((char*)"dat3");
	cout << "After erase \nLst:";
	lst->print();
	cout << endl << endl;

	nd.set_data(txt[2]);
	lst->push_back(nd);
	nd.set_data(txt[3]);
	lst->push_back(nd);
	nd.set_data(txt[4]);
	lst->push_back(nd);

	cout << "Before Unique:" << endl;
	cout << "Lst:";
	lst->print();
	cout << endl;
	cout << "After Unique:" << endl;
	cout << "Lst:";
	lst->unique();
	lst->print();
	cout << endl << endl;

	DoublyLinkedList *lst3 = new DoublyLinkedList();

	for (int i = 0; i < 5; i++)
	{
		nd.set_data(txt[i]);
		lst3->push_back(nd);
	}

	cout << "Assign(lst3, first = 1, last = 3):" << endl;
	cout << "Lst:";
	lst->print();
	cout << endl;
	cout << "Lst3:";
	lst3->print();
	cout << endl;
	lst->assign(*lst3, 1, 3);
	cout << "After assign \nLst: ";
	lst->print();
	cout << endl << endl;

	DoublyLinkedList *lst4 = new DoublyLinkedList();

	for (int i = 0; i < 4; i++)
	{
		nd.set_data(txt[i]);
		lst4->push_back(nd);
	}

	cout << "Splice(where = 2, lst4) with lst4:" << endl;
	cout << "Lst:";
	lst->print();
	cout << endl;
	cout << "Lst4: ";
	lst4->print();
	cout << endl;
	lst->splice(2, *lst4);
	cout << "After splice \nLst: ";
	lst->print();
	cout << endl << endl;

	DoublyLinkedList *lst5 = new DoublyLinkedList();

	for (int i = 0; i < 4; i++)
	{
		nd.set_data(txt[i]);
		lst5->push_back(nd);
	}

	cout << "Splice(where = 2, lst5, first = 0, last = 2) with lst5:" << endl;
	cout << "Lst:";
	lst->print();
	cout << endl;
	cout << "Lst5: ";
	lst5->print();
	cout << endl;
	lst->splice(2, *lst5, 0, 2);
	cout << "After splice \nLst: ";
	lst->print();
	cout << endl;

	return 0;
}