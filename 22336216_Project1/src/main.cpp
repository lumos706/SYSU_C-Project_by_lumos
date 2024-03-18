#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <ctype.h>
#include <windows.h>
#include "func.h"

using namespace std;

int main(){
	polynomial pa; polynomial pb; polynomial pc; polynomial pd;
	InitList(pa); InitList(pb); InitList(pc); InitList(pd);
	system("color F3");
	SetConsoleTitle(LPCWSTR(L"Calculator"));
	Cls(pa, pb, pc, pd);
	string f;
	while (1) {
		cout << "|--------------------------------------������--------------------------------------|" << endl;
		cout << "|                            |                        |                            |" << endl;
		cout << "|          1:����pa          |        2:����pb        |           3:�ӷ�           |" << endl;
		cout << "|                            |                        |                            |" << endl;
		cout << "|----------------------------------------------------------------------------------|" << endl;
		cout << "|                            |                        |                            |" << endl;
		cout << "|           4:����           |         5:�˷�         |         6:��pa��         |" << endl;
		cout << "|                            |                        |                            |" << endl;
		cout << "|----------------------------------------------------------------------------------|" << endl;
		cout << "|                            |                        |                            |" << endl;
		cout << "|         7:��pb��         |      8:����x����ֵ     |           9:�˳�           |" << endl;
		cout << "|                            |                        |                            |" << endl;
		cout << "|----------------------------------------------------------------------------------|" << endl << endl;
		cin >> f;
		rewind(stdin);
		if (f == "1") {
			delete pa; 
			InitList(pa); 
			int n;
			cout << endl << "|----------------------------------------------------------------------------------|" << endl;
			cout << "|                                  ������pa��������                                |" << endl;
			cout << "|----------------------------------------------------------------------------------|" << endl << endl;
			cin >> n;
			while (n == 0||cin.fail()) {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << endl << "|-------------------------------------�������-----------------------------------|" << endl << endl;
				cin >> n;
			}
			if(!cin.fail()) {
				rewind(stdin);
			}
			CreatePolyn(pa, n);
			system("cls");
			Cls(pa, pb, pc, pd);
		}

		else if (f == "2") {
			delete pb;
			InitList(pb);
			int m;
			cout << endl << "|----------------------------------------------------------------------------------|" << endl;
			cout << "|                                  ������pb��������                                |" << endl;
			cout << "|----------------------------------------------------------------------------------|" << endl << endl;
			cin >> m;
			while (m == 0 || cin.fail()) {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << endl << "|-------------------------------------�������-----------------------------------|" << endl << endl;
				cin >> m;
			}
			if (!cin.fail()) {
				rewind(stdin);
			}			
			CreatePolyn(pb, m);
			system("cls");
			Cls(pa, pb, pc, pd);
		}
		else if (f == "3"){
			AddPolyn(pa, pb, pc, pd);
		}
		else if (f == "4"){
			SubPolyn(pa, pb, pc, pd);
		}
		else if (f == "5"){
			MultiplyPolyn(pa, pb, pc, pd);
		}
		else if (f == "6") {
			DerivativeA(pa, pb, pc, pd);
		}
		else if (f == "7") {
			DerivativeB(pa, pb, pc, pd);
		}
		else if (f == "8") {
			double x;
			char p;
			cout << endl << "|----------------------------���������ʽ(a,b)�Լ�xֵ------------------------------|" << endl << endl;
			cin >> p >> x;
			while (cin.fail()||(p!='a'&& p!='b')) {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << endl << "|--------------------------------------�������----------------------------------|" << endl << endl;
				cin >> p >> x;
			}
			if (p == 'a') {
				cout << endl << "|-------------------------------------������Ϊ-----------------------------------|" << endl << endl << "pa(" << x << ")=" << Value(pa, x) << endl << endl;
				cout << "|-------------------------------------���س�����-----------------------------------|" << endl;
			}
			else if (p == 'b') {
				cout << endl << "|-------------------------------------������Ϊ-----------------------------------|" << endl << endl << "pb(" << x << ")=" << Value(pb, x) << endl << endl;
				cout << "|-------------------------------------���س�����-----------------------------------|" << endl;
			}
			rewind(stdin);
			system("pause>nul");
			system("cls");
			Cls(pa, pb, pc, pd);
		}
		else if (f == "9") {
			cout << endl;
			cout << "|----------------------------------ллʹ�ã��ټ���--------------------------------|" ;
			break;
		}
		else {
			cout << "|----------------------------------������Ϸ�����----------------------------------|" << endl << endl;
			continue;
		}
	}
	double x, y, a;
	for (y = 1.5; y > -1.5; y -= 0.1) {
		for (x = -1.5; x < 1.5; x += 0.05) {
			a = x * x + y * y - 1;
			cout << (a * a * a - x * x * y * y * y <= 0.0 ? "*" : " ");
		}
		system("color Fc");
		cout << endl;
	}
	return 0;
}
