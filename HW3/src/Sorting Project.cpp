#include <iostream>
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
