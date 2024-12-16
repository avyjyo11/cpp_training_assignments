// friend

#include <iostream>

enum VarType {
  INTEGER,
  STRING,
  DOUBLE,
  ARRAY
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
      std::cout << "str" << str << "\n";
      m_strValue = new char(strlen(str) + 1);
      for (int i = 0; i< strlen(str); i++) {
        m_strValue[i] = str[i];
      }
    }

    Var& operator=(const Var& a) {
      m_type = a.m_type;
      if (a.m_type == VarType::INTEGER) {
        m_intValue = a.m_intValue;
      } else if (a.m_type == VarType::DOUBLE) {
        m_doubleValue = a.m_doubleValue;
      } else if (a.m_type == VarType::STRING) {
        delete[] m_strValue;
        m_strValue = nullptr;
        stringConcat(a.m_strValue);
      } else {
        std::cout << "Type mismatch when adding" << "\n";
      }
      return *this;
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
        std::cout << "Type mismatch when adding" << "\n";
      }
      return *this;
    }

    Var& operator>(Var& a) {
       if (a.m_type == VarType::DOUBLE && m_type == VarType::DOUBLE) {
        m_doubleValue += a.m_doubleValue;
      } else if (a.m_type == VarType::STRING && m_type == VarType::STRING) {
        stringConcat(a.m_strValue);
      } else {
        std::cout << "Type mismatch when adding" << "\n";
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

    friend std::ostream& operator<<(std::ostream&, const Var&);

    ~Var() {
      // std::cout << "Detroying Var" << "\n";
      if (m_type == VarType::STRING) {
        // std::cout << "Detroying string" << "\n";
        delete[] m_strValue;
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

std::ostream& operator<<(std::ostream& os, const Var& var) {
  if (var.m_type == VarType::INTEGER) {
    os << "var:" << var.m_intValue;
  } else if (var.m_type == VarType::DOUBLE) {
    os << "var:" << var.m_doubleValue;
  } else {
    os << "var:" << var.m_strValue;
  }
  return os;
}

int main() {
  // Var a = "hello";
  // // Var b = "hello";
  // // Var c = 12.33;
  // Var d = "world";

  // a = "hi";
  // a.display();

  // a = a + d;
  // a.display();

  // std::cout << a << "\n";
  const char *c = "leapfrog";

  std::cout << c;

  delete c;

  return 0;
}
