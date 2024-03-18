#pragma once
#pragma warning(disable:26451)
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
using namespace std;

string name[26] = { "空",
    "乌鲁木齐","西宁","兰州","呼和浩特","西安",
    "北京","郑州","天津","徐州","沈阳",
    "大连","长春","哈尔滨","成都","武汉",
    "上海","昆明","贵阳","株洲","南昌",
    "福州","南宁","柳州","广州","深圳"
};

// 结构体表示边
struct Edge {
    int vertex1;  // 边的起点
    int vertex2;  // 边的终点
    int weight;   // 边的权重
};

// 邻接多重表的结点
struct ArcNode {
    int adjvex;              // 邻接结点的编号
    int weight;              // 边的权重
    ArcNode* nextarc;        // 指向下一个邻接结点
    ArcNode* opposite;       // 指向与当前边相反的边
};

// 图的顶点
struct VNode {
    int data;                // 顶点编号
    ArcNode* firstarc;       // 指向第一个邻接结点
};

// 图
class Graph {
private:
    vector<VNode> vertices;  // 存储图的顶点
    stack<int> dfs_stack;     // 深度优先遍历辅助栈
    queue<int> bfs_queue;     // 广度优先遍历辅助队列
    queue<pair<int, int>> bfstree_queue;
    // 深度优先遍历递归函数
    void DFSRecursive1(int v, vector<bool>& visited);
    void DFSRecursive2(int v, vector<bool>& visited);

public:
    Graph(const vector<VNode>& initialVertices);

    void Print();
    // 添加无向边
    void AddEdge(const Edge& edge);

    // 深度优先遍历
    void DFS(int start);

    // 非递归深度优先遍历
    void DFSNonRecursive(int start);

    // 广度优先遍历
    void BFS1(int start);

    void BFS2(int start);

    void DFSRecursiveTreeIndent(int v, vector<bool>& visited, int depth);

    // 构建深度优先生成树
    void DFSTree(int start);

    // 构建广度优先生成树
    void BFSTree(int start);

    // 打印图的邻接多重表
    void PrintGraph();
};

Graph::Graph(const vector<VNode>& initialVertices) : vertices(initialVertices) {
    // 可以在这里执行其他初始化操作，如果需要的话
}

void Graph::Print() {
    cout << "字典： " << endl;
    for (int i = 0; i < 26; i++) {
        cout <<"点" << i << ": " << name[i] << endl;
    }

    cout << "\n选择功能:" << endl;
    cout << "1. 深度优先搜索 (DFS)" << endl;
    cout << "2. 非递归深度优先搜索 DFS" << endl;
    cout << "3. 广度优先搜索 (BFS)" << endl;
    cout << "4. 深度优先生成树" << endl;
    cout << "5. 广度优先生成树" << endl;
    cout << "6. 打印图" << endl;
    cout << "0. Exit" << endl;

    cout << "输入功能: ";

}
void Graph::AddEdge(const Edge& edge) {
    ArcNode* arc1 = new ArcNode{ edge.vertex2, edge.weight, nullptr, nullptr };
    ArcNode* arc2 = new ArcNode{ edge.vertex1, edge.weight, nullptr, nullptr };

    // 添加边到v1的邻接多重表
    arc1->nextarc = vertices[edge.vertex1].firstarc;
    vertices[edge.vertex1].firstarc = arc1;

    // 添加边到v2的邻接多重表
    arc2->nextarc = vertices[edge.vertex2].firstarc;
    vertices[edge.vertex2].firstarc = arc2;

    // 设置边的相反边
    arc1->opposite = arc2;
    arc2->opposite = arc1;
}

void Graph::DFSRecursive1(int v, vector<bool>& visited) {
    // 标记当前结点为已访问
    visited[v] = true;
    cout << name[v] << " ";

    // 遍历邻接结点
    for (ArcNode* arc = vertices[v].firstarc; arc != nullptr; arc = arc->nextarc) {
        int adjvex = arc->adjvex;
        // 如果邻接结点未被访问，则递归访问
        if (!visited[adjvex]) {
            DFSRecursive1(adjvex, visited);
        }
    }
}

