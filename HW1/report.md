# 41343105

問題一 
Max/Min Heap

## 解題說明
本題要求根據 MaxPQ 的設計，實作一個 Min Priority Queue（MinPQ），並使用 Binary Heap 完成 MinHeap 類別。

MinHeap 為完全二元樹，並滿足：
每個節點的值 ≤ 子節點（Min Heap 性質）
### 解題策略
1. 資料結構選擇
- 使用陣列實作 Binary Heap
- index 從 1 開始方便計算 parent / child
- parent = i / 2
- left child = 2i
- right child = 2i + 1
2. MinPQ 抽象類別
- IsEmpty()：判斷是否為空
- Top()：回傳最小值
- Push()：插入元素
- Pop()：刪除最小值
3. MinHeap 實作方法
- Push：使用 up-heap（往上調整）
- Pop：使用 down-heap（往下調整）
## 程式實作
```cpp
#include <iostream>
using namespace std;

template <class T>
class MinPQ {
public:
    virtual ~MinPQ() {}
    virtual bool IsEmpty() const = 0;
    virtual const T& Top() const = 0;
    virtual void Push(const T&) = 0;
    virtual void Pop() = 0;
};

template <class T>
class MinHeap : public MinPQ<T> {
private:
    T* heap;
    int capacity;
    int size;

    void Resize() {
        capacity *= 2;
        T* newHeap = new T[capacity];
        for (int i = 1; i <= size; i++)
            newHeap[i] = heap[i];
        delete[] heap;
        heap = newHeap;
    }

public:
    MinHeap(int cap = 100) {
        capacity = cap;
        size = 0;
        heap = new T[capacity];
    }

    ~MinHeap() {
        delete[] heap;
    }

    bool IsEmpty() const override {
        return size == 0;
    }

    const T& Top() const override {
        return heap[1];
    }

    void Push(const T& x) override {
        if (size + 1 == capacity)
            Resize();

        int i = ++size;

        while (i != 1 && x < heap[i / 2]) {
            heap[i] = heap[i / 2];
            i /= 2;
        }
        heap[i] = x;
    }

    void Pop() override {
        if (IsEmpty()) return;

        T last = heap[size--];
        int i = 1, child = 2;

        while (child <= size) {
            if (child < size && heap[child] > heap[child + 1])
                child++;

            if (last <= heap[child]) break;

            heap[i] = heap[child];
            i = child;
            child *= 2;
        }

        heap[i] = last;
    }
};
```
## 效能分析

1,Push：O(log n)，最多往上調整高度

2.Pop：O(log n)，最多往下調整高度

3.Top：O(1)

## 測試與驗證
### 測試案例

| 測試案例 | 操作序列 | 預期輸出 | 實際輸出 |
|----------|-------------|----------|----------|
| 測試一   |插入 5, 3, 8 → Top()   | 3     |3       |
| 測試二   |插入 10, 4, 7 → Top()  | 4 | 4       |
| 測試三	   |插入 10, 4, 7 → Pop() → Top() | 7 |	7 |
| 測試四	   |插入 6, 2, 9 → Pop() → Pop() → Top()| 9 | 9 |
### 編譯與執行指令

```bash
g++ -std=c++17 -o minheap minheap.cpp
./minheap
```

## 結論
成功實作 MinHeap，並完成 Priority Queue 功能。
透過 Binary Heap 可有效維持最小值於根節點。
## 申論及開發報告

本題學習到：

1.Priority Queue 抽象設計

2.Heap 的上濾與下濾操作

3.陣列實作完全二元樹技巧

4.時間複雜度分析（log n）
問題二
Binary Search Tree

## 解題說明

(a) 建立 BST 並分析高度

(b) 實作刪除節點
## 解題策略

1. BST 特性
- 左子樹 < 根 < 右子樹
2. (a) 隨機插入
- 使用亂數產生節點
- 計算樹高度
3. (b) 刪除節點三種情況
(1.)無子節點
(2.)一個子節點
(3.)兩個子節點（用 inorder successor）
## 程式實作

```cpp
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;

    Node* Insert(Node* node, int key) {
        if (!node) return new Node(key);

        if (key < node->key)
            node->left = Insert(node->left, key);
        else
            node->right = Insert(node->right, key);

        return node;
    }

    int Height(Node* node) {
        if (!node) return 0;
        return 1 + max(Height(node->left), Height(node->right));
    }

    Node* Delete(Node* node, int key) {
        if (!node) return nullptr;

        if (key < node->key)
            node->left = Delete(node->left, key);
        else if (key > node->key)
            node->right = Delete(node->right, key);
        else {
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            }
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* succ = node->right;
            while (succ->left)
                succ = succ->left;

            node->key = succ->key;
            node->right = Delete(node->right, succ->key);
        }

        return node;
    }

public:
    BST() { root = nullptr; }

    void Insert(int key) { root = Insert(root, key); }

    int GetHeight() { return Height(root); }

    void DeleteKey(int key) { root = Delete(root, key); }
};

int main() {
    srand(time(0));
    int test[] = {100, 500, 1000, 2000};

    for (int n : test) {
        BST tree;

        for (int i = 0; i < n; i++)
            tree.Insert(rand());

        int h = tree.GetHeight();
        double ratio = h / log2(n);

        cout << "n=" << n
             << " height=" << h
             << " ratio=" << ratio << endl;
    }

    return 0;
}
```

## 效能分析
   1.插入：平均 O(log n)，最差 O(n)
   
   2.刪除：平均 O(log n)，最差 O(n)
   
   3.高度：平均 O(log n)
 

## 測試與驗證

| 測試案例 | 輸入 (m, n) | 預期輸出 | 實際輸出 |
|----------|-------------|----------|----------|
|測試一	|  插入 5, 3, 7, 2, 4 → Height()| 3 | 3 |
|測試二	|  插入 10, 5, 15, 3, 7 → Height()|	3 |	3 |
|測試三	|  插入 10, 5, 15 → Delete(5) → Height()| 2 | 2 |
|測試四	|  插入 10, 5, 15 → Delete(10) → Height() | 2 | 2 |
|測試五	|  插入 8, 3, 10, 1, 6 → Delete(3) → Height()| 3 | 3 |


## 編譯與執行指令

```bash
g++ -std=c++17 -o bst bst.cpp
./bst
```

## 結論

隨機 BST 的高度接近 O(log n)，
因此 height/log₂n 約為常數（≈2）。
刪除操作需依節點子樹情況分類處理。

### 申論及開發報告

本題學習到：

1.BST 結構與操作
2.隨機插入對樹高度影響
3.刪除節點演算法設計
4.時間複雜度分析與實驗驗證



