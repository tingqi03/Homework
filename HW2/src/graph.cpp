#include <iostream>
#include <queue>
using namespace std;

const int MAX = 100;
int graph[MAX][MAX];
bool visited[MAX];
int n;

void DFS(int v) {
    visited[v] = true;
    cout << v << " ";

    for (int i = 0; i < n; i++) {
        if (graph[v][i] != 0 && !visited[i]) {
            DFS(i);
        }
    }
}

void BFS(int start) {
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        cout << v << " ";

        for (int i = 0; i < n; i++) {
            if (graph[v][i] != 0 && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
}

void connectedComponents() {
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    int count = 0;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            cout << "Component " << ++count << ": ";
            DFS(i);
            cout << endl;
        }
    }
}

int main() {
    n = 5;

    int temp[5][5] = {
        {0, 1, 1, 0, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = temp[i][j];
        }
    }

    for (int i = 0; i < n; i++) visited[i] = false;
    cout << "DFS: ";
    DFS(0);
    cout << endl;

    for (int i = 0; i < n; i++) visited[i] = false;
    cout << "BFS: ";
    BFS(0);
    cout << endl;

    cout << "Connected Components:" << endl;
    connectedComponents();

    return 0;
}
