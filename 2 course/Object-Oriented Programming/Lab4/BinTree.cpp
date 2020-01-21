#include "BinTree.h"
#include <fstream>


CBinTree::CBinTree()
{
	ifstream in("./library.csv");
	string temp;
	while(getline(in,temp))
	{
		if(root == nullptr)
			root = new CTreeNode(temp);
		else
			root->insert(new CTreeNode(temp));
	}

}

void CBinTree::isTitlePresent(string title)
{
	if(root != nullptr && root->isTitlePresent(title))
	{
		cout << "Title " << title << " is present in library" << endl;
		root->printByTitle(title);
	}
	else
	{
		cout << "Title " << title << " is not present in library" << endl;
	}
}

void CBinTree::isAuthorPresent(string author) 
{
	int found = 0;
	int present = 0;
	if (root != nullptr) root->isAuthorPresent(author, found, present);

	if (found == present && found != 0)
		cout << "All books of " << author << " are present in library" << endl;
	else if(found == 0)
		cout << "Books of " << author << " are not present in library" << endl;
	else
		cout << "Some books of " << author << " are not present in library" << endl;
}

void CBinTree::add() 
{
	cout << "Enter data in csv format\n m_Bookid; m_Author; m_Title; m_Year; m_Quantity" << endl;
	string tmp;
	while (tmp.length() < 4) 
	{
		getline(cin, tmp);
	}
	if (root == nullptr)
		root = new CTreeNode(tmp);
	else
		root->insert(new CTreeNode(tmp));
	cout << "Book added" << endl;
}

void CBinTree::remove()
{
	int n;
	cout << "Enter book id" << endl;
	cin >> n;
	CTreeNode* rem = root->find(n);
	if(rem != nullptr)
	{
		vector<CTreeNode*> store;
		rem->getAllChildren(store);
		root->removeById(n);
		delete rem;
		for(int i = 0;i<store.size();i++)
		{
			store[i]->left = nullptr;
			store[i]->right = nullptr;
			root->insert(store[i]);
		}
	}
}
	
void CBinTree::printAll() 
{
	root->print_nodes();
}
	




