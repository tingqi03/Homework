# 41343104 41343105

# 作業 Sorting Project

# 排序演算法實作

## 解題說明

這次作業主要是實作幾種常見的排序演算法，透過自己實際寫程式來了解不同排序法的運作方式以及它們之間的差異。

排序在很多程式中都很常用，例如查詢資料、整理資料或分析資料時，都會先進行排序，所以了解排序演算法是很重要的。

這次作業實作的排序方法有：

1. Insertion Sort
2. Quick Sort（Median-of-Three）
3. Iterative Merge Sort
4. Heap Sort
5. Composite Sort

另外利用不同大小的資料進行測試，並利用 chrono 計算執行時間，最後整理結果進行比較。

## 解題策略

1. 建立測試資料。
2. 產生 Worst Case Data。
3. 複製相同資料給各排序法使用。
4. 執行排序。
5. 利用 chrono 計算執行時間。
6. 整理測試結果。
7. 比較各排序法的效率差異

## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;


void copyArray(int from[], int to[], int n)
{
    for(int i = 0; i < n; i++)
        to[i] = from[i];
}

// Worst Case Data
void worstData(int a[], int n)
{
    for(int i = 0; i < n; i++)
        a[i] = n - i;
}

// Insertion Sort
void insertionSort(int a[], int n)
{
    for(int i = 1; i < n; i++)
    {
        int key = a[i];
        int j = i - 1;

        while(j >= 0 && a[j] > key)
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

// Median-of-Three（修正版）
void medianOfThree(int a[], int low, int high)
{
    int mid = (low + high) / 2;

    if(a[low] > a[mid]) swap(a[low], a[mid]);
    if(a[low] > a[high]) swap(a[low], a[high]);
    if(a[mid] > a[high]) swap(a[mid], a[high]);

    swap(a[mid], a[high]);
}

// Quick Sort Partition
int partition(int a[], int low, int high)
{
    medianOfThree(a, low, high);

    int pivot = a[high];
    int i = low - 1;

    for(int j = low; j < high; j++)
    {
        if(a[j] < pivot)
        {
            i++;
            swap(a[i], a[j]);
        }
    }

    swap(a[i + 1], a[high]);
    return i + 1;
}

void quickSort(int a[], int low, int high)
{
    if(low < high)
    {
        int pi = partition(a, low, high);
        quickSort(a, low, pi - 1);
        quickSort(a, pi + 1, high);
    }
}

// Bottom-up Merge Sort
void merge(int a[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for(int i = 0; i < n1; i++)
        L[i] = a[left + i];

    for(int j = 0; j < n2; j++)
        R[j] = a[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while(i < n1 && j < n2)
        a[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];

    while(i < n1) a[k++] = L[i++];
    while(j < n2) a[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(int a[], int n)
{
    for(int size = 1; size < n; size *= 2)
    {
        for(int left = 0; left < n - 1; left += 2 * size)
        {
            int mid = min(left + size - 1, n - 1);
            int right = min(left + 2 * size - 1, n - 1);

            if(mid < right)
                merge(a, left, mid, right);
        }
    }
}

// Heap Sort
void heapify(int a[], int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if(l < n && a[l] > a[largest]) largest = l;
    if(r < n && a[r] > a[largest]) largest = r;

    if(largest != i)
    {
        swap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}

void heapSort(int a[], int n)
{
    for(int i = n/2 - 1; i >= 0; i--)
        heapify(a, n, i);

    for(int i = n - 1; i > 0; i--)
    {
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}

// Composite Sort（混合策略）
void compositeSort(int a[], int n)
{
    if(n <= 50)
        insertionSort(a, n);
    else
        quickSort(a, 0, n - 1);
}


template <typename Func>
double measureTime(Func sortFunc, int data[], int n)
{
    int* temp = new int[n];
    copyArray(data, temp, n);

    volatile int sink = 0;

    auto start = high_resolution_clock::now();
    sortFunc(temp, n);
    sink += temp[0];
    auto end = high_resolution_clock::now();

    duration<double, milli> time = end - start;

    delete[] temp;
    return time.count();
}

int main()
{
    int sizes[6] = {500,1000,2000,3000,4000,5000};

    cout << "n\tInsertion\tQuick\tMerge\tHeap\tComposite\n";

    for(int i = 0; i < 6; i++)
    {
        int n = sizes[i];
        int* data = new int[n];

        worstData(data, n);

        cout << n << "\t"
             << measureTime([](int a[], int n){ insertionSort(a,n); }, data, n) << "\t"
             << measureTime([](int a[], int n){ quickSort(a,0,n-1); }, data, n) << "\t"
             << measureTime([](int a[], int n){ mergeSort(a,n); }, data, n) << "\t"
             << measureTime([](int a[], int n){ heapSort(a,n); }, data, n) << "\t"
             << measureTime([](int a[], int n){ compositeSort(a,n); }, data, n)
             << endl;

        delete[] data;
    }

    return 0;
}
```
## 效能分析

1.時間複雜度：

|      排序方法      |    最佳情況    |    平均情況    |    最差情況    |
| :------------: | :--------: | :--------: | :--------: |
|   Insertion Sort  |   O(n)    |    O(n²)   |    O(n²)   |
| Quick Sort  |    O(n log n)  |   O(n log n)  |    O(n²)   |
| Merge Sort |   O(n log n)   |    O(n log n)   |    O(n log n)   |
|   Heap Sort   | O(n log n) | O(n log n) | O(n log n) |
|Composite Sort| 視情況 | 視情況 |    視情況   |

從表格可以看出，Insertion Sort 在資料量增加時效率下降最快，而 Quick Sort、Merge Sort 和 Heap Sort 的表現較穩定。


2.空間複雜度：

|      排序方法      |   空間複雜度  |
| :------------: | :------: |
|   Insertion Sort  |   O(1)   |
| Quick Sort |   O(log n)   |
| Merge Sort  |   O(n)   |
|   Heap Sort   |    O(1)   |
|   Composite Sort |  視使用方式 |
  
Merge Sort 因為需要額外陣列進行合併，所以空間需求較高。

## 測試與驗證

| n | Insertion Sort| Quick Sort | Merge Sort| Heap Sort | Composite Sort |
|---|--------------:|--------:|-------:|------:|--------:|
|  500 |   0.41   | 0.05 | 0.08 |  0.10 | 0.05 |
| 1000 | 1.62 | 0.09 | 0.17 | 0.22 | 0.09 |
| 2000 | 6.48 | 0.20 | 0.38 | 0.50 | 0.20  |
| 3000 |  14.50 | 0.32 | 0.60 | 0.81 | 0.32 |
| 4000 | 25.90 | 0.45 | 0.84 | 1.12 | 0.45 |
| 5000  | 40.45  | 0.59 | 1.10 | 1.46 |  0.59 |

從結果可以發現，Insertion Sort 的執行時間隨著資料量增加而快速上升。

而 Quick Sort、Merge Sort 與 Heap Sort 的時間增加較平穩。

隨著資料量增加，也能明顯看出 O(n²) 與 O(n log n) 的差異

### 編譯與執行指令

```bash
g++ Sorting.cpp -std=c++14 -o Sorting

Sorting.exe
```

## 結論

- Insertion Sort 在資料小的時候還算快，但資料變大後效率下降很明顯
- Quick Sort 在大部分情況下表現最好
- Merge Sort 雖然穩定，但需要額外記憶體
- Heap Sort 表現穩定，但實作與常數成本稍高
- Composite Sort 透過小資料用插入排序，可以稍微提升整體效率
  
## 申論及開發報告

### 為什麼選擇這些排序法

1.這幾種排序法是課堂上比較常見的排序演算法

2.不同排序法有不同特點，適合拿來比較

3.可以透過實作了解排序的流程

### 方法摘要

1.使用陣列存放資料

2.每個排序法獨立寫成函式

3.排序完成後輸出結果確認

4.比較不同排序法的效率

## 正確性說明

1.Insertion Sort 是透過逐步插入方式，把每個元素放到正確位置，最後形成排序結果 

2.Quick Sort 使用 Median-of-Three 選 pivot，再透過 partition 分割左右區間並遞迴排序

3.Merge Sort 是用 bottom-up 的方式，不斷合併小區塊，最後完成排序

4.Heap Sort 先建立 max heap，再把最大值依序交換到後面完成排序

5.Composite Sort 會依照資料量決定使用 Insertion Sort 或 Quick Sort，以平衡效能
## 缺點

1. Insertion Sort 在資料變大時效能很差

2. Quick Sort 在最差情況下可能退化為 O(n²)

3. Merge Sort 需要額外記憶體空間
 
4. Heap Sort 常數較大，實際速度不一定最快

## 改進建議

1.可以加入更多排序演算法比較

2.使用更多測試資料分析效率

3.Quick Sort 可以改成隨機 Pivot

4.Merge Sort 可以改善空間使用量

## 分工說明

本次作業由兩位組員共同完成，依據各自負責內容進行分工如下：

|    學號    |  姓名 | 負責內容                                              |
| :------: | :-: | :------------------------------------------------ |
| 41343104 | 楊彩榕 | Heap Sort、Insertion Sort、測試與報告整理 |
| 41343105 | 蕭婷亓 | Merge Sort、Quick Sort、Composite Sort、效能分析與文件檢查                   |

## 分工內容說明

### 41343104 楊彩榕

1. 實作 Heap Sort
2. 實作 Insertion Sort
3. 測試程式結果  
4. 整理報告內容

### 41343105 蕭婷亓

1. 實作 Merge Sort
2. 實作 Quick Sort
3. 實作 Composite Sort
4. 效能分析與文件檢查 

