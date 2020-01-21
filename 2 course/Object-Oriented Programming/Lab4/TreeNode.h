#pragma once

#include <string>
#include <iostream>
#include <vector>


using namespace std;

class CTreeNode
{
	public:
		CTreeNode *left = nullptr;
		CTreeNode *right = nullptr;
		CTreeNode(string);

		int id;
		int quantity;
		string author;
		string title;
		string year;

		void print();
		void printByTitle(string);
		void insert(CTreeNode*);
		void isAuthorPresent(string au, int& found, int& present);
		bool isTitlePresent(string);
		CTreeNode* find(int);
		void getAllChildren(vector<CTreeNode*>&);
		void removeById(int);
		void print_nodes();
};

