#include <iostream>
#include <algorithm>
#include <random>
#include <cmath>
#include <vector>

struct Node {
    int key;
    Node *left, *right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

class BST {
public:
    Node* root = nullptr;

    void insert(int key) {
        root = insertRecursive(root, key);
    }

    int getHeight(Node* node) {
        if (!node) return 0;
        return 1 + std::max(getHeight(node->left), getHeight(node->right));
    }

   
    void remove(int k) {
        root = deleteNode(root, k);
    }

private:
    Node* insertRecursive(Node* node, int key) {
        if (!node) return new Node(key);
        if (key < node->key) node->left = insertRecursive(node->left, key);
        else if (key > node->key) node->right = insertRecursive(node->right, key);
        return node;
    }

    Node* findMin(Node* node) {
        while (node && node->left) node = node->left;
        return node;
    }

    Node* deleteNode(Node* node, int k) {
        if (!node) return nullptr;
        if (k < node->key) node->left = deleteNode(node->left, k);
        else if (k > node->key) node->right = deleteNode(node->right, k);
        else {
           if (!node->left) {
                Node* temp = node->right; delete node; return temp;
            } else if (!node->right) {
                Node* temp = node->left; delete node; return temp;
            }
          
            Node* temp = findMin(node->right);
            node->key = temp->key;
            node->right = deleteNode(node->right, temp->key);
        }
        return node;
    }
};


int main() {
    std::vector<int> n_values = {100, 500, 1000, 2000, 3000, 5000, 10000};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);

    std::cout << "n\tHeight\tlog2(n)\tRatio (H/log2n)\n";
    for (int n : n_values) {
        BST tree;
        for (int i = 0; i < n; ++i) tree.insert(dis(gen));
        
        int h = tree.getHeight(tree.root);
        double log2n = std::log2(n);
        std::cout << n << "\t" << h << "\t" << (int)log2n << "\t" << h/log2n << "\n";
    }
    return 0;
}
