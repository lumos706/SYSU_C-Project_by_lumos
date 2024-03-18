#include <iostream>
#include <string>
#include <ctype.h>
#include <math.h>
#include <Windows.h>
#include <vector>
#include <stack>
#include <unordered_map>
#include <queue>
#include "ExpressionTree.h"
using namespace std;
int cnt = 0;

int main() {
	cout << "|----------------------------------------------------------------------------------|" << endl;
	cout << "|----------------------------------���ʽ��������----------------------------------|" << endl;
	cout << "|-------------------------------------------------------22336216 ����׿------------|" << endl;
	cout << endl << "|--------------------------------------״̬��--------------------------------------|";
	cout << endl << "|----------------------------------------------------------------------------------|" << endl << endl;
	while (1) {
		cout << "|--------------------------------------������--------------------------------------|" << endl;
		cout << "|                            |                        |                            |" << endl;
		cout << "|        1:������ʽ        |      2:�Ա�����ֵ      |           3:��ֵ           |" << endl;
		cout << "|                            |                        |                            |" << endl;
		cout << "|----------------------------------------------------------------------------------|" << endl;
		cout << "|                            |                        |                            |" << endl;
		cout << "|           4:�ϲ�           |         5:��         |          6:���ӻ�          |" << endl;
		cout << "|                            |                        |                            |" << endl;
		cout << "|----------------------------------------------------------------------------------|" << endl;
		cout << "|                            |                        |                            |" << endl;
		cout << "|                            |         7:�˳�         |                            |" << endl;
		cout << "|                            |                        |                            |" << endl;
		cout << "|----------------------------------------------------------------------------------|" << endl << endl;

		int func;
		cin >> func;
		rewind(stdin);

		if (func == 1) {
			string prefix;
			cout << endl;
			cout << "|-------------------------------������ǰ׺���ʽ��---------------------------------| " << endl;
			cout << endl;
			getline(cin, prefix);
			TreeNode* root = ReadExpr(prefix);
			if (!root) goto cls;
			roots[cnt] = root;
			copyroots[cnt] = Copy(root);
			cnt++;
			cls:
			system("cls");
			Cls();
			}


		else if (func == 2) {
			int number; double val = 0; string v = "";
			cout << endl;
			cout << "|----------------------------��������ʽ��ţ�0��ʼ��-----------------------------| " << endl;
			cout << endl;
			cin >> number;
			copyroots[number] = Copy(roots[number]);
			cout << endl;
			cout << "|-------------------------------������������Լ�ֵ---------------------------------| " << endl;
			cout << endl;
			while (1) {
				cin >> v;
				if (v == "exit") break;
				cin >> val;
				Assign(copyroots[number], v, val);
			}
			//copyroots[number] = Copy(roots[number].first);
			//Assign(copyroots[number], v, val);
			system("cls");
			Cls();
			}


		else if (func == 3) {
			int number;
			cout << endl;
			cout << "|----------------------------��������ʽ��ţ�0��ʼ��-----------------------------| " << endl;
			cout << endl;
			cin >> number;
			if (copyroots.count(number) == 0) {
				cout << "���Ϊ�� " << Value(roots[number]) << endl;
			}
			else cout << "���Ϊ�� " << Value(copyroots[number]) << endl;
			system("pause");
			system("cls");
			Cls();
		}


		else if (func == 4) {
			int funct;
			cout << endl;
			cout << "|-----------------------------�ϲ�����(1)or���ʽ(2)��-----------------------------| " << endl;
			cout << endl;
			cin >> funct;
			if (funct == 1) {
				int number;
				cout << endl;
				cout << "|----------------------------��������ʽ��ţ�0��ʼ��-----------------------------| " << endl;
				cout << endl;
				cin >> number;
				Merge(roots[number]);
				copyroots[number] = Copy(roots[number]);
				system("cls");
				Cls();
			}
			else if (funct == 2) {
				int number1, number2;
				cout << endl;
				cout << "|----------------------------��������ʽ��ţ�0��ʼ��-----------------------------| " << endl;
				cout << endl;
				cin >> number1 >> number2;
				cout << endl;
				cout << "|---------------------------------�����������-------------------------------------| " << endl;
				cout << endl;
				string p;
				cin >> p;
				roots[cnt] = (Compound(p, roots[number1], roots[number2]));
				copyroots[cnt] = Copy(roots[cnt]);
				cnt++;
				system("cls");
				Cls();
			}
		}


		else if (func == 5) {
			int number;
			cout << endl;
			cout << "|----------------------------��������ʽ��ţ�0��ʼ��-----------------------------| " << endl;
			cout << endl;
			cin >> number;
			cout << endl;
			cout << "|---------------------------------�����������-------------------------------------| " << endl;
			cout << endl;
			string v;
			cin >> v;
			TreeNode* derivativeTree = Derivative(roots[number], v);
			cout << endl;
			cout << "|---------------------------------��ƫ�����Ϊ-------------------------------------| " << endl;
			cout << endl;
			cout << WriteExpr(derivativeTree) << endl;
			system("pause");
			system("cls");
			Cls();
		}

		else if (func == 6) {
			int number;
			cout << endl;
			cout << "|----------------------------��������ʽ��ţ�0��ʼ��-----------------------------| " << endl;
			cout << endl;
			cin >> number;
			cout << endl;
			cout << "|----------------------------���ʽ��Ӧ����(��)������------------------------------| " << endl;
			cout << endl;
			printTree(copyroots[number]);
			system("pause");
			system("cls");
			Cls();

		}
		else if(func == 7) {
			cout << endl;
			cout << "|--------------------------------ллʹ�ã��ټ���----------------------------------|" << endl;
			return 0;
		}
	
	}

	return 0;
}


//������չ����