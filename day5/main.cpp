#include <iostream>

template<typename T>
class SharedPointer {
public:
  explicit SharedPointer(T* a = nullptr): ptr(a), count(nullptr) {
    if (ptr) {
      count = new std::atomic<int>(1);
    }
  }

  SharedPointer(const SharedPointer& other): ptr(other.ptr), count(other.count) {
    if (count) {
      ++(*count);
    }
  }

  SharedPointer& operator=(const SharedPointer& other) {
    if (this == &other) return *this;

    release();
    ptr = other.ptr;
    count = other.count;

    if (count) {
      ++(*count);
    }
    return *this;
  }

  bool unique() {
    if(count && *count == 1) {
      return true;
    }
    return false;
  }

  void swap(SharedPointer& other) {
    if (this == &other) return;

    T* tempPtr = ptr;
    ptr = other.ptr;
    other.ptr = tempPtr;

    std::atomic<int>* tempCount = count;
    count = other.count;
    other.count = tempCount;
  }

  void showCount() {
    std::cout << "counter: "  << *count << "\n";
  }

  const T* get() {
    return ptr;
  }

  ~SharedPointer(){
    std::cout << "Destructor called: " << *count << "\n";
    release();
  }

private:
  T* ptr;
  std::atomic<int>* count;

  void release() {
    if (count && --(*count) == 0) {
      delete ptr;
      delete count;
    }
    ptr = nullptr;
    count = nullptr;
  }
};

int main() {
  SharedPointer<int> sp1(new int(10));
  sp1.showCount();

  SharedPointer<int> sp2 = sp1;
  sp2.showCount();
  sp1.showCount();

  SharedPointer<int> sp3;
  sp3 = sp1;
  sp3.showCount();
  sp2.showCount();
  sp1.showCount();

  SharedPointer<int> sp4(new int(20));
  sp4.swap(sp1);

  std::cout << "Before swap:" << "\n";
  std::cout << "sp4 points to: " << *sp4.get() << ", sp1 points to: " << *sp1.get() << "\n";
  return 0;
}