void Graph::DFSRecursive2(int v, vector<bool>& visited) {
    // 标记当前结点为已访问
    visited[v] = true;
    //cout << name[v] << " ";

    // 遍历邻接结点
    for (ArcNode* arc = vertices[v].firstarc; arc != nullptr; arc = arc->nextarc) {
        int adjvex = arc->adjvex;
        // 如果邻接结点未被访问，则递归访问
        if (!visited[adjvex]) {
            cout << "( " << v << " , " << adjvex << " ) ";
            DFSRecursive2(adjvex, visited);
        }
    }
}

void Graph::DFS(int start) {
    // 初始化visited数组
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
    // 初始化visited数组
    vector<bool> visited(vertices.size(), false);
    ArcNode* arc = vertices[start].firstarc;
    // 将起始结点入栈并输出
    dfs_stack.push(start);
    visited[start] = true;
    cout << name[start] << " ";

    while (!dfs_stack.empty()) {
        int v = dfs_stack.top();
        

        // 遍历邻接结点
        for (arc = vertices[v].firstarc; arc != nullptr; arc = arc->nextarc) {
            int adjvex = arc->adjvex;

            // 如果邻接结点未被访问，则输出并入栈
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
    // 初始化visited数组
    vector<bool> visited(vertices.size(), false);

    // 将起始结点入队列
    bfs_queue.push(start);

    while (!bfs_queue.empty()) {
        int v = bfs_queue.front();
        bfs_queue.pop();

        // 如果结点未被访问，则访问并将邻接结点入队列
        if (!visited[v]) {
            visited[v] = true;
            cout << name[v] << " ";

            // 遍历邻接结点
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
    // 初始化visited数组
    vector<bool> visited(vertices.size(), false);

    // 将起始结点入队列
    bfs_queue.push(start);

    while (!bfs_queue.empty()) {
        int v = bfs_queue.front();
        bfs_queue.pop();

        // 如果结点未被访问，则访问并将邻接结点入队列
        if (!visited[v]) {
            visited[v] = true;
            /*cout << name[v] << " ";*/

            // 遍历邻接结点
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
    // 标记结点为已访问
    visited[v] = true;
    cout << "|---";
    // 输出当前节点
    for (int i = 0; i < depth; ++i) {
        cout << "---";
    }
    cout << name[v] << endl;

    // 遍历邻接结点
    for (ArcNode* arc = vertices[v].firstarc; arc != nullptr; arc = arc->nextarc) {
        int adjvex = arc->adjvex;

        // 如果邻接结点未被访问，则递归输出并进行缩进
        if (!visited[adjvex]) {
            DFSRecursiveTreeIndent(adjvex, visited, depth + 1);
        }
    }
}

void Graph::DFSTree(int start) {
    // 初始化visited数组
    vector<bool> visited(vertices.size(), false);

    // 递归构建深度优先生成树
    DFSRecursiveTreeIndent(start, visited, 0);
    cout << endl;
}

void Graph::BFSTree(int start) {
    // 初始化visited数组
    vector<bool> visited(vertices.size(), false);

    // 将起始结点入队列，并记录节点的深度
    bfstree_queue.push({ start, 0 });

    while (!bfstree_queue.empty()) {
        pair<int,int> front = bfstree_queue.front();
        bfstree_queue.pop();

        int v = front.first;
        int depth = front.second;

        // 如果结点未被访问，则访问并将邻接结点入队列
        if (!visited[v]) {
            visited[v] = true;

            cout << "|---";
            // 输出当前节点，根据深度确定缩进
            for (int i = 0; i < depth; ++i) {
                cout << "---";
            }
            cout << name[v] << endl;

            // 遍历邻接结点
            for (ArcNode* arc = vertices[v].firstarc; arc != nullptr; arc = arc->nextarc) {
                int adjvex = arc->adjvex;

                // 如果邻接结点未被访问，则入队列并记录深度
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
