#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <map>
#include <cstdlib>
using namespace std;

enum {
	NPREF = 2,
	NHASH = 4093,
	MAXGEN = 100000
};

char NONWORD[] = "\n";

using prefix = deque<string>;
map<prefix, vector<string>> statetab;

void add(prefix &pref, const string &s)
{
	if (pref.size() == NPREF) {
		statetab[pref].push_back(s);
		pref.pop_front();
	}

	pref.push_back(s);
}

void build(prefix &pref, istream &in)
{
	string buf;
	while (in >> buf) {
		add(pref, buf);
	}
}

void generate(int nwords)
{
	prefix pref;

	for (int i = 0; i < NPREF; ++i) {
		add(pref, NONWORD);
	}

	for (int i = 0; i < nwords; ++i) {
		vector<string> &suf = statetab[pref];
		const string &w = suf[rand() % suf.size()];
		if (w == NONWORD) {
			break;
		}
		cout << w << "\n";
		pref.pop_front();
		pref.push_back(w);
	}
}

int main(int argc, char *argv[])
{
	int nwords = MAXGEN;
	prefix pref;

	for (int i = 0; i < NPREF; ++i) {
		add(pref, NONWORD);
	}

	build(pref, cin);
	add(pref, NONWORD);
	generate(nwords);

	return 0;
}
