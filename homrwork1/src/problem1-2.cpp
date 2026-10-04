#include <iostream>
#include <string>

using namespace std;

void printSubsets(string set[], string currentSet[], int size, int index, int currentSize) {
    
    if (index == size) {
        cout << "{ ";
        
        for (int i = 0; i < currentSize; i++) {
            cout << currentSet[i] << " ";
        }
        
        cout << "}" << endl;
        return;
    }

    currentSet[currentSize] = set[index];
    printSubsets(set, currentSet, size, index + 1, currentSize + 1);

    printSubsets(set, currentSet, size, index + 1, currentSize);
}

void computePowerset(string set[], int size) {
    string currentSet[100];
    
    printSubsets(set, currentSet, size, 0, 0);
}

int main() {
    string set[] = {"a", "b", "c"};
    int size = 3;

    cout << "Powerset of {a, b, c} is:" << endl;

    computePowerset(set, size);

    return 0;
}
