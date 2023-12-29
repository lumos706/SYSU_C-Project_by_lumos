#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <time.h>
#include <iomanip>
using namespace std;
//mt19937 rng;

//int randomidx = 0;
vector<string> names = { "Zhang San", "Li Si", "Wang Wu", "Sun ZeKun", "Tao YuZhuo", "Zhou Zheng",
        "Zhou Jiu", "Wu Shi", "Zheng ShiYi", "Feng ShiEr", "Chen ShiSan", "Chu ShiSi", "Wei ShiWu",
        "Jiang ShiLiu", "Shen ShiQi", "Han ShiBa", "Yang ShiJiu", "Zhu SiShi", "Qin ErShi", "You Er ShiYi",
        "Cai ShenLin", "Chen ZhenHuang", "Zhu ShiSi", "Xu ShiWu", "Lu ShiLiu", "Wei Er ShiQi", "Tang Er ShiBa",
        "Chen ZhengXi", "Liu SanShi", "Su Zhuo" };

class HashTable {
public:
    HashTable(int size) : size(size), table(size, ""), attempts(size, 0)/*, randomlist(30, 0)*/ {
        /*Inirandom(randomlist);*/
    }

    //void Inirandom(vector<int>& ramdomlist) {
    //    srand((unsigned)time(NULL));
    //    int t = rand() % 30;
    //    for (int i = 0; i < 30; i++) {
    //        randomlist[i] = (i + t) % 30;
    //    }
    //}

    int hashFunction(const string& name) {
        // 简单的除留余数法哈希函数
        int total = 0;
        for (char c : name) {
            total += static_cast<int>(c);
        }
        return (total+size*100) % size;
    }
    //int pseudoRandomFunction(int key, int attempt) {
    //    // 使用伪随机数生成器
    //    if (randomidx == 29) randomidx = 0;
    //    return (key + randomlist[randomidx++]) % size;

    //}
    int pseudoRandomFunction(int key, int attempt) {
        // 伪随机探测再散列法
        return (key + attempt ) % size;
    }
    //int pseudoRandomFunction(int key, int attempt) {
    //    // 使用伪随机数生成器
    //    uniform_int_distribution<int> distribution(1, size - 1);
    //    return (key + distribution(rng)) % size;
    //}

    void insert(const string& name) {
        int attempt = 0;
        int index = hashFunction(name);

        while (!table[index].empty()) {
            // 冲突处理
            attempt++;
            index = pseudoRandomFunction(hashFunction(name), attempt);
        }

        table[index] = name;
        attempts[index] = attempt + 1;
    }

    int search(const string& name, int& numAttempts) {
        int attempt = 0;
        int index = hashFunction(name);

        while (!table[index].empty()) {
            if (table[index] == name) {
                numAttempts = attempt + 1;  // 找到了
                return static_cast<int>(index);
            }
            else {
                // 冲突处理
                attempt++;
                index = pseudoRandomFunction(hashFunction(name), attempt);
            }
        }

        numAttempts = attempt + 1;  // 未找到
        return -1;
    }

    void displayTable() {
        cout << endl << "                   哈希表内容：" << endl;
        int totalAttempts = 0;

        cout << left << setw(15) << "索引" << setw(15) << "姓名" << setw(15) << "键值" << "查找次数" << endl;

        for (int i = 0; i < size; ++i) {
            int total = 0;
            for (char c : table[i]) {
                total += static_cast<int>(c);
            }

            cout << left << setw(15) << i << setw(15) << table[i] << setw(15) << total << attempts[i] << endl;
            totalAttempts += attempts[i];
        }

        double averageAttempts = static_cast<double>(totalAttempts) / 30;
        cout << "平均查找次数：" << averageAttempts << endl << endl;
    }

    void rebuild(int newSize) {
        size = newSize;
        table.clear();
        table.resize(size);
        attempts.clear();
        attempts.resize(size);
        
        for (const string& name : names) {
            insert(name);
        }
    }

private:
    int size;
    vector<string> table;
    vector<int> attempts;
   /* vector<int> randomlist;*/
};
