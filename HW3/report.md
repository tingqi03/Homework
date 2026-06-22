# 41343104 41343105

# 作業 Sorting Project

# 排序演算法實作

## 解題說明

這次作業主要是實作幾種常見的排序演算法，透過自己實際寫程式來了解不同排序法的運作方式以及它們之間的差異。

排序在很多程式中都很常用，例如查詢資料、整理資料或分析資料時，都會先進行排序，所以了解排序演算法是很重要的。

這次作業實作的排序方法有：

1. Bubble Sort（氣泡排序）
2. Selection Sort（選擇排序）
3. Insertion Sort（插入排序）
4. Merge Sort（合併排序）
5. Quick Sort（快速排序）

除了實作排序功能之外，也有比較各種排序的時間與空間複雜度。

## 解題策略

1. 使用陣列存放資料
2. 每個排序法分別寫成函式
3. 使用同一組資料進行排序
4. 排序後輸出結果確認是否正確
5. 比較不同排序法的效率差異

## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

const int SIZE = 8;

void printArray(int arr[]) {

    for (int i = 0; i < SIZE; i++) {
        cout << arr[i] << " ";
    }

    cout << endl;
}


void bubbleSort(int arr[]) {

    for (int i = 0; i < SIZE - 1; i++) {

        for (int j = 0; j < SIZE - i - 1; j++) {

            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}


void selectionSort(int arr[]) {

    for (int i = 0; i < SIZE - 1; i++) {

        int minIndex = i;

        for (int j = i + 1; j < SIZE; j++) {

            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        swap(arr[i], arr[minIndex]);
    }
}


void insertionSort(int arr[]) {

    for (int i = 1; i < SIZE; i++) {

        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {

            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}


void merge(int arr[], int left, int mid, int right) {

    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[100], R[100];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }

    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {

        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }

        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right) {

    if (left < right) {

        int mid = (left + right) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}


int partition(int arr[], int low, int high) {

    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {

        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);

    return i + 1;
}

void quickSort(int arr[], int low, int high) {

    if (low < high) {

        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {

    int data1[SIZE] = {64, 34, 25, 12, 22, 11, 90, 5};
    int data2[SIZE] = {64, 34, 25, 12, 22, 11, 90, 5};
    int data3[SIZE] = {64, 34, 25, 12, 22, 11, 90, 5};
    int data4[SIZE] = {64, 34, 25, 12, 22, 11, 90, 5};
    int data5[SIZE] = {64, 34, 25, 12, 22, 11, 90, 5};

    cout << "Original Array: ";
    printArray(data1);

    bubbleSort(data1);
    cout << "Bubble Sort: ";
    printArray(data1);

    selectionSort(data2);
    cout << "Selection Sort: ";
    printArray(data2);

    insertionSort(data3);
    cout << "Insertion Sort: ";
    printArray(data3);

    mergeSort(data4, 0, SIZE - 1);
    cout << "Merge Sort: ";
    printArray(data4);

    quickSort(data5, 0, SIZE - 1);
    cout << "Quick Sort: ";
    printArray(data5);

    return 0;
}
```
## 效能分析

1.時間複雜度：

|      排序方法      |    最佳情況    |    平均情況    |    最差情況    |
| :------------: | :--------: | :--------: | :--------: |
|   Bubble Sort  |    O(n²)    |    O(n²)   |    O(n²)   |
| Selection Sort |    O(n²)   |    O(n²)   |    O(n²)   |
| Insertion Sort |    O(n)    |    O(n²)   |    O(n²)   |
|   Merge Sort   | O(n log n) | O(n log n) | O(n log n) |
|   Quick Sort   | O(n log n) | O(n log n) |    O(n²)   |

從表格可以看出Bubble Sort 跟 Selection Sort 在資料量變大時效率會比較差，而 Merge Sort 跟 Quick Sort 的效率比較好


2.空間複雜度：

|      排序方法      |   空間複雜度  |
| :------------: | :------: |
|   Bubble Sort  |   O(1)   |
| Selection Sort |   O(1)   |
| Insertion Sort |   O(1)   |
|   Merge Sort   |   O(n)   |
|   Quick Sort   | O(log n) |
  
Merge Sort 因為需要額外陣列，所以空間使用量會比較大

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

