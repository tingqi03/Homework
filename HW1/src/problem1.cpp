#include <iostream>
using namespace std;

template <class T>
class MinPQ {
public:
    virtual ~MinPQ() {}
    virtual bool IsEmpty() const = 0;
    virtual const T& Top() const = 0;
    virtual void Push(const T&) = 0;
    virtual void Pop() = 0;
};

template <class T>
class MinHeap : public MinPQ<T> {
private:
    T* heap;
    int capacity;
    int size;

    void Resize() {
        capacity *= 2;
        T* newHeap = new T[capacity];
        for (int i = 1; i <= size; i++)
            newHeap[i] = heap[i];
        delete[] heap;
        heap = newHeap;
    }

public:
    MinHeap(int cap = 100) {
        capacity = cap;
        size = 0;
        heap = new T[capacity];
    }

    ~MinHeap() {
        delete[] heap;
    }

    bool IsEmpty() const override {
        return size == 0;
    }

    const T& Top() const override {
        return heap[1];
    }

    void Push(const T& x) override {
        if (size + 1 == capacity)
            Resize();

        int i = ++size;

        while (i != 1 && x < heap[i / 2]) {
            heap[i] = heap[i / 2];
            i /= 2;
        }
        heap[i] = x;
    }

    void Pop() override {
        if (IsEmpty()) return;

        T last = heap[size--];
        int i = 1, child = 2;

        while (child <= size) {
            if (child < size && heap[child] > heap[child + 1])
                child++;

            if (last <= heap[child]) break;

            heap[i] = heap[child];
            i = child;
            child *= 2;
        }

        heap[i] = last;
    }
};
