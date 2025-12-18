template <class T>
class Chain 
{
  public:
    typedef ChainNode<T> Node;
    Node* head;
  Chain() 
  {
    head = new Node();
    head->link = head;
  }
   ~Chain() 
  {
    Clear();
    delete head;
  }
  void Clear() {
        Node* p = head->link;
        while (p != head) {
            Node* tmp = p;
            p = p->link;
            delete tmp;
        }
        head->link = head;
    }
    void InsertBack(const T& x) 
  {
        Node* p = head;
        while (p->link != head)
        p = p->link;
        p->link = new Node(x, head);
  }
};
