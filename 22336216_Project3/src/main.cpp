#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <ctype.h>
#include <algorithm>
#include <iomanip>
#include <Windows.h>
#include "text.h"
using namespace std;
int main() {
	system("color F3");
	SetConsoleTitle(LPCWSTR(L"TXTcounter"));


	//输入地址打开文本

	while (1) {
		targetword.clear();
		keyword.clear();
		word_count.clear();
		cout << "|----------------------------------------------------------------------------------|" << endl;
		cout << "|-----------------------------------文本检测程序-----------------------------------|" << endl;
		cout << "|-------------------------------------------------------22336216 陶宇卓------------|" << endl;
		string filename;
		cout << "|-------------------------------请输入地址：(exit退出)-----------------------------|" << endl << endl;
		cin >> filename;
		if (filename == "exit") return 0;
		const char* file = filename.c_str();
		ifstream ReadFile;
		ReadFile.open(file);
			while (ReadFile.fail()) {
				cout << "|-------------------------------------打开失败！-----------------------------------|" << endl << endl;
				cin.ignore(10000, '\n');
				cin >> filename;
				const char* file = filename.c_str();
				ReadFile.open(file);

			}
			file = filename.c_str();
			//计算行数
			int countlines = CountLines(file);
			cout << "|-------------------------------------读取文本：-----------------------------------|" << endl << endl;
			for (int i = 1; i <= countlines; i++) {
				string oneline = Readline(file, i);
				cout << setw(2) << left << i << ":" << oneline << endl;
				GetKeyWord(oneline);
			}

			//输入目标单词
			sort(keyword.begin(), keyword.end());
			cout << endl;
			cout << "|---------------------------1：查找所有单词 2：查找指定单词------------------------|" << endl << endl;
			int choose = 0;
			cin >> choose;
			while (choose < 1 || choose > 2 || cin.fail()) {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << endl << "|-------------------------------------输入错误！-----------------------------------|" << endl << endl;
				cin >> choose;
			}
			if (choose == 1) {
				cout << endl;
				cout << "|-------------------------------------字符集：-------------------------------------|" << endl << endl;
				for (auto x : keyword) {
					cout << x << " ";
				}
				targetword.assign(keyword.begin(), keyword.end());
			}
			else if (choose == 2) {
				cout << endl;
				cout << "|-------------------------------输入单词（以exit结束）：---------------------------|" << endl << endl;
				string tar;
				while (1) {
					cin >> tar;
					if (tar == "exit") break;
					targetword.push_back(tar);
				}
				sort(targetword.begin(), targetword.end());
			}

			//分析。。。
			for (int i = 1; i <= countlines; i++) {
				string oneline = Readline(file, i);
				if (choose == 1) Analyse(oneline, i, 1);
				if (choose == 2) Analyse(oneline, i, 2);
			}
			vector<pair<string, pair<int, string>>> word_counttmp(word_count.begin(), word_count.end());
			sort(word_counttmp.begin(), word_counttmp.end(), Compare());
			//result
			cout << endl;
			cout << endl << "|-------------------------------------检测结果：-----------------------------------|" << endl << endl;
			for (auto x : word_counttmp) {
				cout << x.first << " 出现了" << x.second.first << "次 , 在第 " << x.second.second << "行" << endl;
				cout << "|-------------------------------------" << endl;
			}
			word_counttmp.clear();
			system("pause");
			system("cls");
		}
		
		return 0;
	}