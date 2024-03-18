#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
using namespace std;

typedef struct pnode {
	float coef = 0.00;		//ϵ��
	int expo = 0;		//ָ��
	struct pnode* next = NULL;		//ָ��
}pnode, * polynomial;
void gotoxy(int x = 0, int y = 0) {
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
int InitList(polynomial& L) {
	L = new pnode;	//Ϊ�����������Զ�����ռ�
	L->next = NULL;	//����ͷ��㣬��next����ΪNULL 
	return 0;
}//��ʼ��
void Push(polynomial& px, float coef, int expo) {
	polynomial q, pre, p3;
	q = px->next;
	pre = px;
	p3 = new pnode;
	p3->coef = coef;
	p3->expo = expo;
	while (q && q->expo > p3->expo) {
		pre = q;
		q = q->next;
	}
	if (q && q->expo == p3->expo) {
		q->coef += p3->coef;
		return;
	}
	p3->next = q;		
	pre->next = p3;
	return;
}//
void CreatePolyn(polynomial& p, int n) {
	float coe;
	int exp;
	cout << endl;
	cout << "|------------------------------����������ÿ��ϵ����ָ����--------------------------|" << endl << endl;
	for (int i = 1; i <= n; ++i) {
		cin >> coe;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(10000000, '\n');
			cout << endl << "|--------------------------------------�������----------------------------------|" << endl << endl;
			cin >> coe;
		}
		if (coe) {
			cin >>exp;
			while (cin.fail()) {
				cin.clear();
				cin.ignore(10000000, '\n');
				cout << endl << "|--------------------------------------�������----------------------------------|" << endl << endl;
				cin >> coe >> exp;
			}
		}
		else {
			if (n == 1) {
				rewind(stdin);
				continue;
			}
			cin >> exp;
			continue;
		}
		Push(p, coe, exp);
	}
	rewind(stdin);
}
void Printresult(polynomial& p) {
	pnode* q;	//��һ��ָ��ָ����Ҫ���������
	q = p->next;	//ָ��������Ԫ���
	if (!q) {
		cout << "0";
		return;
	}
	if (q->coef == 1) {
		if (q->expo == 1) cout << "x";
		else if (q->expo == 0) cout << 1;
		else cout << "x^" << q->expo;
	}
	else if (q->coef == -1) {
		if (q->expo == 1) cout << "-x";
		else if (q->expo == 0) cout << -1;
		else cout << "-x^" << q->expo;
	}
	else {
		if (q->expo == 1) cout << q->coef << "x";
		else if (q->expo == 0) cout << q->coef;
		else cout << q->coef << "x^" << q->expo;
	}
	q = q->next;	//��ָ��ָ����Ԫ������һ����㣬����ľ�ֻ��Ҫ��һ��ѭ�����ϵ����ָ������
	while (q) {
		if (q->coef == 1) {
			if (q->expo == 1) cout << "+x";
			else if (q->expo == 0) cout << "+1";
			else cout << "+x^" << q->expo;
		}
		else if (q->coef == -1) {
			if (q->expo == 1) cout << "-x";
			else if (q->expo == 0) cout << "-1";
			else cout << "-x^" << q->expo;
		}
		else {
			if (q->coef > 0) {
				if (q->expo == 1) cout << "+" << q->coef << "x";
				else if (q->expo == 0) cout << "+" << q->coef;
				else cout << "+" << q->coef << "x^" << q->expo;
			}
			else {
				if (q->expo == 1) cout << q->coef << "x";
				else if (q->expo == 0) cout << q->coef;
				else cout << q->coef << "x^" << q->expo;
			}
		}
		q = q->next;	//ָ�����ƶ�����һ�����
	}
}
void Cls(polynomial& pa, polynomial& pb, polynomial& pc, polynomial& pd) {
	cout << "|----------------------------------------------------------------------------------|" << endl;
	cout << "|-------------------------------һԪϡ�����ʽ������-------------------------------|" << endl;
	cout << "|-------------------------------------------------------22336216 ����׿------------|" << endl;
	cout << endl << "|--------------------------------------״̬��--------------------------------------|";
	cout << endl << "|--pa: ";
	Printresult(pa);
	cout << endl << "|--pb: ";
	Printresult(pb);
	cout << endl << "|--pc: ";
	Printresult(pc);
	cout << endl << "|--pd: ";
	Printresult(pd);
	cout << endl << "|----------------------------------------------------------------------------------|" << endl << endl;
}
void AddPolyn(polynomial& pa, polynomial& pb, polynomial& pc, polynomial& pd) {
	delete pc;
	InitList(pc);
	float sum = 0.00;	//���ڱ���ָ����ͬʱ��ϵ����Ӻ�Ľ��
	polynomial p1, p2;
	p1 = pa->next;
	p2 = pb->next;
	while (p1 && p2) {
		if (p1->expo == p2->expo) {
			sum = p1->coef + p2->coef;
			if (sum != 0) {
				Push(pc, sum, p1->expo);
				p1 = p1->next;
				p2 = p2->next;
			}
			else {
				p1 = p1->next;
				p2 = p2->next;
			}
		}
		else if (p1->expo < p2->expo) {
			Push(pc, p2->coef, p2->expo);
			p2 = p2->next;
		}
		else {
			Push(pc, p1->coef, p1->expo);
			p1 = p1->next;
		}
	}
	if (p1) {
		while (p1) {
			Push(pc, p1->coef, p1->expo);
			p1 = p1->next;
		}
	}
	else if (p2) {
		while (p2) {
			Push(pc, p2->coef, p2->expo);
			p2 = p2->next;
		}
	}
	cout << endl;
	system("cls");
	Cls(pa, pb, pc, pd);
}
void SubPolyn(polynomial& pa, polynomial& pb, polynomial& pc, polynomial& pd) {
	delete pc;
	InitList(pc);
	float sum = 0.00;	//���ڱ���ָ����ͬʱ��ϵ����Ӻ�Ľ��
	polynomial p1, p2;	//p1ָ��pa,p2ָ��pb,p3ָ��ǰ��㣬��ֵΪpa��r���ڱ���������Ҫ�ͷŵ�p2���
	p1 = pa->next;
	p2 = pb->next;
	while (p1 && p2) {
		if (p1->expo == p2->expo) {
			sum = p1->coef - p2->coef;
			if (sum != 0) {
				Push(pc, sum, p1->expo);
				p1 = p1->next;
				p2 = p2->next;
			}
			else {
				p1 = p1->next;
				p2 = p2->next;
			}
		}
		else if (p1->expo < p2->expo) {
			Push(pc, 0 - p2->coef, p2->expo);
			p2 = p2->next;
		}
		else {
			Push(pc, p1->coef, p1->expo);
			p1 = p1->next;
		}
	}
	if (p1) {
		while (p1) {
			Push(pc, p1->coef, p1->expo);
			p1 = p1->next;
		}
	}
	else if (p2) {
		while (p2) {
			Push(pc, 0 - p2->coef, p2->expo);
			p2 = p2->next;
		}
	}
	cout << endl;
	system("cls");
	Cls(pa, pb, pc, pd);
}
void MultiplyPolyn(polynomial pa, polynomial pb, polynomial& pc, polynomial& pd){
	delete pc;
	InitList(pc);
	polynomial p1, p2;
	p1 = pa->next;
	p2 = pb->next;
	if (p1 == nullptr || p2 == nullptr) {
		cout << endl;
		system("cls");
		Cls(pa, pb, pc, pd);	//��pc��ӡ����
		return;
	}
	while(p1){
		while(p2){
			int sum = 0;	//����ָ����ӵĽ��
			sum = p1->expo + p2->expo;		//����ָ����ӵĽ��
			Push(pc, p1->coef * p2->coef, sum);
			p2 = p2->next;
		}
		p2 = pb->next;
		p1 = p1->next;
	}
	cout << endl;
	system("cls");
	Cls(pa, pb, pc, pd);
}
double Value(polynomial& p, double x) {
	double sum = 0.00;
	double tmp = 0.00;
	polynomial p1;
	p1 = p->next;
	while (p1) {
		sum += double(double(p1->coef) * pow(x, p1->expo));
		p1 = p1->next;
	}
	return sum;
}
void DerivativeA(polynomial& pa, polynomial& pb, polynomial& pc,polynomial& pd) {
	delete pd;
	InitList(pd);
	polynomial p1 = pa->next;
	while (p1) {
		if (p1->expo != 0) {
			Push(pd, (p1->coef * p1->expo), (p1->expo) - 1);
			p1 = p1->next;
		}
		else p1 = p1->next;
	}
	cout << endl;
	system("cls");
	Cls(pa, pb, pc, pd);
}
void DerivativeB(polynomial& pa, polynomial& pb, polynomial& pc, polynomial& pd) {
	delete pd;
	InitList(pd);
	polynomial p2 = pb->next;
	while (p2) {
		if (p2->expo != 0) {
			Push(pd, (p2->coef * p2->expo), (p2->expo) - 1);
			p2 = p2->next;
		}
		else p2 = p2->next;
	}
	cout << endl;
	system("cls");
	Cls(pa, pb, pc, pd);
}
