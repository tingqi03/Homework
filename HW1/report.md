# 41343105

問題一 
Max/Min Heap

## 解題說明
本題要求根據 MaxPQ 的設計，實作一個 Min Priority Queue（MinPQ），並使用 Binary Heap 完成 MinHeap 類別。

MinHeap 為完全二元樹，並滿足：
每個節點的值 ≤ 子節點（Min Heap 性質）
### 解題策略
1. 資料結構選擇
使用陣列實作 Binary Heap
index 從 1 開始方便計算 parent / child
parent = i / 2
left child = 2i
right child = 2i + 1
2. MinPQ 抽象類別
IsEmpty()：判斷是否為空
Top()：回傳最小值
Push()：插入元素
Pop()：刪除最小值
3. MinHeap 實作方法
Push：使用 up-heap（往上調整）
Pop：使用 down-heap（往下調整）
## 程式實作
```cpp
#include <iostream>
#include <vector>
#include <stdexcept>

template <class T>
class MinPQ {
public:
    virtual ~MinPQ() {}
    virtual bool IsEmpty() const = 0;
    virtual const T& Top() const = 0;
    virtual void Push(const T& x) = 0;
    virtual void Pop() = 0;
};


template <class T>
class MinHeap : public MinPQ<T> {
private:
    std::vector<T> heap;

public:
    bool IsEmpty() const override {
        return heap.empty();
    }

    const T& Top() const override {
        if (IsEmpty()) throw std::runtime_error("Heap is empty");
        return heap[0];
    }

    void Push(const T& x) override {
        heap.push_back(x);
        int current = heap.size() - 1;
        
       
        while (current > 0) {
            int parent = (current - 1) / 2;
            if (heap[current] < heap[parent]) {
                std::swap(heap[current], heap[parent]);
                current = parent;
            } else break;
        }
    }

    void Pop() override {
        if (IsEmpty()) throw std::runtime_error("Heap is empty");
        
        heap[0] = heap.back(); 
        heap.pop_back();
        
        if (!heap.empty()) {
            int current = 0;
            int size = heap.size();
            while (true) {
                int left = 2 * current + 1;
                int right = 2 * current + 2;
                int smallest = current;

                if (left < size && heap[left] < heap[smallest]) smallest = left;
                if (right < size && heap[right] < heap[smallest]) smallest = right;

                if (smallest != current) {
                    std::swap(heap[current], heap[smallest]);
                    current = smallest;
                } else break;
            }
        }
    }
};
```
## 效能分析

1. 時間複雜度：Push 與 Pop：皆為 $O(\log n)$，因為樹的高度與元素個數呈對數關係。Top：$O(1)$，直接存取陣列首位。
2. 空間複雜度：$O(n)$，需儲存 $n$ 個元素。

## 測試與驗證
### 測試案例

| 測試案例 | 操作序列 | 預期輸出 | 實際輸出 |
|----------|-------------|----------|----------|
| 測試一   | Push(10, 5, 20)    | 5     | 5        |
| 測試二   | Pop() 之後   | 10 | 10       |
### 編譯與執行指令

$ g++ -std=c++17 -o powerset powerset.cpp
$ ./powerset


## 結論

## 申論及開發報告

Ackermann 函數是一個經典的遞迴函數，常用來測試程式語言的遞迴能力。在本次作業中，我選擇直接使用遞迴來實作這個函數，原因如下：

1. 符合數學定義：Ackermann 的定義本身就是遞迴式，使用遞迴可以讓程式邏輯與數學公式一致，容易閱讀與理解
2. 實作簡單：使用三層 if-else 條件就可以處理所有情況，讓程式維持簡潔
3. 展示遞迴威力：透過這題可以觀察遞迴如何呼叫自身，也讓我體會到堆疊過深會導致程式錯誤的風險

## **非遞迴方式**

## 解題說明

本題要求實作 Ackermann 函數  A(m, n)。由於 Ackermann 函數是一個高度遞迴的數學函數，若直接使用遞迴實作會容易導致堆疊溢位。本版本改用 stack（堆疊）資料結構模擬遞迴，實現非遞迴版本。

## 解題策略

1. 使用 stack`模擬函數呼叫堆疊，避免系統遞迴造成的堆疊溢位問題。
2. 根據 Ackermann 函數定義進行模擬分支：
   - 若 m = 0，直接回傳 n + 1。
   - 若 n = 0，轉為呼叫 A(m-1, 1)，把 m - 1 壓入 stack。
   - 其他情況下，先將 m 與 m - 1 依序壓入，並將 n 減 1。
3. 使用 while 迴圈不斷處理 stack 中的內容，直到 stack 為空為止。

## 程式實作

```cpp
#include <iostream>
#include <stack>
using namespace std;

