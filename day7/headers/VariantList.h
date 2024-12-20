#ifndef VARIANTLIST_H
#define VARIANTLIST_H

#include "Var.h"

struct Node {
  Var data;
  std::shared_ptr<Node> next;
};

class VariantList {
public:
  ~VariantList();

  void insert(Var data);
  void add(int index, Var data);

  friend std::ostream& operator<<(std::ostream& os, const VariantList& ll);

private:
  std::shared_ptr<Node> m_head;
  std::shared_ptr<Node> m_tail;
};

#endif
