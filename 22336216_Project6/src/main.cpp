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
    cout << "�ֵ䣺 " << endl;
    for (int i = 0; i < 26; i++) {
        cout << "��" << i << ": " << name[i] << endl;
    }

    // ����ߵ�����
    int numEdges;
    cout << "Enter the number of edges(����): ";
    cin >> numEdges;

    // ����ߵ���Ϣ����ͳ�Ƶ�ĸ���
    set<int> uniqueVertices;  // ʹ�ü�����ͳ��Ψһ�Ķ�����
    vector<Edge> edges;

    cout << "�������ʽ����� (vertex1 vertex2 weight):" << endl;
    for (int i = 0; i < numEdges; ++i) {
        Edge edge;
        cin >> edge.vertex1 >> edge.vertex2 >> edge.weight;

        // ͳ�ƶ�����
        uniqueVertices.insert(edge.vertex1);
        uniqueVertices.insert(edge.vertex2);

        edges.push_back(edge);
    }

    // ��ʼ�� vector<VNode> vertices
    vector<VNode> vertices(uniqueVertices.size() + 1);  // �� 1 ��ʼ���

    // Ϊÿ�����㸳ֵ
    int index = 1;
    for (int vertex : uniqueVertices) {
        vertices[index].data = vertex;
        ++index;
    }

    // ����ͼ����ӱ�
    Graph graph(vertices);

    for (const Edge& edge : edges) {
        graph.AddEdge(edge);
    }

    while (true) {
        // ��ӡ�˵�
        system("cls");
        graph.Print();
        // �����û�ѡ��
        int choice;
        
        cin >> choice;
        int n;
        switch (choice) {
        case 1:
            cout << "�������:";
            cin >> n;
            cout << "DFS from vertex " << name[n] << " :" << endl;
            graph.DFS(n);
            system("pause");
            system("cls");
            break;
        case 2:
            cout << "�������:";
            cin >> n;
            cout << "Non-recursive DFS from vertex " << name[n] << ": " << endl;
            graph.DFSNonRecursive(n);
            system("pause");
            system("cls");
            break;
        case 3:
            cout << "�������:";
            cin >> n;
            cout << "BFS starting from vertex " << name[n] << ": " << endl;
            graph.BFS1(n);
            cout << endl;
            graph.BFS2(n);
            system("pause");
            system("cls");
            break;
        case 4:
            cout << "�������:";
            cin >> n;
            cout << "DFS Tree starting from vertex " << name[n] << ": " << endl;
            graph.DFSTree(n);
            system("pause");
            system("cls");
            break;
        case 5:
            cout << "�������:";
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