int ackermann_iterative(int m, int n) {
    stack<int> s;
    s.push(m);
    while (!s.empty()) {
        m = s.top();
        s.pop();

        if (m == 0) {
            n = n + 1;
        } else if (n == 0) {
            s.push(m - 1);
            n = 1;
        } else {
            s.push(m - 1);
            s.push(m);
            n = n - 1;
        }
    }
    return n;
}

int main() {
    int m = 3, n = 2;
    cout << ackermann_iterative(m, n) << '\n';
}
```

## 效能分析

1. 時間複雜度：Ackermann 函數的成長速度非常快，當 m 和 n 增加時，計算次數會爆炸性增加，因此時間複雜度極高，無法用一般公式表示。
2. 空間複雜度：使用 stack 模擬遞迴，所需空間與函數呼叫層數成正比，為 O(A(m, n))。雖然空間使用仍高，但不會造成系統堆疊溢位，比起遞迴方式更穩定。


## 測試與驗證

| 測試案例 | 輸入 (m, n) | 預期輸出 | 實際輸出 |
|----------|-------------|----------|----------|
| 測試一   | 0, 5        | 6        | 6        |
| 測試二   | 1, 2        | 4        | 4        |
| 測試三   | 2, 2        | 7        | 7        |
| 測試四   | 3, 2        | 29       | 29       |


## 編譯與執行指令

```bash
g++ -std=c++17 -o ackermann_iter ackermann_iter.cpp
./ackermann_iter
```

## 結論

1. 使用 stack 取代系統遞迴的方式，成功計算 Ackermann 函數，且避免了堆疊溢位的問題。
2. 非遞迴版本在中小型輸入下能穩定執行，結果與遞迴版本相同。
3. 雖然程式邏輯稍微複雜，但更適合實務應用，具備良好穩定性與效能。

### 申論及開發報告

本次使用非遞迴的方式來實作 Ackermann 函數，是為了解決遞迴版本容易發生堆疊溢位的問題。透過 stack 模擬遞迴行為，可以讓程式在輸入較大的情況下仍能正確執行。
在實作過程中，我深入了解了「如何將遞迴轉換成迴圈」的技巧，也學會使用 stack 控制流程。雖然非遞迴的寫法比遞迴更難撰寫與理解，但它在實際應用上更穩定、也更安全。
透過這次作業，我不僅熟悉了 Ackermann 函數的運作邏輯，也訓練了轉換程式邏輯與資料結構的能力，是一次有挑戰但收穫很大的練習。

問題二
Powerset

## 解題說明

用以計算S的冪集合,包含子集合的所有集合。

### 解題策略

1. 若已知n-1個元素冪集合,則第n個元素可選或不可選,因此新冪集合=舊冪集合。

## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
#include <string>

using namespace std;


void printSubsets(const vector<string>& set, vector<string>& currentSet, int index) {
    
    if (index == set.size()) {
        // Print the current subset
        cout << "{ ";
        for (const auto& element : currentSet) {
            cout << element << " ";
        }
        cout << "}" << endl;
        return;
    }

    
    currentSet.push_back(set[index]);
    printSubsets(set, currentSet, index + 1);

    
    currentSet.pop_back();
    printSubsets(set, currentSet, index + 1);
}


void computePowerset(const vector<string>& set) {
    vector<string> currentSet; // Temporary vector to store current subset
    printSubsets(set, currentSet, 0);
}

int main() {
    vector<string> set = {"a", "b", "c"};  // Set S = {a, b, c}
    
    cout << "Powerset of {a, b, c} is:" << endl;
    computePowerset(set);  
    return 0;
}
```

## 效能分析

1. 時間複雜度：每個元素選與不選,因此共有2的n次方種子集合。
2. 空間複雜度：儲存所有子集合的時間。

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 S | 預期輸出 | 實際輸出 |
|----------|--------------|----------|----------|
| 測試一   | {}      | {0}       | {0}  |
| 測試二   | {a}     | {0,(a)}   |{0,(a)} |
| 測試三   | {a,b}   | {0,(a),(b),(a,b)} | 正確 |
| 測試四   | {a,b,c} | {0,(a),(b),(c),(a,b),(a,c),(b,c),(a,b,c)} | 正確 |

### 編譯與執行指令

$ g++ -std=c++17 -o powerset powerset.cpp

$ ./powerset



### 結論

利用S的冪集合分解了問題與結構的思想。

## 申論及開發報告

### 選擇遞迴的原因

在本程式中，使用遞迴來計算連加總和的主要原因如下：

1. **程式邏輯簡單直觀**
   使得整體邏輯更意理解
2.**語意清晰且可擴充**
    程式能容易擴充到任何型別得集合元素
  
   


