#include <algorithm>
#include <iostream>
#include <ctime>

using namespace std;

// ====================== 基本工具 ======================

void copyArray(int from[], int to[], int n)
{
    for(int i = 0; i < n; i++)
        to[i] = from[i];
}

void worstData(int a[], int n)
{
    for(int i = 0; i < n; i++)
        a[i] = n - i;
}

// ====================== Insertion Sort ======================

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

// ====================== Quick Sort ======================

void medianOfThree(int a[], int low, int high)
{
    int mid = (low + high) / 2;

    if(a[low] > a[mid]) swap(a[low], a[mid]);
    if(a[low] > a[high]) swap(a[low], a[high]);
    if(a[mid] > a[high]) swap(a[mid], a[high]);

    swap(a[mid], a[high]);
}

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

void quickWrapper(int a[], int n)
{
    quickSort(a, 0, n - 1);
}

// ====================== Merge Sort (Bottom-up) ======================

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

// ====================== Heap Sort ======================

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
    for(int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    for(int i = n - 1; i > 0; i--)
    {
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}

// ====================== Composite Sort ======================

void compositeSort(int a[], int n)
{
    if(n <= 50)
        insertionSort(a, n);
    else
        quickWrapper(a, n);
}

// ====================== 計時 ======================

double measureTime(void (*func)(int*, int), int data[], int n)
{
    int* temp = new int[n];

    for(int i = 0; i < n; i++)
        temp[i] = data[i];

    clock_t start = clock();

    func(temp, n);

    clock_t end = clock();

    double ms = (double)(end - start) / CLOCKS_PER_SEC * 1000;

    delete[] temp;
    return ms;
}

// ====================== 主程式 ======================

int main()
{
    int sizes[6] = {500, 1000, 2000, 3000, 4000, 5000};

    cout << "n\tInsertion\tQuick\tMerge\tHeap\tComposite\n";

    for(int i = 0; i < 6; i++)
    {
        int n = sizes[i];
        int* data = new int[n];

        worstData(data, n);

        cout << n << "\t"
             << measureTime(insertionSort, data, n) << "\t"
             << measureTime(quickWrapper, data, n) << "\t"
             << measureTime(mergeSort, data, n) << "\t"
             << measureTime(heapSort, data, n) << "\t"
             << measureTime(compositeSort, data, n)
             << endl;

        delete[] data;
    }

    return 0;
}
