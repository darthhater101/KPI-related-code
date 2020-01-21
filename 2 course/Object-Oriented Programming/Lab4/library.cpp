#include "BinTree.h"
#include <cstdlib>

void menu()
{
	CBinTree t;

	cout << "Library\n"
		"1. Add book\n"
		"2. Delete book by id\n"
		"3. View statement about the availability of all the books of the author by his name\n"
		"4. View statement about the availability of the book by title\n" << endl;

	while (1)
	{
		t.printAll();
		cout << endl;

		char c = 0;
		cout << "Enter the menu item you want to call(1-4), enter something else to exit:";
		cin >> c;
		switch (c) 
		{
			case '1': 
			{
				t.add();
				break;
			}
			case '2': 
			{
				t.remove();
				break;
			}
			case '3':
			{
				cout << "Enter author name:";
				string author;
				cin >> author;
				t.isAuthorPresent(author);
				break;
			}
			case '4': 
			{
				cout << "Enter title:";
				string title;
				cin >> title;
				t.isTitlePresent(title);
				break;
			}
			default: return;
		}
	}
}


int main()
{
	menu();
	return 0;
}
