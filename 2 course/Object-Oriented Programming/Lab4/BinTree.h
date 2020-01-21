#pragma once

#include "TreeNode.h"



class CBinTree
{
	public:
		CTreeNode* root = nullptr;
		
		CBinTree();
		void remove();
		void add();
		void isAuthorPresent(string);
		void isTitlePresent(string);
		void printAll();
};
