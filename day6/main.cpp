#include <iostream>
#include "headers/VariantList.h"

int main(){
  VariantList ll;

  ll.insert(1);
  ll.insert(2.1);
  ll.insert("hello");
  ll.insert(true);

  ll.add(2, "world");

  std::cout << ll;
  return 0;
}