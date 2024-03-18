#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <windows.h>
#include "graph.h"
using namespace std;

int main() {
    system("color F0");
    cout << "字典： " << endl;
    for (int i = 0; i < 26; i++) {
        cout << "点" << i << ": " << name[i] << endl;
    }

    // 输入边的数量
    int numEdges;
    cout << "Enter the number of edges(边数): ";
    cin >> numEdges;

    // 输入边的信息，并统计点的个数
    set<int> uniqueVertices;  // 使用集合来统计唯一的顶点编号
    vector<Edge> edges;

    cout << "以这个形式输入边 (vertex1 vertex2 weight):" << endl;
    for (int i = 0; i < numEdges; ++i) {
        Edge edge;
        cin >> edge.vertex1 >> edge.vertex2 >> edge.weight;

        // 统计顶点编号
        uniqueVertices.insert(edge.vertex1);
        uniqueVertices.insert(edge.vertex2);

        edges.push_back(edge);
    }

    // 初始化 vector<VNode> vertices
    vector<VNode> vertices(uniqueVertices.size() + 1);  // 从 1 开始编号

    // 为每个顶点赋值
    int index = 1;
    for (int vertex : uniqueVertices) {
        vertices[index].data = vertex;
        ++index;
    }

    // 创建图并添加边
    Graph graph(vertices);

    for (const Edge& edge : edges) {
        graph.AddEdge(edge);
    }

    while (true) {
        // 打印菜单
        system("cls");
        graph.Print();
        // 输入用户选择
        int choice;
        
        cin >> choice;
        int n;
        switch (choice) {
        case 1:
            cout << "输入起点:";
            cin >> n;
            cout << "DFS from vertex " << name[n] << " :" << endl;
            graph.DFS(n);
            system("pause");
            system("cls");
            break;
        case 2:
            cout << "输入起点:";
            cin >> n;
            cout << "Non-recursive DFS from vertex " << name[n] << ": " << endl;
            graph.DFSNonRecursive(n);
            system("pause");
            system("cls");
            break;
        case 3:
            cout << "输入起点:";
            cin >> n;
            cout << "BFS starting from vertex " << name[n] << ": " << endl;
            graph.BFS1(n);
            cout << endl;
            graph.BFS2(n);
            system("pause");
            system("cls");
            break;
        case 4:
            cout << "输入起点:";
            cin >> n;
            cout << "DFS Tree starting from vertex " << name[n] << ": " << endl;
            graph.DFSTree(n);
            system("pause");
            system("cls");
            break;
        case 5:
            cout << "输入起点:";
            cin >> n;
            cout << "BFS Tree starting from vertex " << name[n] << ": " << endl;
            graph.BFSTree(n);
            system("pause");
            system("cls");
            break;
        case 6:
            cout << "Graph:" << endl << endl;
            graph.PrintGraph();
            system("pause");
            system("cls");
            break;
        case 0:
            cout << "Exiting program. Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please enter a valid option." << endl;
        }
    }

    return 0;
}
