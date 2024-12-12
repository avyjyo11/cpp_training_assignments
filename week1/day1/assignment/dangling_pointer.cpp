#include <iostream>

//A dangling pointer in C/C++ is a pointer that points to a memory location that has been freed, deallocated, or gone out of scope

// 3 main ways a dangling pointer
int* getLocalPointer() {
    int x = 42; // Local variable
    return &x;  // Returning address of local variable (bad practice)
}

int* getLocalPointerSolution() {
    int *x = new int(42); // Allocate on the heap
    return x;  // Returning pointer variable
}


int main() {
  // 1. Deallocation of Memory (Using delete or free)
  int *ptr1 = new int(42); // Dynamically allocate memory
  std::cout << "Value of *ptr: " << *ptr1 << std::endl;
  delete ptr1; // Deallocate memory
  std::cout << "Accessing dangling pointer 1: " << *ptr1 << std::endl; // Undefined behavior
  // ptr is now a dangling pointer (it still holds the old address)
  
  // 2. Pointer to Local Variables (Out-of-scope pointers)
  int *ptr2 = getLocalPointer(); 
  // x is out of scope, ptr points to a non-existent memory location
  std::cout << "Accessing dangling pointer 2: " << *ptr2 << std::endl; // Undefined behavior

  // 3. Accessing Variable Out of Scope
  int *ptr3;
  // block scope
  {
      int var = 210;
      ptr3 = &var;
  }
  std::cout << "Accessing dangling pointer 3: " << *ptr3 << std::endl; // Undefined behavior

  // Solutions
  // 1. Assign NULL or nullptr to the Pointers that are Not in Use
  ptr1 = nullptr; // Solution to avoid dangling pointer

  // 2. Use Dynamic Memory Allocation for the Local Variables that are to be returned.
  ptr2 = getLocalPointerSolution();
  delete ptr2;
  ptr2 = NULL;

  // 3. Using Smart Pointers
  std::unique_ptr<int> uptr = std::make_unique<int>(42);
  std::shared_ptr<int> sptr = std::make_shared<int>(42);
  // Smart pointer automatically handles memory deallocation

  return 0;
} 