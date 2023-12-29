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

    // 插入测试数据
    for (const string& name : names) {
        hashTable.insert(name);
    }

    int choice;
    while (true) {
        cout << "请选择功能：" << endl;
        cout << "1. 查找数据\n2. 输出哈希表\n3. 重构哈希表\n4. 退出程序\n" << endl;
        cin >> choice;

        switch (choice) {
        case 1: {
            string name;
            cout << "请输入要查找的姓名：";
            cin.ignore();
            getline(cin, name);

            int numAttempts;
            int index = hashTable.search(name, numAttempts);

            if (index != -1) {
                cout << "姓名：" << name << "，在哈希表中的索引：" << index << endl;
                cout << "查找次数：" << numAttempts << endl;
            }
            else {
                cout << "姓名：" << name << " 未找到" << endl;
            }

            break;
        }
        case 2:
            hashTable.displayTable();
            break;
        case 3: {
            int newSize;
            cout << "请输入新的哈希表大小：";
            cin >> newSize;
            hashTable.rebuild(newSize);
            cout << "哈希表已重构" << endl;
            break;
        }
        case 4:
            cout << "程序退出\n";
            return 0;
        default:
            cout << "无效选择，请重新输入\n";
        }
    }
}