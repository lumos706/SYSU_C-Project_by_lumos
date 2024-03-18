#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <ctype.h>
#include <algorithm>
using namespace std;
class Compare {
public:
	bool operator()(const pair<string, pair<int, string>>& a, const pair<string, pair<int, string>>& b) {
		if (a.second.first != b.second.first) {
			return a.second.first > b.second.first;
		}
		else return a.first < b.first;
	}
};
vector<string> keyword;
vector<string> targetword;
map<string, pair<int, string>> word_count;

int CountLines(const char* filename);
string Readline(const char* filename, int line);
void GetKeyWord(string tmp);
void Analyse(string tmp);
int KMP(string line, string target);

int CountLines(const char* filename) {
	ifstream ReadFile;
	int count = 0;
	string tmp;
	ReadFile.open(filename, ios::in);
	if (ReadFile.fail()) {
		return 0;
	}
	else {
		while (getline(ReadFile, tmp, '\n')) {
			count++;
		}
		ReadFile.close();
		return count;
	}
}

string Readline(const char* filename, int line) {
	fstream file;
	string tmp;
	file.open(filename, ios::in);
	int i = 0;
	while (getline(file, tmp) && i < line - 1) {
		i++;
	}
	file.close();
	return tmp;
}  

void GetKeyWord(string tmp) {
	istringstream ss(tmp);
	string word;
	while (ss >> word) {
		while (ispunct(word[word.size() - 1]) && word.size()>1) {
			word = word.substr(0, word.size() - 1);
		}
		while (ispunct(word[0]) && word.size() > 1) {
			word = word.substr(1, word.size() - 1);
		}
		if (ispunct(word[0])) continue;
		if (find(keyword.begin(), keyword.end(), word) == keyword.end()) keyword.push_back(word);
		else;
	}
	return;
}

void Analyse(string tmp,int line,int func) {
	/**/tmp.erase(remove_if(tmp.begin(), tmp.end(), static_cast<int(*)(int)>(&ispunct)), tmp.end());
	for (auto x : targetword) {
		string target = x;
		target.erase(remove_if(target.begin(), target.end(), static_cast<int(*)(int)>(&ispunct)), target.end());
		int ans = KMP(tmp, target);
		if (ans) {
			if (word_count.find(x) != word_count.end()) {
				word_count[x].first += ans;
				word_count[x].second += (to_string(line) + " ");
			}
			else {
				word_count[x].first = ans;
				word_count[x].second += (to_string(line) + " ");
			}
		}
		else {
			word_count[x].first += ans;
		}
		///*if (word_line.find(x) != word_line.end())*/ word_line[x].push_back(line);
	}
}

int KMP(string line, string target) {
	int ans = 0;
	int i = 0, j = 0;
	int lineLen = line.size(), targetLen = target.size();
	//if (find(keyword.begin(), keyword.end(), target) == keyword.end()) return 0;// ?
	while (i <= lineLen) {
		if (j == targetLen) {
			if (isalnum(line[i])) {
				j = 0;
				goto count;
			}
			else if (i - j - 1 >= 0) {
				if (isalnum(line[i - j - 1])) {
					j = 0;
					goto count;
				}
			}
			j = 0;
			ans++;
		}
		if (i == lineLen) break;
		count:
		if (line[i] == target[j]) {
			i++; j++;
		}
		else {
			i = i - j + 1;
			j = 0;
		}
	}
	return j == targetLen ? ans + 1 : ans;
}
