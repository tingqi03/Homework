template <class T>
class ChainIterator {
public:
  ChainNode<T>* current;
  ChainIterator(ChainNode<T>* p = nullptr) : current(p) {}
  T& operator*() const { return current->data; }
  ChainIterator<T>& operator++() {
        current = current->link;
        return *this;
    }

    bool operator!=(const ChainIterator<T>& x) const {
        return current != x.current;
    }
};
