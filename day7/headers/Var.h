#ifndef VAR_H
#define VAR_H

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
  Var();

  Var(const int a);
  Var(const double a);
  Var(const bool a);
  Var(const char* str);

  ~Var();

  Var& operator=(const Var& a);

  Var& operator+(const int& a);
  Var& operator+(const double& a);
  Var& operator+(const char* a);
  Var& operator+(Var& a);

  void display();

  int getInt();
  bool getBool();
  double getDouble();
  std::shared_ptr<char[]> getString();
  
  friend std::ostream& operator<<(std::ostream&, const Var&);

private:
  int m_intValue;
  bool m_boolValue;
  double m_doubleValue; 
  std::shared_ptr<char[]> m_strValue;
  
  uint8_t m_type;
  void stringConcat(const char* a);
};

#endif