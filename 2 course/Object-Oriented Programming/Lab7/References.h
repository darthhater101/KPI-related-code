#pragma once
#include <ostream>

using namespace std;

class References {
public:

	References();
	References(const References&obj);
	References(char *_word, int *_pages, int __size);
	~References();

	char* getWord();
	void setWord(char *_word);
	int getSize();

	bool operator!=(const References &ref);
	References& operator= (const References &ref);

	void pr_arr();

	friend ostream& operator<<(ostream& stream, References &obj);
private:
	char *word;
	int *pages;//pages numbers
	int _size;//number of pages
};

