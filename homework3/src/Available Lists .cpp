template <class T>
class ChainNode {
public:
    T data;
    ChainNode<T>* link;
    static ChainNode<T>* available;

    ChainNode(const T& d = T(), ChainNode<T>* l = nullptr)
        : data(d), link(l) {}

    void* operator new(size_t size) {
        if (available == nullptr)
            return ::operator new(size);
        ChainNode<T>* p = available;
        available = available->link;
        return p;
    }

    void operator delete(void* ptr) {
        ChainNode<T>* p = (ChainNode<T>*)ptr;
        p->link = available;
        available = p;
    }
};

template <class T>
ChainNode<T>* ChainNode<T>::available = nullptr;
