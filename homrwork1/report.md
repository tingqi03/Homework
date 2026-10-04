# 41343105

問題一 
Ackermann Function

## **遞迴方式**

## 解題說明
這題是要用遞迴的方式來計算Ackermann函數A(m,n)的結果
### 解題策略
1. 根據Ackermann 函數的數學定義分三種情況:
   - 當 m = 0 時，回傳 n + 1。
   - 當 m > 0且 n = 0 時，呼叫 A(m - 1, 1)。
   - 否則，先呼叫 A(m, n - 1)，再將結果作為 A(m - 1, 結果)的第二個參數遞迴呼叫
2. 透過 if-else 條件式分支實作上述邏輯，讓程式能根據參數值進行正確的遞迴路徑
3. 終止條件為 m = 0，此時遞迴停止並開始回傳值，逐層往上收斂結果
## 程式實作
```cpp
#include <iostream>
using namespace std;

int ackermann(int m, int n) {
    if (m == 0)
        return n + 1;
    else if (n == 0)
        return ackermann(m - 1, 1);
    else
        return ackermann(m - 1, ackermann(m, n - 1));
}

int main() {
    int m = 3, n = 2;

    cout << ackermann(m, n) << endl;

    return 0;
}
```
## 效能分析

1. 時間複雜度：Ackermann 函數的成長很快，當 m 和 n 變大時，程式需要計算很多次。

2. 空間複雜度：因為使用遞迴，所以會使用到系統的 stack，遞迴次數越多，需要的空間也越多。

## 測試與驗證
### 測試案例

| 測試案例 | 輸入 (m,n) | 預期輸出 | 實際輸出 |
|----------|-------------|----------|----------|
| 測試一   | (0,5)      | 6      | 6        |
| 測試二   | (1,2)     | 4  | 4        |
| 測試三   | (2,2)   | 7 | 7       |
| 測試四   | (3,2) | 29 | 29      |

### 編譯與執行指令

$ g++ -std=c++17 -o ackermann ackermann.cpp 
./ackermann


## 結論

1. 這次使用遞迴方式來實作 Ackermann 函數，讓我比較了解函數自己呼叫自己的方式。
2. Ackermann 函數的計算量會隨著輸入增加而快速變大，所以輸入不能設得太大。
3. 透過這次作業，我也比較了解遞迴的運作方式，以及遞迴層數太深可能會造成記憶體使用增加的問題。
   
## 申論及開發報告

Ackermann 函數本身就是使用遞迴定義的，所以我選擇直接按照數學定義來寫程式。

在寫程式的時候，我先處理 m = 0 的情況，再處理 n = 0 的情況，最後處理其他情況。這樣可以讓程式按照不同條件進行遞迴。

一開始看 Ackermann 函數的公式時，我覺得它的遞迴方式比較難理解，尤其是最後一種情況會連續呼叫兩次函數。不過實際寫成程式後，對遞迴的運作方式比較有概念。

透過這次作業，我也了解到 Ackermann 函數的成長速度很快，因此不能隨便輸入很大的數字。

## **非遞迴方式**

## 解題說明

Ackermann 函數原本是使用遞迴方式來計算，但是也可以使用 stack 來模擬遞迴。

這個版本不直接讓函數自己呼叫自己，而是使用 stack 儲存需要處理的資料，再搭配 while 迴圈來完成計算。。

## 解題策略

1. 建立一個 stack，用來模擬原本的函數呼叫。
2. 一開始先把 m 放進 stack。
3. 使用 while 迴圈，只要 stack 裡面還有資料就繼續計算。
4. 當 m = 0 時，讓 n 加 1。
5. 當 n = 0 時，把 m - 1 放進 stack，並把 n 設為 1。
6. 其他情況則把需要處理的資料放進 stack，並讓 n 減 1。
7. 最後 stack 為空時，n 就是 Ackermann 函數的結果。
   
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

1. 時間複雜度：Ackermann 函數成長非常快，當輸入增加時，需要執行的次數也會快速增加，所以計算時間會變長。
2. 空間複雜度：使用 stack 來儲存需要處理的資料。輸入越大時，stack 可能需要儲存越多資料，因此記憶體使用量也會增加。


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
2. 雖然程式的寫法比遞迴版本稍微複雜，但是可以讓我了解如何使用 stack 來模擬遞迴。
3. 兩種方法最後都可以得到相同的結果，也讓我比較了解遞迴和 stack 之間的關係。
### 申論及開發報告

這次使用非遞迴方式實作 Ackermann 函數，主要是想了解如果不用函數自己呼叫自己，要怎麼完成原本的遞迴流程。

我使用 stack 把需要處理的 m 存起來，再透過 while 迴圈一個一個處理。

其中比較難理解的是原本遞迴的部分要怎麼轉換成 stack 的操作。實際寫完之後，我比較了解 stack 的先進後出特性，也知道可以利用 stack 來模擬函數呼叫。

透過這次練習，我學到不只是 Ackermann 函數，也了解遞迴程式可以使用資料結構來改成非遞迴的寫法。
問題二
Powerset

## 解題說明

這題是要計算集合 S 的 Powerset，也就是找出集合中所有可能的子集合。
### 解題策略

每處理一個元素時，都會分成兩種情況：

1. 把這個元素放進目前的子集合。
2. 不把這個元素放進目前的子集合。

然後繼續處理下一個元素。

當所有元素都處理完時，就代表找到一個完整的子集合，這時候把它印出來。
## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
#include <string>

using namespace std;


void printSubsets(const vector<string>& set, vector<string>& currentSet, int index) {
    
    if (index == set.size()) {
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

這次 Powerset 使用遞迴的方式來完成，主要是因為每個元素都有「選擇」和「不選擇」兩種情況，所以很適合使用遞迴來處理。

在寫程式的時候，我使用 currentSet 來記錄目前選到的元素。

如果選擇加入元素，就先使用 push_back 把元素放進去，再繼續處理下一個元素。

處理完之後，再使用 pop_back 把剛剛加入的元素移除，接著處理不選擇這個元素的情況。

這樣就可以把所有可能的子集合找出來。

透過這次作業，我比較了解遞迴可以用來處理很多種可能，也知道 Powerset 的數量會隨著元素增加而快速增加。
   

