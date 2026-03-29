#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;

    Node* Insert(Node* node, int key) {
        if (!node) return new Node(key);

        if (key < node->key)
            node->left = Insert(node->left, key);
        else
            node->right = Insert(node->right, key);

        return node;
    }

    int Height(Node* node) {
        if (!node) return 0;
        return 1 + max(Height(node->left), Height(node->right));
    }

    Node* Delete(Node* node, int key) {
        if (!node) return nullptr;

        if (key < node->key)
            node->left = Delete(node->left, key);
        else if (key > node->key)
            node->right = Delete(node->right, key);
        else {
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            }
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* succ = node->right;
            while (succ->left)
                succ = succ->left;

            node->key = succ->key;
            node->right = Delete(node->right, succ->key);
        }

        return node;
    }

public:
    BST() { root = nullptr; }

    void Insert(int key) { root = Insert(root, key); }

    int GetHeight() { return Height(root); }

    void DeleteKey(int key) { root = Delete(root, key); }
};

int main() {
    srand(time(0));
    int test[] = {100, 500, 1000, 2000};

    for (int n : test) {
        BST tree;

        for (int i = 0; i < n; i++)
            tree.Insert(rand());

        int h = tree.GetHeight();
        double ratio = h / log2(n);

        cout << "n=" << n
             << " height=" << h
             << " ratio=" << ratio << endl;
    }

    return 0;
}
