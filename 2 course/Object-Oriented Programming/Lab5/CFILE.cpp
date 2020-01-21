#include "CFILE.h"
#include <iostream>
#include <cstdio>
#include <fstream>
#include <cstring>

using namespace std;

CFile::CFile()
{
	cout << "Calling constructor" << endl;
	name = nullptr;
	keywords = nullptr;
}

CFile::CFile(const CFile &object)
{
	cout << "Calling copy constructor" << endl;
	name = new char[strlen(object.name) + 1];
	strcpy(name, object.name);
	size = object.size;
	keywords = new char[strlen(object.keywords) + 1];
	strcpy(keywords, object.keywords);
	keywords_nmb = object.keywords_nmb;
}

CFile::~CFile()
{
	cout << "Calling destructor" << endl;
	if (name != nullptr)
		delete[] name;
	if (keywords != nullptr)
		delete[] keywords;
}

void CFile::SetDetails(const char *_name, int _size)
{
	if (_name == nullptr)
	{
		cout << "Name parametr is empty" << endl;
		return;
	}

	if (name != nullptr)
		delete[] name;

	name = new char[strlen(_name) + 1];
	strcpy(name, _name);
	size = _size;
}


void CFile::SetSize(int _size)
{
	size = _size;
}

void CFile::Print()const
{
	cout << "Name:" << name << endl << "Size = " << size << endl << "Keywords: " << keywords << endl << "Keywords_nmb: " << keywords_nmb << endl;
}

CFile& CFile::operator=(const CFile &object)
{
	if (this == &object)
		return *this;
	
	if (name != nullptr)
		delete[] name;
	if (keywords != nullptr)
		delete[] keywords;

	name = new char[strlen(object.name) + 1];
	strcpy(name, object.name);
	size = object.size;
	keywords = new char[strlen(object.keywords) + 1];
	strcpy(keywords, object.keywords);
	keywords_nmb = object.keywords_nmb;
	return *this;
}

bool CFile::operator<(const CFile &object)const
{
	if (this->keywords_nmb < object.keywords_nmb)
		return true;
	else return false;
}

void CFile::SetKeywords(const char* kw)
{
	if (kw == nullptr)
	{
		cout << "Keywords parametr is empty" << endl;
		return;
	}

	if (keywords != nullptr)
		delete[] keywords;

	keywords = new char[strlen(kw) + 1];
	strcpy(keywords, kw);

	int words = 0;
	for (int i = 0; i < strlen(kw); i++)
	{
		if (kw[i] == ';') words++;
	}
	keywords_nmb = words + 1;
}

int CFile::GetKeywords_nmb()
{
	return keywords_nmb;
}

char* CFile::GetKeywords()
{
	char* kwr = new char[strlen(keywords) + 1];
	strcpy(kwr, keywords);
	return kwr;
}

char* CFile::GetName()
{
	return name;
}

void input(vector <CFile> &vec, const char* file)
{
	ifstream f(file);
	if (!(f.is_open()))
		return;
	while (!f.eof())
	{
		char* name = new char[256];
		char* size = new char[256];
		char* keywords = new char[256];

		f.getline(name, 256, ';');
		f.getline(size, 256, ';');
		f.getline(keywords, 256);

		CFile buff;
		buff.SetDetails(name, atoi(size));
		buff.SetKeywords(keywords);
		vec.push_back(buff);

		delete[] name;
		delete[] size;
		delete[] keywords;
	}
	f.close();
}

void SortBySize(vector<CFile> &vec)//Відсортувати елементи контейнера в лексикографічному порядку імен файлів.
{
	for (int i = 0; i < vec.size(); i++)
	{
		for (int j = vec.size() - 2; j >= i; j--)
		{
			if (strcmp(vec[j].GetName(), vec[j + 1].GetName()) > 0)
			{
				CFile temp = vec[j];
				vec[j] = vec[j + 1];
				vec[j + 1] = temp;
			}
		}
	}
}

void SortByKeywordsNumber(vector<CFile> &vec)//Відсортувати елементи контейнера в порядку неубування числа ключових слів.
{
	for (int i = 0; i < vec.size(); i++)
	{
		for (int j = vec.size() - 2; j >= i; j--)
		{
			if (vec[j].GetKeywords_nmb() > vec[j + 1].GetKeywords_nmb())
			{
				CFile temp = vec[j];
				vec[j] = vec[j + 1];
				vec[j + 1] = temp;
			}
		}
	}
}

void ListAll(const vector<CFile> &vec) //Вивести на консоль уміст контейнера
{
	for (int i = 0; i < vec.size(); i++)
	{
		cout << "Object" << i + 1 << ":" << endl;
		vec[i].Print();
		cout << endl;
	}
}

void AddKeyword(vector <CFile> &vec, char *word)//Додати у файли ключове слово
{
	for (int i = 0; i < vec.size(); i++)
	{
		char* tmp = vec[i].GetKeywords();
		char* buff = new char[strlen(tmp) + strlen(word)+2];
		buff[0] = 0;
		strcat(buff, vec[i].GetKeywords());
		strcat(buff, ";");
		strcat(buff, word);

		vec[i].SetKeywords(buff);

		delete[] tmp;
		delete[] buff;
	}
}

void DelKeyword(vector <CFile> &vec, char *kwrd)//Вилучити з файлів ключове слово kwrd.
{
	for (int i = 0; i < vec.size(); i++)
	{
		char* str = vec[i].GetKeywords();
		char *t = 0, *t2 = 0;
		for (; t = strstr(str, kwrd); )
		{
			t2 = t + strlen(kwrd);
			while (*t++ = *t2++);
		}

		for (int i = 0; i < strlen(str); i++)
		{
			if (((str[i] == ';') && (str[i + 1] == ';')))
				for (int j = i; j < strlen(str); j++)
					str[j] = str[j + 1];
		}

		if (str[0] == ';')
		{
			for (int i = 0; i < strlen(str); i++)
			{
				str[i] = str[i + 1];
			}
		}

		if (str[strlen(str) - 1] == ';')
			str[strlen(str) - 1] = str[strlen(str)];

		vec[i].SetKeywords(str);
	}
}

void DelKeywordByLen(vector <CFile> &vec, int len)//Вилучити з файлів ключові слова, довжини більше len.
{
	for (int i = 0; i < vec.size(); i++)
	{
		char* tmp = vec[i].GetKeywords();
		char* buff = new char[strlen(tmp) + 1];
		buff[0] = 0;

		char* word = strtok(tmp, ";");
		while (word != NULL)
		{
			if (strlen(word) <= len)
			{
				strcat(buff, word);
				strcat(buff, ";");
			}
			word = strtok(NULL, ";");
		}

		if (buff[strlen(buff) - 1] == ';')
			buff[strlen(buff) - 1] = 0;
		vec[i].SetKeywords(buff);

		delete[] tmp;
		delete[] buff;
	}
}