# 41343105

問題一 
Ackermann Function

## **遞迴方式**

## 解題說明
本題要求實現一個遞迴函式，計算Ackermann函數A(m,n)的結果
### 解題策略
1. 根據數學定義分三種情況:
   - 當 m = 0 時，回傳 n + 1。
   - 當 m > 0且 n = 0 時，呼叫 A(m - 1, 1)`。
   - 否則，先呼叫 A(m, n - 1)，再將結果作為 `A(m - 1, 結果)的第二個參數遞迴呼叫
2. 透過 if-else 條件式分支實作上述邏輯，讓程式能根據參數值進行正確的遞迴路徑
3. 終止條件為 m = 0，此時遞迴停止並開始回傳值，逐層往上收斂結果
## 程式實作
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

1. 時間複雜度：每個元素都有選與不選,2的n次方種新集合

2. 空間複雜度：儲存所有子集合需要同樣數量的空間

## 測試與驗證
### 測試案例

| 測試案例 | 輸入 S | 預期輸出 | 實際輸出 |
|----------|-------------|----------|----------|
| 測試一   | {}      | {0}      | {0}        |
| 測試二   | {a}     | {0,(a)}  | {0,(a)}        |
| 測試三   | {a,b}   | {0,(a),(b),(a,b)} | 正確       |
| 測試四   | {a,b,c} | {0,(a),(b),(c),(a,b),(a,c),(b,c),(a,b,c)} | 正確      |

### 編譯與執行指令

$ g++ -std=c++17 -o powerset powerset.cpp
$ ./powerset


## 結論

## 申論與開發報告

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

### 申論與開發報告

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
using namespace std;

int sigma(int n) {
    if (n < 0)
        throw "n < 0";
    else if (n <= 1)
        return n;
    return n + sigma(n - 1);
}

int main() {
    int result = sigma(3);
    cout << result << '\n';
}
```

## 效能分析

1. 時間複雜度：程式的時間複雜度為 $O(\log n)$。
2. 空間複雜度：空間複雜度為 $O(100\times \log n + \pi)$。

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 $n$ | 預期輸出 | 實際輸出 |
|----------|--------------|----------|----------|
| 測試一   | $n = 0$      | 0        | 0        |
| 測試二   | $n = 1$      | 1        | 1        |
| 測試三   | $n = 3$      | 6        | 6        |
| 測試四   | $n = 5$      | 15       | 15       |
| 測試五   | $n = -1$     | 異常拋出 | 異常拋出 |

### 編譯與執行指令

```shell
$ g++ -std=c++17 -o sigma sigma.cpp
$ ./sigma
6
```

### 結論

1. 程式能正確計算 $n$ 到 $1$ 的連加總和。  
2. 在 $n < 0$ 的情況下，程式會成功拋出異常，符合設計預期。  
3. 測試案例涵蓋了多種邊界情況（$n = 0$、$n = 1$、$n > 1$、$n < 0$），驗證程式的正確性。

## 申論及開發報告

### 選擇遞迴的原因

在本程式中，使用遞迴來計算連加總和的主要原因如下：

1. **程式邏輯簡單直觀**  
   遞迴的寫法能夠清楚表達「將問題拆解為更小的子問題」的核心概念。  
   例如，計算 $\Sigma(n)$ 的過程可分解為：  

   $$
   \Sigma(n) = n + \Sigma(n-1)
   $$

   當 $n$ 等於 1 或 0 時，直接返回結果，結束遞迴。

2. **易於理解與實現**  
   遞迴的程式碼更接近數學公式的表示方式，特別適合新手學習遞迴的基本概念。  
   以本程式為例：  

   ```cpp
   int sigma(int n) {
       if (n < 0)
           throw "n < 0";
       else if (n <= 1)
           return n;
       return n + sigma(n - 1);
   }
   ```

3. **遞迴的語意清楚**  
   在程式中，每次遞迴呼叫都代表一個「子問題的解」，而最終遞迴的返回結果會逐層相加，完成整體問題的求解。  
   這種設計簡化了邏輯，不需要額外變數來維護中間狀態。

透過遞迴實作 Sigma 計算，程式邏輯簡單且易於理解，特別適合展示遞迴的核心思想。然而，遞迴會因堆疊深度受到限制，當 $n$ 值過大時，應考慮使用迭代版本來避免 Stack Overflow 問題。

