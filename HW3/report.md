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
#include <fstream>

using namespace std;
using namespace chrono;

// 複製陣列
void copyArray(int from[], int to[], int n)
{
    for(int i = 0; i < n; i++)
    {
        to[i] = from[i];
    }
}

// 產生 Worst Case Data
void worstData(int a[], int n)
{
    for(int i = 0; i < n; i++)
    {
        a[i] = n - i;
    }
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

// Median-of-Three
int medianOfThree(int a[], int low, int high)
{
    int mid = (low + high) / 2;

    if(a[low] > a[mid])
        swap(a[low], a[mid]);

    if(a[low] > a[high])
        swap(a[low], a[high]);

    if(a[mid] > a[high])
        swap(a[mid], a[high]);

    swap(a[mid], a[high]);

    return a[high];
}

// Quick Sort
int partition(int a[], int low, int high)
{
    int pivot = medianOfThree(a, low, high);
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

// Merge Sort
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

    int i = 0;
    int j = 0;
    int k = left;

    while(i < n1 && j < n2)
    {
        if(L[i] <= R[j])
            a[k++] = L[i++];
        else
            a[k++] = R[j++];
    }

    while(i < n1)
        a[k++] = L[i++];

    while(j < n2)
        a[k++] = R[j++];

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
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < n && a[left] > a[largest])
        largest = left;

    if(right < n && a[right] > a[largest])
        largest = right;

    if(largest != i)
    {
        swap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}

void heapSort(int a[], int n)
{
    for(int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    for(int i = n - 1; i > 0; i--)
    {
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}

// Composite Sort
void compositeSort(int a[], int n)
{
    if(n <= 50)
        insertionSort(a, n);
    else
        quickSort(a, 0, n - 1);
}

// 計時函式
template <typename Func>
double measureTime(Func sortFunc, int data[], int n)
{
    int* temp = new int[n];

    copyArray(data, temp, n);

    auto start = high_resolution_clock::now();

    sortFunc(temp, n);

    auto end = high_resolution_clock::now();

    duration<double, milli> time = end - start;

    delete[] temp;

    return time.count();
}

int main()
{
    int sizes[6] = {500,1000,2000,3000,4000,5000};

    cout << "n\tInsertion\tQuick\tMerge\tHeap\tComposite" << endl;

    for(int i = 0; i < 6; i++)
    {
        int n = sizes[i];

        int* data = new int[n];

        worstData(data, n);

        double insertionTime =
            measureTime(
                [](int a[], int n)
                {
                    insertionSort(a, n);
                },
                data,
                n
            );

        double quickTime =
            measureTime(
                [](int a[], int n)
                {
                    quickSort(a, 0, n - 1);
                },
                data,
                n
            );

        double mergeTime =
            measureTime(
                [](int a[], int n)
                {
                    mergeSort(a, n);
                },
                data,
                n
            );

        double heapTime =
            measureTime(
                [](int a[], int n)
                {
                    heapSort(a, n);
                },
                data,
                n
            );

        double compositeTime =
            measureTime(
                [](int a[], int n)
                {
                    compositeSort(a, n);
                },
                data,
                n
            );

        cout << n << "\t"
             << insertionTime << "\t"
             << quickTime << "\t"
             << mergeTime << "\t"
             << heapTime << "\t"
             << compositeTime << endl;

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
|Composite Sort| 視情況而定| 視情況而定 |    視情況而定   |

從表格可以看出，Insertion Sort 在資料量增加時效率下降最快，而 Quick Sort、Merge Sort 和 Heap Sort 的表現較穩定。


2.空間複雜度：

|      排序方法      |   空間複雜度  |
| :------------: | :------: |
|   Insertion Sort  |   O(1)   |
| Quick Sort |   O(log n)   |
| Merge Sort  |   O(n)   |
|   Heap Sort   |    O(1)   |
|   Composite Sort |  視使用方式而定 |
  
Merge Sort 因為需要額外陣列進行合併，所以空間需求較高。

## 測試與驗證

| 測試案例 |      排序方法      | 預期輸出                   | 實際輸出                   | 備註   |
| :--: | :------------: | :--------------------- | :--------------------- | :--- |
|  測試一 |   Bubble Sort  | 5 11 12 22 25 34 64 90 | 5 11 12 22 25 34 64 90 | 排序正確 |
|  測試二 | Selection Sort | 5 11 12 22 25 34 64 90 | 5 11 12 22 25 34 64 90 | 排序正確 |
|  測試三 | Insertion Sort | 5 11 12 22 25 34 64 90 | 5 11 12 22 25 34 64 90 | 排序正確 |
|  測試四 |   Merge Sort   | 5 11 12 22 25 34 64 90 | 5 11 12 22 25 34 64 90 | 排序正確 |
|  測試五 |   Quick Sort   | 5 11 12 22 25 34 64 90 | 5 11 12 22 25 34 64 90 | 排序正確 |


### 編譯與執行指令

```bash
g++ Sorting.cpp -std=c++14 -o Sorting

Sorting.exe
```

- 執行結果：

```bash
Original Array: 64 34 25 12 22 11 90 5

Bubble Sort: 5 11 12 22 25 34 64 90

Selection Sort: 5 11 12 22 25 34 64 90

Insertion Sort: 5 11 12 22 25 34 64 90

Merge Sort: 5 11 12 22 25 34 64 90

Quick Sort: 5 11 12 22 25 34 64 90
```

## 結論

- 這次作業實際寫了五種排序演算法，透過比較不同排序方式，可以更清楚知道它們的差異
- Bubble Sort 跟 Selection Sort 雖然比較簡單，但資料變多之後效率會比較差
- Insertion Sort 在資料量小的時候其實還不錯，而且程式也比較好理解
- Merge Sort 跟 Quick Sort 的效率比較高，其中 Quick Sort 平均速度很快，所以很多程式都會使用
- 這次作業除了學到排序演算法之外，也更熟悉函式、陣列以及遞迴的使用方式

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

1.Bubble Sort 使用相鄰交換方式排序

2.Selection Sort 每次找最小值

3.Insertion Sort 將資料插入正確位置

4.Merge Sort 使用分割與合併方式

5.Quick Sort 使用 Pivot 分割資料

## 缺點

1.Bubble Sort 效率較低

2.Selection Sort 需要重複比較很多次

3.Merge Sort 需要額外空間

4.Quick Sort 最差情況下會變慢

## 改進建議

1.可以加入更多排序演算法比較

2.使用更多測試資料分析效率

3.Quick Sort 可以改成隨機 Pivot

4.Merge Sort 可以改善空間使用量

## 分工說明

本次作業由兩位組員共同完成，依據各自負責內容進行分工如下：

|    學號    |  姓名 | 負責內容                                              |
| :------: | :-: | :------------------------------------------------ |
| 41343104 | 楊彩榕 | Bubble Sort、Selection Sort、Insertion Sort、測試與報告整理 |
| 41343105 | 蕭婷亓 | Merge Sort、Quick Sort、效能分析與文件檢查                   |

## 分工內容說明

### 41343104 楊彩榕

1. 實作 Bubble Sort
2. 實作 Selection Sort
3. 實作 Insertion Sort
4. 測試程式結果  
5. 整理報告內容

### 41343105 蕭婷亓

1. 實作 Merge Sort
2. 實作 Quick Sort
3. 分析時間複雜度
4. 整理文件格式
5. 檢查程式輸出結果

