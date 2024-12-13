// descrutor necessary for base abstract class

// rule of 3: copy contructor, operator= overloading, destructor always needed

#include <iostream>

enum VarType {
  INTEGER,
  STRING,
  DOUBLE
};

class Var { 
  public:
    Var() {}
    
    Var(const int a): m_type(int(VarType::INTEGER)) {
      m_intValue = a;
    }

    Var(const double a): m_type(int(VarType::DOUBLE)) {
      m_doubleValue = a;
    }

    Var(const char* str): m_type(int(VarType::STRING)) {
      m_strValue = new char(strlen(str) + 1);
      for (int i = 0; i< strlen(str); i++) {
        m_strValue[i] = str[i];
      }
    }

    Var& operator+(const int& a) {
      m_intValue += a;
      return *this;
    }

    Var& operator+(const double& a) {
      m_doubleValue += a;
      return *this;
    }

    Var& operator+(const char* a) {
      stringConcat(a);
      return *this;
    }

    Var& operator+(Var& a) {
      if (a.m_type == VarType::INTEGER && m_type == VarType::INTEGER) {
        m_intValue += a.m_intValue;
      } else if (a.m_type == VarType::DOUBLE && m_type == VarType::DOUBLE) {
        m_doubleValue += a.m_doubleValue;
      } else if (a.m_type == VarType::STRING && m_type == VarType::STRING) {
        stringConcat(a.m_strValue);
      } else {
        std::cout << "Type mismatch when adding" << std::endl;
      }
      return *this;
    }

    void display() {
      if (m_type == VarType::INTEGER) {
        std::cout << m_intValue << std::endl;
      } else if (m_type == VarType::DOUBLE) {
        std::cout << m_doubleValue << std::endl;
      } else {
        std::cout << m_strValue << std::endl;
      }
    }

    ~Var() {
      std::cout << "Detroying Var" << std::endl;
      if (m_type == VarType::STRING) {
        std::cout << "Detroying string" << std::endl;
        delete m_strValue;
      }
    }

  private:
    int m_intValue;
    double m_doubleValue; 
    char *m_strValue;
    uint8_t m_type;

    void stringConcat(const char* a) {
      int newLen = strlen(a) + strlen(m_strValue) + 1;
      char *temp = new char(newLen);
      strcpy(temp, m_strValue);
      delete m_strValue;
      strcat(temp, a);
      m_strValue = temp;
    }
};

int main() {
  Var a = "hello";
  Var b = "hello";
  Var c = 12.33;
  Var d = "world";
  a = a + d;
  a.display();

  return 0;
}
