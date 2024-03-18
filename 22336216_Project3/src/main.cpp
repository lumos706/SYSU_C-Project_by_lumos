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


	//�����ַ���ı�

	while (1) {
		targetword.clear();
		keyword.clear();
		word_count.clear();
		cout << "|----------------------------------------------------------------------------------|" << endl;
		cout << "|-----------------------------------�ı�������-----------------------------------|" << endl;
		cout << "|-------------------------------------------------------22336216 ����׿------------|" << endl;
		string filename;
		cout << "|-------------------------------�������ַ��(exit�˳�)-----------------------------|" << endl << endl;
		cin >> filename;
		if (filename == "exit") return 0;
		const char* file = filename.c_str();
		ifstream ReadFile;
		ReadFile.open(file);
			while (ReadFile.fail()) {
				cout << "|-------------------------------------��ʧ�ܣ�-----------------------------------|" << endl << endl;
				cin.ignore(10000, '\n');
				cin >> filename;
				const char* file = filename.c_str();
				ReadFile.open(file);

			}
			file = filename.c_str();
			//��������
			int countlines = CountLines(file);
			cout << "|-------------------------------------��ȡ�ı���-----------------------------------|" << endl << endl;
			for (int i = 1; i <= countlines; i++) {
				string oneline = Readline(file, i);
				cout << setw(2) << left << i << ":" << oneline << endl;
				GetKeyWord(oneline);
			}

			//����Ŀ�굥��
			sort(keyword.begin(), keyword.end());
			cout << endl;
			cout << "|---------------------------1���������е��� 2������ָ������------------------------|" << endl << endl;
			int choose = 0;
			cin >> choose;
			while (choose < 1 || choose > 2 || cin.fail()) {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << endl << "|-------------------------------------�������-----------------------------------|" << endl << endl;
				cin >> choose;
			}
			if (choose == 1) {
				cout << endl;
				cout << "|-------------------------------------�ַ�����-------------------------------------|" << endl << endl;
				for (auto x : keyword) {
					cout << x << " ";
				}
				targetword.assign(keyword.begin(), keyword.end());
			}
			else if (choose == 2) {
				cout << endl;
				cout << "|-------------------------------���뵥�ʣ���exit��������---------------------------|" << endl << endl;
				string tar;
				while (1) {
					cin >> tar;
					if (tar == "exit") break;
					targetword.push_back(tar);
				}
				sort(targetword.begin(), targetword.end());
			}

			//����������
			for (int i = 1; i <= countlines; i++) {
				string oneline = Readline(file, i);
				if (choose == 1) Analyse(oneline, i, 1);
				if (choose == 2) Analyse(oneline, i, 2);
			}
			vector<pair<string, pair<int, string>>> word_counttmp(word_count.begin(), word_count.end());
			sort(word_counttmp.begin(), word_counttmp.end(), Compare());
			//result
			cout << endl;
			cout << endl << "|-------------------------------------�������-----------------------------------|" << endl << endl;
			for (auto x : word_counttmp) {
				cout << x.first << " ������" << x.second.first << "�� , �ڵ� " << x.second.second << "��" << endl;
				cout << "|-------------------------------------" << endl;
			}
			word_counttmp.clear();
			system("pause");
			system("cls");
		}
		
		return 0;
	}