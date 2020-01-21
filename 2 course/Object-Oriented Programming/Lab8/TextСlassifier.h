#pragma once
#include <vector>
#include <string>
#include <map>

using namespace std;

#define MAX_SCORE 150
#define LOWER_NGRAM_LEN	2
#define UPPER_NGRAM_LEN	5
//Довжина профілів категорій й текстів, що розпізнаються повинна бути однаковою і обмеженою. Наприклад,
#define CATEGORY_LEN 1000

/* N-grams frequencies profile */
typedef map<string, unsigned long> frequency_map;
typedef vector<pair<string, unsigned long>> vec_pair;



class TextСlassifier {
public:

	/* Name of category defaults to 'Unknown.' */
	TextСlassifier() {};

	/*Param classification - name of the category (e.g., "English").    */
	TextСlassifier(const string category);

	/* returns the map N-grams and their frequencies.     */
	frequency_map freqs() { return _freqs; }

	/* returns the name of the classifier.*/
	string category() { return _category; }

	/*Param classification - name of the category.*/
	void setCategory(string& cat) { _category = cat; }

	void create_ngrams(string word);

	/*learns the frequencies of N-grams in a corpus.*/
	void learn(istream& in);

	/*dumps the frequencies of N-grams in a corpus.
	File structure is as follows:
	* lines which start with c - comments
	* line which starts with s - classification
	* lines with N-grams start with n  and contain
	* N-gram and its quantity separated with space or tab*/
	void dumpProfile(ostream& out);

	/*learns the frequencies of N-grams from a file created by.
	dumpProfile() function */
	void learnfromDump(istream& in);

	/*returns distance measure between 2 TextСlassifiers*/
	long int score(const TextСlassifier &);

	void sort_map();

	void vec_to_map();

	vec_pair _vec_pair;

	string get_cat() { return _category; }

	frequency_map get_fr() { return _freqs; }

private:
	/*! internal frequency map */
	frequency_map _freqs;
	map<string, int> ngrams_index;
	/*! internal name of classifer */
	string _category;

};
