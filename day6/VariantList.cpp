#include <iostream>

#include "headers/VariantList.h"

VariantList::~VariantList(){
  std::cout << "Detroying VariantList" << "\n";
  m_head.reset();
}

void VariantList::insert(Var data){
  std::shared_ptr<Node> node(new Node);
  node->data = data;
  if (!m_head){
    m_head = node;
    m_tail = m_head;
  } else {
    m_tail->next = node;
    m_tail = m_tail->next;
  }
}

void VariantList::add(int index, Var data) {
  std::shared_ptr<Node> temp = m_head;
  int _index = 0;
  while(_index < index) {
    temp = temp->next;
    _index++;
  }
  temp->data = temp->data + data;
}

std::ostream& operator<<(std::ostream& os, const VariantList& ll){
  std::shared_ptr<Node> currNode = ll.m_head;
  while (currNode) {
    os << currNode->data << "\n";
    currNode = currNode->next;  
  }
  return os;
}