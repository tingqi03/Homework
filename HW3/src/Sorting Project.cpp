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

void printCost(long long compareCount, long long moveCount) {
    cout << "Compare Count: " << compareCount << endl;
    cout << "Move/Swap Count: " << moveCount << endl;
    cout << endl;
}

void bubbleSort(int arr[], long long& compareCount, long long& moveCount) {
    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = 0; j < SIZE - i - 1; j++) {
            compareCount++;

            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                moveCount++;
            }
        }
    }
}

void selectionSort(int arr[], long long& compareCount, long long& moveCount) {
    for (int i = 0; i < SIZE - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < SIZE; j++) {
            compareCount++;

            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
            moveCount++;
        }
    }
}

void insertionSort(int arr[], long long& compareCount, long long& moveCount) {
    for (int i = 1; i < SIZE; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0) {
            compareCount++;

            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                moveCount++;
                j--;
            }
            else {
                break;
            }
        }

        arr[j + 1] = key;
        moveCount++;
    }
}

void merge(int arr[], int left, int mid, int right,
    long long& compareCount, long long& moveCount) {

    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[100], R[100];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
        moveCount++;
    }

    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
        moveCount++;
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        compareCount++;

        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }

        moveCount++;
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        moveCount++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        moveCount++;
    }
}

void mergeSort(int arr[], int left, int right,
    long long& compareCount, long long& moveCount) {

    if (left < right) {
        int mid = (left + right) / 2;

        mergeSort(arr, left, mid, compareCount, moveCount);
        mergeSort(arr, mid + 1, right, compareCount, moveCount);

        merge(arr, left, mid, right, compareCount, moveCount);
    }
}

int partition(int arr[], int low, int high,
    long long& compareCount, long long& moveCount) {

    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        compareCount++;

        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
            moveCount++;
        }
    }

    swap(arr[i + 1], arr[high]);
    moveCount++;

    return i + 1;
}

void quickSort(int arr[], int low, int high,
    long long& compareCount, long long& moveCount) {

    if (low < high) {
        int pi = partition(arr, low, high, compareCount, moveCount);

        quickSort(arr, low, pi - 1, compareCount, moveCount);
        quickSort(arr, pi + 1, high, compareCount, moveCount);
    }
}

int main() {
    int data1[SIZE] = { 64, 34, 25, 12, 22, 11, 90, 5 };
    int data2[SIZE] = { 64, 34, 25, 12, 22, 11, 90, 5 };
    int data3[SIZE] = { 64, 34, 25, 12, 22, 11, 90, 5 };
    int data4[SIZE] = { 64, 34, 25, 12, 22, 11, 90, 5 };
    int data5[SIZE] = { 64, 34, 25, 12, 22, 11, 90, 5 };

    long long compareCount = 0;
    long long moveCount = 0;

    cout << "Original Array: ";
    printArray(data1);
    cout << endl;

    compareCount = 0;
    moveCount = 0;
    bubbleSort(data1, compareCount, moveCount);
    cout << "Bubble Sort: ";
    printArray(data1);
    printCost(compareCount, moveCount);

    compareCount = 0;
    moveCount = 0;
    selectionSort(data2, compareCount, moveCount);
    cout << "Selection Sort: ";
    printArray(data2);
    printCost(compareCount, moveCount);

    compareCount = 0;
    moveCount = 0;
    insertionSort(data3, compareCount, moveCount);
    cout << "Insertion Sort: ";
    printArray(data3);
    printCost(compareCount, moveCount);

    compareCount = 0;
    moveCount = 0;
    mergeSort(data4, 0, SIZE - 1, compareCount, moveCount);
    cout << "Merge Sort: ";
    printArray(data4);
    printCost(compareCount, moveCount);

    compareCount = 0;
    moveCount = 0;
    quickSort(data5, 0, SIZE - 1, compareCount, moveCount);
    cout << "Quick Sort: ";
    printArray(data5);
    printCost(compareCount, moveCount);

    return 0;
}
