#include <iostream>

class Distance {
   public:
      Distance() {}

      Distance(const int &f, const int &i): m_feet(f), m_inches(i) {}
      
      // overload function call
      Distance operator()(int f, int i, int c) {
         Distance D;
         D.m_feet = f + c;
         D.m_inches = i + c;
         return D;
      }
      
      void displayDistance() {
        std::cout << "F: " << m_feet << " I:" << m_inches << std::endl;
      }   

  private:
    int m_feet;           
    int m_inches;     
};

int main() {
    // Invoke the constructor
    Distance d1(11, 10), d2;
    d1.displayDistance();
    
    d2 = d1(10, 10, 10);
    d2.displayDistance();
    return 0;
}
