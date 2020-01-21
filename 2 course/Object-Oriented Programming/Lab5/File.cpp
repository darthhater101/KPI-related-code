#include "CFILE.h"
#include <cstdlib>
#include <iostream>

using namespace std;

void another_test()
{
	cout << "Testing methods and assignments" << endl;
	cout << "Overloaded assignments:" << endl;

	CFile file1;

	file1.SetDetails("Name.exe", 304);
	file1.SetKeywords("text1;text2;text3");

	cout << "File1(first object):" << endl;
	file1.Print();

	cout << "File2 = File1..." << endl;
	CFile file2; 
	file2 = file1;

	cout << "File2(second object):" << endl;
	file2.Print();

	file2.SetKeywords("text1;text2;text3;text4");
	cout << "file2 < file1: " << (file2 < file1) << endl;
}

void func_test()
{
	vector <CFile> vec;

	cout << "Input:" << endl;
	input(vec, "test.csv");
	ListAll(vec);
	cout << endl;

	cout << "Add keyword \"way\":" << endl;
	AddKeyword(vec, (char*)"way");
	ListAll(vec);
	cout << endl;

	cout << "Sort by keywords number:" << endl;
	SortByKeywordsNumber(vec);
	ListAll(vec);
	cout << endl;

	cout << "Delete keywords: \"rock\" , \"is\" , \"take\"" << endl;
	DelKeyword(vec, (char*)"rock");
	DelKeyword(vec, (char*)"is");
	DelKeyword(vec, (char*)"take");
	ListAll(vec);
	cout << endl;

	cout << "Sort by name:" << endl;
	SortBySize(vec);
	ListAll(vec);
	cout << endl;

	cout << "Delete keywords with len more than 4:" << endl;
	DelKeywordByLen(vec, 4);
	ListAll(vec);
	cout << endl;
}

int main()
{
	func_test();
	another_test();

	system("pause");
	return 0;
}