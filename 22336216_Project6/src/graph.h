#pragma once
#pragma warning(disable:26451)
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
using namespace std;

string name[26] = { "��",
    "��³ľ��","����","����","���ͺ���","����",
    "����","֣��","���","����","����",
    "����","����","������","�ɶ�","�人",
    "�Ϻ�","����","����","����","�ϲ�",
    "����","����","����","����","����"
};

// �ṹ���ʾ��
struct Edge {
    int vertex1;  // �ߵ����
    int vertex2;  // �ߵ��յ�
    int weight;   // �ߵ�Ȩ��
};

// �ڽӶ��ر�Ľ��
struct ArcNode {
    int adjvex;              // �ڽӽ��ı��
    int weight;              // �ߵ�Ȩ��
    ArcNode* nextarc;        // ָ����һ���ڽӽ��
    ArcNode* opposite;       // ָ���뵱ǰ���෴�ı�
};

// ͼ�Ķ���
struct VNode {
    int data;                // ������
    ArcNode* firstarc;       // ָ���һ���ڽӽ��
};

// ͼ
class Graph {
private:
    vector<VNode> vertices;  // �洢ͼ�Ķ���
    stack<int> dfs_stack;     // ������ȱ�������ջ
    queue<int> bfs_queue;     // ������ȱ�����������
    queue<pair<int, int>> bfstree_queue;
    // ������ȱ����ݹ麯��
    void DFSRecursive1(int v, vector<bool>& visited);
    void DFSRecursive2(int v, vector<bool>& visited);

public:
    Graph(const vector<VNode>& initialVertices);

    void Print();
    // ��������
    void AddEdge(const Edge& edge);

    // ������ȱ���
    void DFS(int start);

    // �ǵݹ�������ȱ���
    void DFSNonRecursive(int start);

    // ������ȱ���
    void BFS1(int start);

    void BFS2(int start);

    void DFSRecursiveTreeIndent(int v, vector<bool>& visited, int depth);

    // �����������������
    void DFSTree(int start);

    // �����������������
    void BFSTree(int start);

    // ��ӡͼ���ڽӶ��ر�
    void PrintGraph();
};

Graph::Graph(const vector<VNode>& initialVertices) : vertices(initialVertices) {
    // ����������ִ��������ʼ�������������Ҫ�Ļ�
}

void Graph::Print() {
    cout << "�ֵ䣺 " << endl;
    for (int i = 0; i < 26; i++) {
        cout <<"��" << i << ": " << name[i] << endl;
    }

    cout << "\nѡ����:" << endl;
    cout << "1. ����������� (DFS)" << endl;
    cout << "2. �ǵݹ������������ DFS" << endl;
    cout << "3. ����������� (BFS)" << endl;
    cout << "4. �������������" << endl;
    cout << "5. �������������" << endl;
    cout << "6. ��ӡͼ" << endl;
    cout << "0. Exit" << endl;

    cout << "���빦��: ";

}
void Graph::AddEdge(const Edge& edge) {
    ArcNode* arc1 = new ArcNode{ edge.vertex2, edge.weight, nullptr, nullptr };
    ArcNode* arc2 = new ArcNode{ edge.vertex1, edge.weight, nullptr, nullptr };

    // ��ӱߵ�v1���ڽӶ��ر�
    arc1->nextarc = vertices[edge.vertex1].firstarc;
    vertices[edge.vertex1].firstarc = arc1;

    // ��ӱߵ�v2���ڽӶ��ر�
    arc2->nextarc = vertices[edge.vertex2].firstarc;
    vertices[edge.vertex2].firstarc = arc2;

    // ���ñߵ��෴��
    arc1->opposite = arc2;
    arc2->opposite = arc1;
}

void Graph::DFSRecursive1(int v, vector<bool>& visited) {
    // ��ǵ�ǰ���Ϊ�ѷ���
    visited[v] = true;
    cout << name[v] << " ";

    // �����ڽӽ��
    for (ArcNode* arc = vertices[v].firstarc; arc != nullptr; arc = arc->nextarc) {
        int adjvex = arc->adjvex;
        // ����ڽӽ��δ�����ʣ���ݹ����
        if (!visited[adjvex]) {
            DFSRecursive1(adjvex, visited);
        }
    }
}

void Graph::DFSRecursive2(int v, vector<bool>& visited) {
    // ��ǵ�ǰ���Ϊ�ѷ���
    visited[v] = true;
    //cout << name[v] << " ";

    // �����ڽӽ��
    for (ArcNode* arc = vertices[v].firstarc; arc != nullptr; arc = arc->nextarc) {
        int adjvex = arc->adjvex;
        // ����ڽӽ��δ�����ʣ���ݹ����
        if (!visited[adjvex]) {
            cout << "( " << v << " , " << adjvex << " ) ";
            DFSRecursive2(adjvex, visited);
        }
    }
}

void Graph::DFS(int start) {
    // ��ʼ��visited����
    vector<bool> visited(vertices.size(), false);

    for (int i = start; i < vertices.size(); i++) {
        if(!visited[i]) DFSRecursive1(i, visited);
    }   
    for (auto x : visited) {
        x = false;
    }
    cout << endl;
    for (int i = start; i < vertices.size(); i++) {
        if (!visited[i]) DFSRecursive2(i, visited);
    }
    cout << endl;
}

