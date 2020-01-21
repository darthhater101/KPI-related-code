#include "Text—lassifier.h"
#include <fstream>
#include <iostream>
#include <iomanip>

int main()
{
	Text—lassifier eng("english");
	Text—lassifier fra("french");
	Text—lassifier spa("spain");
	Text—lassifier ita("italian");

	ifstream engt("english.txt");
	ifstream frat("french.txt");
	ifstream spat("spain.txt");
	ifstream itat("italian.txt");

	cout << "Learning examples..." << endl;

	eng.learn(engt);
	fra.learn(frat);
	spa.learn(spat);
	ita.learn(itat);

	engt.close();
	frat.close();
	spat.close();
	itat.close();

	vector<Text—lassifier> examples;

	examples.push_back(eng);
	examples.push_back(fra);
	examples.push_back(spa);
	examples.push_back(ita);

	for (auto &x : examples)
	{
		x.sort_map();
	}

	cout << "Recognizing...(the minimum value is a match)" << endl;
	cout << "Recognizing first text (must be english)" << endl;

	ifstream unk_text("test_eng.txt");
	Text—lassifier test;
	test.learn(unk_text);
	unk_text.close();
	test.sort_map();


	for (auto x : examples)
	{
		unsigned long score = x.score(test);
		cout << x.get_cat() << " score: " << score << endl;
	}

	cout << endl;

	cout << "Recognizing second text (must be italian)" << endl;

	ifstream unk_text2("test_ita.txt");
	Text—lassifier test2;
	test2.learn(unk_text2);
	unk_text2.close();
	test2.sort_map();

	for (auto x : examples)
	{
		unsigned long score = x.score(test2);
		cout << x.get_cat() << " score: " << score << endl;
	}

	cout << endl;

	cout << "Recognizing third text (must be french)" << endl;

	ifstream unk_text3("test_fre.txt");
	Text—lassifier test3;
	test3.learn(unk_text3);
	unk_text3.close();
	test3.sort_map();

	for (auto x : examples)
	{
		unsigned long score = x.score(test3);
		cout << x.get_cat() << " score: " << score << endl;
	}

	cout << endl;

	cout << "Recognizing fourth text (must be spanish)" << endl;

	ifstream unk_text4("test_spa.txt");
	Text—lassifier test4;
	test4.learn(unk_text4);
	unk_text4.close();
	test4.sort_map();

	for (auto x : examples)
	{
		unsigned long score = x.score(test4);
		cout << x.get_cat() << " score: " << score << endl;
	}

	cout << endl << endl;

	cout << "Testing dumpProfile" << endl;

	cout << "Load to file ngrams from english text example" << endl;
	ofstream out("ngrams.txt");
	eng.sort_map();
	eng.dumpProfile(out);
	out.close();

	cout << "Load from file ngrams from english text example" << endl;
	ifstream in("ngrams.txt");
	Text—lassifier dump;
	dump.learnfromDump(in);
	dump.vec_to_map();

	cout << "Counting score between them (it must be 0)" << endl;
	int score = dump.score(eng);
	cout << "Score: " << score << endl;

	in.close();

	system("pause");
	return 0;
}