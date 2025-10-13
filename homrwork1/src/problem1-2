#include <iostream>
#include <stack>
using namespace std;

int ackermann_non_recursive(int m, int n) {
    stack<pair<int, int>> call_stack;

    while (true) {
        if (m == 0) {
            n = n + 1;
            if (call_stack.empty()) break;
            m = call_stack.top().first;
            n = call_stack.top().second;
            call_stack.pop();
        }
        else if (n == 0) {
            call_stack.push({m - 1, 1});
            m = m - 1;
            n = 1;
        }
        else {
            call_stack.push({m - 1, n - 1});
            m = m - 1;
            n = n - 1;
        }
    }

    return n;
}

int main() {
    int m, n;
    cout << "Enter values for m and n: ";
    cin >> m >> n;
    
    cout << "Ackermann(" << m << ", " << n << ") = " << ackermann_non_recursive(m, n) << endl;
    
    return 0;
}
