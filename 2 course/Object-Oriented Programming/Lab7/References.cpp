#pragma warning(disable: 4996)
#include "References.h"
#include "MyList.h"

References::References()
{
	word = nullptr;
	pages = nullptr;
	_size = 0;
}

References::~References()
{
	if (word != nullptr)
		delete[] word;
	if (pages != nullptr)
		delete[] pages;

	word = nullptr;
	pages = nullptr;
}

References::References(char *_word, int *_pages, int __size)
{
	word = new char[strlen(_word) + 1];
	strcpy(word, _word);

	pages = new int[__size];

	for (int i = 0; i < __size; i++)
		pages[i] = _pages[i];

	_size = __size;
}

References::References(const References& obj)
{
	word = new char[strlen(obj.word) + 1];
	strcpy(word, obj.word);

	pages = new int[obj._size];

	for (int i = 0; i < obj._size; i++)
		pages[i] = obj.pages[i];

	_size = obj._size;
}

char* References::getWord()
{
	char* wd = new char[strlen(word) + 1];
	strcpy(wd, word);
	return wd;
}

void References::setWord(char *_word)
{
	if (word != nullptr)
		delete[] word;

	word = new char[strlen(_word) + 1];
	strcpy(word, _word);
}

int References::getSize()
{
	return _size;
}

References& References::operator= (const References &obj)
{
	if (this == &obj)
		return *this;

	delete[] word;
	delete[] pages;

	word = new char[strlen(obj.word) + 1];
	strcpy(word, obj.word);

	pages = new int[obj._size];

	for (int i = 0; i < obj._size; i++)
		pages[i] = obj.pages[i];

	_size = obj._size;

	return *this;
}

bool References::operator!=(const References &ref)
{
	return (strcmp(word, ref.word) != 0 && pages != ref.pages && _size != ref._size);
}

void References::pr_arr()
{
	for (int i = 0; i < _size; i++)
		cout << pages[i] << " ";
}

ostream& operator<<(ostream& stream, References &obj)
{
	stream << "Word: " << obj.word << endl;
	stream << "Pages: "; obj.pr_arr();
	stream << "\nSize: " <<  obj._size << endl;
	return stream;
}