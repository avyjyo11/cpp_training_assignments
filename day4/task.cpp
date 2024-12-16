#include <iostream>

template<typename T>
struct Node {
  T data;
  Node *next = nullptr;
};

template<typename T>
class LinkedList {
public:
  void insert(T data){
    Node<T> *node = new Node<T>;
    node->data = data;
    if (!m_head){
      m_head = node;
      m_tail = m_head;
    } else {
      m_tail->next = node;
      m_tail = m_tail->next;
    }
  }

  ~LinkedList(){
    Node<T> *temp = m_head;
    while(temp){
        Node<T> *t = temp->next;
        delete temp;
        temp = t;
    }
  }

  // fix: need to initialize the template type seperate for friend functions
  template<typename U>
  friend std::ostream& operator<<(std::ostream& os, const LinkedList<U>& ll);

private:
  Node<T> *m_head = nullptr;
  Node<T> *m_tail = nullptr;

};

template<typename T>
std::ostream& operator<<(std::ostream& os, const LinkedList<T>& ll){
  Node<T> *currNode = ll.m_head;
  while (currNode) {
    os << currNode->data << "\n";
    currNode = currNode->next;  
  }
  return os;
}


int main(){
  LinkedList<int> ll;
  ll.insert(1);
  ll.insert(2);
  ll.insert(3);
  ll.insert(4);

  std::cout<<ll;

  // ll.insert("hello");
  // ll.insert(34);
  // ll.insert(45.56);
  return 0;
}