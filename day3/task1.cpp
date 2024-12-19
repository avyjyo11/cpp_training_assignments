// friend

#include <iostream>

enum VarType {
  UNKNOWN = -1,
  INTEGER = 0,
  STRING,
  DOUBLE,
  BOOLEAN
};

class Var { 
  public:
    Var(): m_type(int(VarType::UNKNOWN)) {}

    Var(const int a): m_intValue(a), m_type(int(VarType::INTEGER)) {}

    Var(const double a): m_doubleValue(a), m_type(int(VarType::DOUBLE)) {}

    Var(const bool a): m_boolValue(a), m_type(int(VarType::BOOLEAN)) {}

    Var(const char* str): m_type(int(VarType::STRING)) {
      m_strValue = new char[strlen(str) + 1];
      strcpy(m_strValue, str);
    }

    Var& operator=(const Var& a) {
      m_type = a.m_type;
      if (a.m_type == VarType::INTEGER) {
        m_intValue = a.m_intValue;
      } else if (a.m_type == VarType::DOUBLE) {
        m_doubleValue = a.m_doubleValue;
      } else if (a.m_type == VarType::BOOLEAN) {
        m_boolValue = a.m_boolValue;
      } else if (a.m_type == VarType::STRING) {
        delete[] m_strValue;
        m_strValue = new char[strlen(a.m_strValue)+1];
        strcpy(m_strValue,a.m_strValue);  
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

    void display() {
      if (m_type == VarType::INTEGER) {
        std::cout << m_intValue << std::endl;
      } else if (m_type == VarType::DOUBLE) {
        std::cout << m_doubleValue << std::endl;
      } else {
        std::cout << m_strValue << std::endl;
      }
    }

    int getInt() {
      return m_intValue;
    }

    double getDouble() {
      return m_doubleValue;
    }

    char* getString() {
      return m_strValue;
    }

    bool getBool() {
      return m_boolValue;
    }

    friend std::ostream& operator<<(std::ostream&, const Var&);

    ~Var() {
      std::cout << "Detroying Var" << "\n";
      if (m_type == VarType::STRING) {
        delete[] m_strValue;
      }
    }

  private:
    int m_intValue;
    double m_doubleValue; 
    bool m_boolValue;
    char *m_strValue;
    uint8_t m_type;

    void stringConcat(const char* a) {
      int newLen = strlen(a) + strlen(m_strValue) + 1;
      char *temp = new char[newLen];
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
  } else if (var.m_type == VarType::BOOLEAN) {
    std::string boolstr = "true";
    if (!var.m_boolValue) boolstr = "false";
    os << "var:" << boolstr;
  } else {
    os << "var:" << var.m_strValue;
  }
  return os;
}

int main() {
  Var a = "hello";
  Var b = "hello2";
  Var c = 12.33;
  Var d = "world";

  a = "hi";
  a.display();

  a = a + d;
  a.display();

  std::cout << c;
  return 0;
}
