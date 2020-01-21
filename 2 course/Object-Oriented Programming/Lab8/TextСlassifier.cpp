#include "Text—lassifier.h"
#include <string>
#include <iostream>
#include <algorithm>

Text—lassifier::Text—lassifier(const string category)
{
	_category = category;
}

void Text—lassifier::create_ngrams(string word)
{
	for (int i = LOWER_NGRAM_LEN; i <= UPPER_NGRAM_LEN; i++)
	{
		word = "_" + word + "_";
		for (int j = 0; j <= word.length() - i; j++) {
			string str = word.substr(j, i);

			if (_freqs.find(str) != _freqs.end())
				_freqs[str]++;
			else
				_freqs.insert(pair<string, unsigned long>(str, 1));
		}
	}
}

void Text—lassifier::learn(istream & in)
{
	string output;
	while (!in.eof()) 
	{
		in >> output;
		create_ngrams(output);
	}
}


void Text—lassifier::dumpProfile(ostream & out)
{
	out.clear();

	out << "s " << _category << endl;

	for (auto x : _vec_pair)
		out << "n " << x.first << " " << x.second << endl;
}

void Text—lassifier::learnfromDump(istream & in)
{
	string input;
	while (!in.eof())
	{
		in >> input;
		if (input == "s")
		{
			in >> input;
			_category = input;
		}
		if (input == "n")
		{
			in >> input;
			string buff = input;
			in >> input;
			unsigned long tmp = stoi(input);
			_vec_pair.push_back(pair<string, unsigned long>(buff, tmp));
		}
	}
}

long int Text—lassifier::score(const Text—lassifier &text)
{
	int max_score = 0;

	for (auto x : ngrams_index)
	{
		int index;
		auto it = text.ngrams_index.find(x.first);
		if (it != text.ngrams_index.end())
			max_score += abs(x.second - it->second);
		else
			max_score += min(ngrams_index.size(), text.ngrams_index.size());
	}

	return max_score;
}

void Text—lassifier::sort_map()
{
	auto it = _freqs.begin();
	while (it != _freqs.end())
	{
		_vec_pair.push_back(*it);
		it++;
	}

	sort(_vec_pair.begin(), _vec_pair.end(), [](auto x, auto y) { return x.second > y.second; });

	auto it2 = _vec_pair.begin();
	int i = 0;
	while (it2 != _vec_pair.end())
	{
		ngrams_index.insert(pair<string, unsigned long>(it2->first, i));
		i++;
		it2++;
	}
}

void Text—lassifier::vec_to_map()
{
	auto it = _vec_pair.begin();
	int i = 0;
	while (it != _vec_pair.end())
	{
		ngrams_index.insert(pair<string, unsigned long>(it->first, i));
		i++;
		it++;
	}
}
