#include "TreeNode.h"
#include <sstream>

#define MAX(a,b) (a>b)?a:b

CTreeNode::CTreeNode(string data)
{
	stringstream ss(data);
	string tmp;
	getline(ss,tmp,';');
	if (tmp.length() == 0) return;
	id = stoi(tmp);
	getline(ss,author,';');
	getline(ss,title,';');
	getline(ss,year,';');
	getline(ss,tmp);
	quantity = stoi(tmp);

}

void CTreeNode::insert(CTreeNode* node)
{
	if(node->id < id)
	{
		if(left != nullptr) left->insert(node);
		else left = node;
	}
	else
	{
		if(right != nullptr) right->insert(node);
		else right = node;
	}
}

bool CTreeNode::isTitlePresent(string ttl)
{
	return(left != nullptr && left->isTitlePresent(ttl)) || 
		(right!= nullptr && right->isTitlePresent(ttl)) ||
	  (title == ttl && quantity > 0) ;
}


void CTreeNode::isAuthorPresent(string au, int& found, int& present) {
	if (author == au) 
	{
		found++;
		if (quantity > 0) 
		{
			present++;
		}
	}
	if (left != nullptr) 
	{
		left->isAuthorPresent(au, found, present);
	}
	if (right != nullptr) 
	{
		right->isAuthorPresent(au, found, present);
	}
}

void CTreeNode::print()
{
	cout << id << " "<< " " << author << " "<< title << " "<< year << " "<< "Quantity: " << quantity << endl;
}

void CTreeNode::print_nodes() 
{
	if (left != nullptr) left->print_nodes();
	print();
	if (right != nullptr) right->print_nodes();
}

void CTreeNode::printByTitle(string ttl)
{
	if(title == ttl)
	{
		print();
	}
	else
	{
		if(right != nullptr)
			right->printByTitle(ttl);
		if(left != nullptr)
			left->printByTitle(ttl);
	}
}

CTreeNode* CTreeNode::find(int n)
{
	if(id == n) return this;
	else
	{
		CTreeNode* l = left;
		CTreeNode* r = right;
		if(l != nullptr) l = l->find(n);
		if(r != nullptr) r = r->find(n);
		return MAX(l,r);
	}
}
void CTreeNode::removeById(int n)
{
	if(left != nullptr)
	{
		if(left->id == n)
		{
			left = nullptr;
			return;
		}
		else
		{
			left->removeById(n);
		}
	}
	if(right != nullptr)
	{
		if(right->id == n)
		{
			right = nullptr;
			return;
		}
		else
		{
			right->removeById(n);
		}
	}
}


void CTreeNode::getAllChildren(vector<CTreeNode*>& store)
{
	if(right != nullptr)
	{
		store.push_back(right);
		right->getAllChildren(store);
	}
	if(left != nullptr)
	{
		store.push_back(left);
		left->getAllChildren(store);
	}
}
