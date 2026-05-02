#include <iostream>
using namespace std;

const int MAX = 100;
int graph[MAX][MAX];
bool visited[MAX];
int n;

// DFS
void DFS(int v) {
    visited[v] = true;
    cout << v << " ";

    for (int i = 0; i < n; i++) {
        if (graph[v][i] != 0 && !visited[i]) {
            DFS(i);
        }
    }
}

// 手刻 Queue
int q[MAX];
int front = 0, rear = 0;

void enqueue(int x) {
    q[rear++] = x;
}

int dequeue() {
    return q[front++];
}

bool isEmpty() {
    return front == rear;
}

// BFS
void BFS(int start) {
    front = rear = 0;

    visited[start] = true;
    enqueue(start);

    while (!isEmpty()) {
        int v = dequeue();
        cout << v << " ";

        for (int i = 0; i < n; i++) {
            if (graph[v][i] != 0 && !visited[i]) {
                visited[i] = true;
                enqueue(i);
            }
        }
    }
}

// Connected Components
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
