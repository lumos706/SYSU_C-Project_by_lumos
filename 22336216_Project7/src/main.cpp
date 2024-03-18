#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include "Hash.h"

using namespace std;

int main() {
    system("color F0");
    int initialSize = 40;

    HashTable hashTable(initialSize);

    // �����������
    for (const string& name : names) {
        hashTable.insert(name);
    }

    int choice;
    while (true) {
        cout << "��ѡ���ܣ�" << endl;
        cout << "1. ��������\n2. �����ϣ��\n3. �ع���ϣ��\n4. �˳�����\n" << endl;
        cin >> choice;

        switch (choice) {
        case 1: {
            string name;
            cout << "������Ҫ���ҵ�������";
            cin.ignore();
            getline(cin, name);

            int numAttempts;
            int index = hashTable.search(name, numAttempts);

            if (index != -1) {
                cout << "������" << name << "���ڹ�ϣ���е�������" << index << endl;
                cout << "���Ҵ�����" << numAttempts << endl;
            }
            else {
                cout << "������" << name << " δ�ҵ�" << endl;
            }

            break;
        }
        case 2:
            hashTable.displayTable();
            break;
        case 3: {
            int newSize;
            cout << "�������µĹ�ϣ���С��";
            cin >> newSize;
            hashTable.rebuild(newSize);
            cout << "��ϣ�����ع�" << endl;
            break;
        }
        case 4:
            cout << "�����˳�\n";
            return 0;
        default:
            cout << "��Чѡ������������\n";
        }
    }
}