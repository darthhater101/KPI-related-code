#pragma once
#pragma warning(disable : 4996)
#include <vector>

using namespace std;

class CFile {
public:
	//default constructor
	CFile();
	//copy constructor
	CFile(const CFile &);
	//destructor
	~CFile();
	void SetDetails(const char *, int);
	void SetKeywords(const char*);
	//overloaded assignment
	CFile & operator=(const CFile &);
	bool operator<(const CFile &)const;
	int GetSize()const { return size; };
	void SetSize(int);
	void Print()const;

	int GetKeywords_nmb();
	char* GetKeywords();
	char* GetName();

private:
	char *name;//file name
	int size;//file length
	char *keywords;//set of keywords
	int keywords_nmb;//keywords number
};

void SortBySize(vector<CFile> &);
void SortByKeywordsNumber(vector<CFile> &);
void ListAll(const vector<CFile> &);
void AddKeyword(vector<CFile> &, char *);
void DelKeyword(vector<CFile> &, char *kwrd);
void DelKeywordByLen(vector<CFile> &, int len);

void input(vector<CFile>&, const char*);