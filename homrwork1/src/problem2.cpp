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
