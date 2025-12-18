template <class T>
class ChainNode {
public:
    T data;
    ChainNode<T>* link;

    ChainNode(const T& d = T(), ChainNode<T>* l = nullptr)
        : data(d), link(l) {}
};
