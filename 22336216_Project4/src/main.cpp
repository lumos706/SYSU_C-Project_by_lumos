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
	cout << "|----------------------------------表达式树生成器----------------------------------|" << endl;
	cout << "|-------------------------------------------------------22336216 陶宇卓------------|" << endl;
	cout << endl << "|--------------------------------------状态栏--------------------------------------|";
	cout << endl << "|----------------------------------------------------------------------------------|" << endl << endl;
	while (1) {
		cout << "|--------------------------------------功能栏--------------------------------------|" << endl;
		cout << "|                            |                        |                            |" << endl;
		cout << "|        1:输入表达式        |      2:对变量赋值      |           3:求值           |" << endl;
		cout << "|                            |                        |                            |" << endl;
		cout << "|----------------------------------------------------------------------------------|" << endl;
		cout << "|                            |                        |                            |" << endl;
		cout << "|           4:合并           |         5:求导         |          6:可视化          |" << endl;
		cout << "|                            |                        |                            |" << endl;
		cout << "|----------------------------------------------------------------------------------|" << endl;
		cout << "|                            |                        |                            |" << endl;
		cout << "|                            |         7:退出         |                            |" << endl;
		cout << "|                            |                        |                            |" << endl;
		cout << "|----------------------------------------------------------------------------------|" << endl << endl;

		int func;
		cin >> func;
		rewind(stdin);

		if (func == 1) {
			string prefix;
			cout << endl;
			cout << "|-------------------------------请输入前缀表达式：---------------------------------| " << endl;
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
			cout << "|----------------------------请输入表达式编号（0开始）-----------------------------| " << endl;
			cout << endl;
			cin >> number;
			copyroots[number] = Copy(roots[number]);
			cout << endl;
			cout << "|-------------------------------请输入变量名以及值---------------------------------| " << endl;
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
			cout << "|----------------------------请输入表达式编号（0开始）-----------------------------| " << endl;
			cout << endl;
			cin >> number;
			if (copyroots.count(number) == 0) {
				cout << "结果为： " << Value(roots[number]) << endl;
			}
			else cout << "结果为： " << Value(copyroots[number]) << endl;
			system("pause");
			system("cls");
			Cls();
		}


		else if (func == 4) {
			int funct;
			cout << endl;
			cout << "|-----------------------------合并常数(1)or表达式(2)？-----------------------------| " << endl;
			cout << endl;
			cin >> funct;
			if (funct == 1) {
				int number;
				cout << endl;
				cout << "|----------------------------请输入表达式编号（0开始）-----------------------------| " << endl;
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
				cout << "|----------------------------请输入表达式编号（0开始）-----------------------------| " << endl;
				cout << endl;
				cin >> number1 >> number2;
				cout << endl;
				cout << "|---------------------------------请输入操作符-------------------------------------| " << endl;
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
			cout << "|----------------------------请输入表达式编号（0开始）-----------------------------| " << endl;
			cout << endl;
			cin >> number;
			cout << endl;
			cout << "|---------------------------------请输入变量名-------------------------------------| " << endl;
			cout << endl;
			string v;
			cin >> v;
			TreeNode* derivativeTree = Derivative(roots[number], v);
			cout << endl;
			cout << "|---------------------------------求偏导结果为-------------------------------------| " << endl;
			cout << endl;
			cout << WriteExpr(derivativeTree) << endl;
			system("pause");
			system("cls");
			Cls();
		}

		else if (func == 6) {
			int number;
			cout << endl;
			cout << "|----------------------------请输入表达式编号（0开始）-----------------------------| " << endl;
			cout << endl;
			cin >> number;
			cout << endl;
			cout << "|----------------------------表达式树应该是(？)这样的------------------------------| " << endl;
			cout << endl;
			printTree(copyroots[number]);
			system("pause");
			system("cls");
			Cls();

		}
		else if(func == 7) {
			cout << endl;
			cout << "|--------------------------------谢谢使用！再见！----------------------------------|" << endl;
			return 0;
		}
	
	}

	return 0;
}


//试试拓展功能