void Graph::DFSNonRecursive(int start) {
    // ��ʼ��visited����
    vector<bool> visited(vertices.size(), false);
    ArcNode* arc = vertices[start].firstarc;
    // ����ʼ�����ջ�����
    dfs_stack.push(start);
    visited[start] = true;
    cout << name[start] << " ";

    while (!dfs_stack.empty()) {
        int v = dfs_stack.top();
        

        // �����ڽӽ��
        for (arc = vertices[v].firstarc; arc != nullptr; arc = arc->nextarc) {
            int adjvex = arc->adjvex;

            // ����ڽӽ��δ�����ʣ����������ջ
            if (!visited[adjvex]) {
                cout << name[adjvex] << " ";
                dfs_stack.push(adjvex);
                visited[adjvex] = true;
                break;
            }
        }
        if(arc==nullptr) dfs_stack.pop();
        //if(vertices[v].firstarc==nullptr) dfs_stack.pop();
    }

    cout << endl;
}

void Graph::BFS1(int start) {
    // ��ʼ��visited����
    vector<bool> visited(vertices.size(), false);

    // ����ʼ��������
    bfs_queue.push(start);

    while (!bfs_queue.empty()) {
        int v = bfs_queue.front();
        bfs_queue.pop();

        // ������δ�����ʣ�����ʲ����ڽӽ�������
        if (!visited[v]) {
            visited[v] = true;
            cout << name[v] << " ";

            // �����ڽӽ��
            for (ArcNode* arc = vertices[v].firstarc; arc != nullptr; arc = arc->nextarc) {
                int adjvex = arc->adjvex;
                if (!visited[adjvex]) {
                    bfs_queue.push(adjvex);
                }
            }
        }
    }

    cout << endl;
}

void Graph::BFS2(int start) {
    // ��ʼ��visited����
    vector<bool> visited(vertices.size(), false);

    // ����ʼ��������
    bfs_queue.push(start);

    while (!bfs_queue.empty()) {
        int v = bfs_queue.front();
        bfs_queue.pop();

        // ������δ�����ʣ�����ʲ����ڽӽ�������
        if (!visited[v]) {
            visited[v] = true;
            /*cout << name[v] << " ";*/

            // �����ڽӽ��
            for (ArcNode* arc = vertices[v].firstarc; arc != nullptr; arc = arc->nextarc) {
                int adjvex = arc->adjvex;
                if (!visited[adjvex]) {
                    cout << "( " << v << " , " << adjvex << " ) ";
                    bfs_queue.push(adjvex);
                }
            }
        }
    }

    cout << endl;
}


void Graph::DFSRecursiveTreeIndent(int v, vector<bool>& visited, int depth) {
    // ��ǽ��Ϊ�ѷ���
    visited[v] = true;
    cout << "|---";
    // �����ǰ�ڵ�
    for (int i = 0; i < depth; ++i) {
        cout << "---";
    }
    cout << name[v] << endl;

    // �����ڽӽ��
    for (ArcNode* arc = vertices[v].firstarc; arc != nullptr; arc = arc->nextarc) {
        int adjvex = arc->adjvex;

        // ����ڽӽ��δ�����ʣ���ݹ��������������
        if (!visited[adjvex]) {
            DFSRecursiveTreeIndent(adjvex, visited, depth + 1);
        }
    }
}

void Graph::DFSTree(int start) {
    // ��ʼ��visited����
    vector<bool> visited(vertices.size(), false);

    // �ݹ鹹���������������
    DFSRecursiveTreeIndent(start, visited, 0);
    cout << endl;
}

void Graph::BFSTree(int start) {
    // ��ʼ��visited����
    vector<bool> visited(vertices.size(), false);

    // ����ʼ�������У�����¼�ڵ�����
    bfstree_queue.push({ start, 0 });

    while (!bfstree_queue.empty()) {
        pair<int,int> front = bfstree_queue.front();
        bfstree_queue.pop();

        int v = front.first;
        int depth = front.second;

        // ������δ�����ʣ�����ʲ����ڽӽ�������
        if (!visited[v]) {
            visited[v] = true;

            cout << "|---";
            // �����ǰ�ڵ㣬�������ȷ������
            for (int i = 0; i < depth; ++i) {
                cout << "---";
            }
            cout << name[v] << endl;

            // �����ڽӽ��
            for (ArcNode* arc = vertices[v].firstarc; arc != nullptr; arc = arc->nextarc) {
                int adjvex = arc->adjvex;

                // ����ڽӽ��δ�����ʣ�������в���¼���
                if (!visited[adjvex]) {
                    bfstree_queue.push({ adjvex, depth + 1 });
                }
            }
        }
    }

    cout << endl;
}

void Graph::PrintGraph() {
    for (int i = 1; i < vertices.size(); ++i) {
        cout << "Vertex " << name[vertices[i].data] << ": ";
        for (ArcNode* arc = vertices[i].firstarc; arc != nullptr; arc = arc->nextarc) {
            cout << name[arc->adjvex] << " (Weight: " << arc->weight << ")  ";
        }
        cout << endl;
    }
}
