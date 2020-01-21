#pragma warning(disable: 4996)
#include "Proc_lst.h"
#include <fstream>

void main_proc(List <References> &ref, List <References> &del_ref)
{
	cout << "From csv to list" << endl;
	load_csv("test.csv", ref);
	ref.Print();
	cout << endl;

	cout << "Deleting element word == \"Farm\" and \"Knight\"" << endl;
	delete_elem(ref, del_ref, (char*)"Farm");
	delete_elem(ref, del_ref, (char*)"Knight");
	cout << "List with existing elements" << endl;
	ref.Print();
	cout << endl;
	cout << "List with removed elements" << endl;
	del_ref.Print();
	cout << endl;

	cout << "Restoring element word == \"Farm\"" << endl;
	restore_elem(ref, del_ref, (char*)"Farm");
	cout << "List with existing elements" << endl;
	ref.Print();
	cout << endl;
	del_ref.Print();
	cout << endl;

	cout << "Deleting elements with size < 4" << endl;
	delete_less(ref, del_ref, 4);
	cout << "List with existing elements" << endl;
	ref.Print();
	cout << endl;
	cout << "List with removed elements" << endl;
	del_ref.Print();
	cout << endl;

	cout << "Changing element word == \"Horn\" to word == \"City\"" << endl;
	cout << "List with existing elements" << endl;
	change_word(ref, "Horn", "City");
	ref.Print();
	cout << endl;
}

void load_csv(string path, List <References> &ref)
{
	bool flag = false;
	ifstream file(path);

	if (!file.is_open())
	{
		cout << "File doesn`t open" << endl;
		return;
	}

	while (!file.eof())
	{
		char* _word = new char[256];
		char* _size = new char[256];
		char* pages = new char[256];

		file.getline(_word, 256, ';');
		file.getline(_size, 256, ';');
		file.getline(pages, 256);

		int *_pg = new int[atoi(_size)];

		char *tmp;
		int i = 0;
		tmp = strtok(pages,";");

		while (i < atoi(_size))
		{
			if (atoi(tmp) > 300)
			{
				flag = true;
			}
			_pg[i] = atoi(tmp);
			i++;
			tmp = strtok(NULL, ";");
		}


		if (!flag)
		{
			References buff(_word, _pg, atoi(_size));
			ref.push_front(buff);
		}

		delete[] _word;
		delete[] _size;
		delete[] pages;
		delete[] tmp;
	}
	file.close();
}

void delete_elem(List <References> &ref, List <References> &del_ref, char *_word)
{
	List <References>::iterator it = ref.begin();
	List <References>::iterator next_it;

	while (it != ref.end())
	{
		if (strcmp((*it).data.getWord(), _word) == 0)
		{
			next_it = (*it).next;
			ref.splice(it, del_ref);
			it = next_it;
		}
		else
			it++;
	}
}

void restore_elem(List <References> &ref, List <References> &del_ref, char *_word)
{
	List <References>::iterator it = del_ref.begin();
	List <References>::iterator next_it;

	while (it != del_ref.end())
	{
  		if (strcmp((*it).data.getWord(), _word) == 0)
		{
			next_it = (*it).next;
			del_ref.splice(it, ref);
			it = next_it;
		}
		else
			it++;
	}
}

void delete_less(List <References> &ref, List <References> &del_ref, int less)
{
	List <References>::iterator it = ref.begin();
	List <References>::iterator next_it;

	while (it != ref.end())
	{
		if ((*it).data.getSize() < less)
		{
			next_it = (*it).next;
			ref.splice(it, del_ref);
			it = next_it;
			
		}
		else
			it++;
	}
}

void change_word(List <References> &ref, const char *_word, const char *_new)
{
	for (List <References>::iterator it = ref.begin(); it != ref.end(); it++)
	{
		if (strcmp((*it).data.getWord(), _word) == 0)
			(*it).data.setWord((char*)_new);
	}
}