# 41343104 41343105

# 作業 Graph

# Graph 基本操作與演算法實作

## 解題說明

本次作業主要針對 Graph（圖形結構）進行實作與分析。  
Graph 可由頂點與邊組成，常見類型包含有向圖、無向圖、有權重圖與無權重圖。

本作業使用鄰接矩陣表示 Graph，並實作以下功能：

1. 建立 Graph 的資料結構。
2. 實作 DFS（Depth First Search，深度優先搜尋）。
3. 實作 BFS（Breadth First Search，廣度優先搜尋）。
4. 使用 DFS 判斷 Connected Components（連通元件）。
5. 分析程式的時間複雜度與空間複雜度。

## 解題策略

1. 使用二維陣列 `graph[MAX][MAX]` 作為鄰接矩陣。
2. 若 `graph[i][j] != 0`，表示節點 `i` 與節點 `j` 相連。
3. 使用 `visited[]` 陣列記錄節點是否已被拜訪。
4. DFS 採用遞迴方式，從起始節點一路拜訪尚未走訪的相鄰節點。
5. BFS 使用陣列手動模擬 Queue，不使用 STL 的 `queue`。
6. Connected Components 透過檢查所有尚未拜訪的節點，重複執行 DFS 找出所有連通區塊。

## 程式實作

以下為主要程式碼：

```cpp
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
```
## 效能分析

1.時間複雜度：

本程式使用鄰接矩陣表示 Graph，因此在 DFS 與 BFS 中，每拜訪一個節點時，都需要掃描該節點與其他所有節點是否相鄰。

- DFS 需要檢查每個節點的所有相鄰狀態，因此時間複雜度為 O(n²)
- BFS 同樣需要掃描鄰接矩陣，因此時間複雜度為 O(n²)
- Connected Components 會檢查所有節點，並對未拜訪節點執行 DFS，因此整體時間複雜度仍為 O(n²)
  
|          演算法         | 使用情況   | 時間複雜度 |
| :------------------: | :----- | :---: |
|          DFS         | 深度優先搜尋 | O(n²) |
|          BFS         | 廣度優先搜尋 | O(n²) |
| Connected Components | 判斷連通元件 | O(n²) |


2.空間複雜度：

- 鄰接矩陣 graph[MAX][MAX] 需要 O(n²) 空間
- visited[] 陣列需要 O(n) 空間
- DFS 遞迴呼叫最深可能為 O(n)
- BFS 使用陣列模擬 Queue，最多存放 O(n) 個節點
  
因此整體空間複雜度為 O(n²)。

## 測試與驗證

| 測試案例 | Graph 類型 | 起始點 | 預期輸出                                  | 實際輸出                                  | 備註     |
| :--: | :------: | :-: | :------------------------------------ | :------------------------------------ | :----- |
|  測試一 |  無向無權重圖  |  0  | DFS: 0 1 3 2                          | DFS: 0 1 3 2                          | 驗證 DFS |
|  測試二 |  無向無權重圖  |  0  | BFS: 0 1 2 3                          | BFS: 0 1 2 3                          | 驗證 BFS |
|  測試三 |  非完全連通圖  |  無  | Component 1: 0 1 3 2 / Component 2: 4 | Component 1: 0 1 3 2 / Component 2: 4 | 驗證連通元件 |
|  測試四 |   單一節點圖  |  0  | DFS: 0                                | DFS: 0                                | 邊界情況   |
|  測試五 |  完全不連通圖  |  無  | 每個節點各自為一個 Component                   | 每個節點各自為一個 Component                   | 驗證獨立節點 |


### 編譯與執行指令

```bash
$ g++ Graph.cpp -std=c++14 -o Graph
$ Graph.exe
DFS: 0 1 3 2
BFS: 0 1 2 3
Connected Components:
Component 1: 0 1 3 2
Component 2: 4
```

## 結論

本次作業使用鄰接矩陣建立 Graph，並完成 DFS、BFS 與 Connected Components 的實作。
DFS 適合用於深入搜尋節點路徑，BFS 則適合依照層級順序進行搜尋。

由測試結果可知，程式能正確輸出 DFS 與 BFS 的拜訪順序，也能成功判斷非完全連通圖中的不同連通元件。
此外，BFS 部分使用陣列手動模擬 Queue，避免使用未允許的標頭檔與 STL 容器，符合本次作業限制。

## 申論及開發報告

### 選擇鄰接矩陣的原因

1.實作方式簡單，適合用於節點數不多的 Graph

2.查詢兩節點是否相連只需要檢查 graph[i][j]，操作直觀

3.矩陣形式容易觀察節點之間的連接關係，方便除錯與測試

### 方法摘要

1.使用 graph[i][j] 表示節點 i 與節點 j 是否相連

2.使用 visited[] 紀錄節點是否已經被拜訪

3.DFS 使用遞迴方式處理相鄰且尚未拜訪的節點

4.BFS 使用陣列 q[] 搭配 front 與 rear 手動模擬 Queue

5.Connected Components 透過掃描所有節點，對尚未拜訪的節點執行 DFS

## 正確性要點

1.DFS 每次只拜訪尚未拜訪過的相鄰節點，因此不會重複走訪

2.BFS 使用 Queue 保證節點會依照距離起點的層級順序被處理。

3.Connected Components 會檢查所有節點，因此即使 Graph 不連通，也能完整找出所有區塊。

## 缺點

1.鄰接矩陣在節點很多但邊很少時會浪費空間。

2.DFS 遞迴太深時可能造成 Stack Overflow。

3.若 Graph 很大，使用鄰接串列會更有效率。
## 改進建議

1.可改用鄰接串列降低空間成本。

2.DFS 可改成非遞迴版本，避免遞迴過深。

3.若加入權重，可擴充 Kruskal、Prim 或 Dijkstra 等演算法。

## 分工說明

本次作業由兩位組員共同完成，依據各自負責內容進行分工如下：

| 學號 | 姓名 | 負責內容 |
|:--:|:--:|:--|
| 41343104 | 楊彩榕 | Graph 基本概念整理、DFS 與 BFS 程式設計、測試案例設計與結果驗證、報告撰寫 |
| 41343105 | 蕭婷亓 | Graph 表示法整理（鄰接矩陣與鄰接串列）、Connected Components 程式設計、效能分析與報告格式整理 |

## 分工內容說明

### 41343104 楊彩榕
1. 整理 Graph 基本定義與分類（有向 / 無向、有權重 / 無權重）。
2. 實作 DFS（Depth First Search）演算法。
3. 實作 BFS（Breadth First Search）演算法。
4. 設計測試資料並驗證程式正確性。
5. 撰寫整體作業報告內容。

### 41343105 蕭婷亓
1. 整理 Graph 表示方法（鄰接矩陣與鄰接串列）。
2. 實作 Connected Components 演算法。
3. 進行時間與空間複雜度分析。
4. 協助整理報告格式與內容校對。
5. 檢查程式執行結果與文件一致性。

## 協作方式

本組採分工合作方式進行，先各自完成負責部分，再進行整合與測試，確保程式正確性與報告內容完整性。
