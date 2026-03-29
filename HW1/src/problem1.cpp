#include <iostream>
#include <vector>
#include <stdexcept>


template <class T>
class MinPQ {
public:
    virtual ~MinPQ() {}
    virtual bool IsEmpty() const = 0;
    virtual const T& Top() const = 0;
    virtual void Push(const T& x) = 0;
    virtual void Pop() = 0;
};


template <class T>
class MinHeap : public MinPQ<T> {
private:
    std::vector<T> heap;

public:
    bool IsEmpty() const override {
        return heap.empty();
    }

    const T& Top() const override {
        if (IsEmpty()) throw std::runtime_error("Heap is empty");
        return heap[0];
    }

    void Push(const T& x) override {
        heap.push_back(x); 
        int current = heap.size() - 1;
        
       
        while (current > 0) {
            int parent = (current - 1) / 2;
            if (heap[current] < heap[parent]) {
                std::swap(heap[current], heap[parent]);
                current = parent;
            } else break;
        }
    }

    void Pop() override {
        if (IsEmpty()) throw std::runtime_error("Heap is empty");
        
        heap[0] = heap.back(); 
        heap.pop_back();
        
        if (!heap.empty()) {
           
            int current = 0;
            int size = heap.size();
            while (true) {
                int left = 2 * current + 1;
                int right = 2 * current + 2;
                int smallest = current;

                if (left < size && heap[left] < heap[smallest]) smallest = left;
                if (right < size && heap[right] < heap[smallest]) smallest = right;

                if (smallest != current) {
                    std::swap(heap[current], heap[smallest]);
                    current = smallest;
                } else break;
            }
        }
    }
};
