#include <iostream>
#include "headers/Var.h"

Var::Var(): m_type(int(VarType::UNKNOWN)) {}

Var::Var(const int a): m_intValue(a), m_type(int(VarType::INTEGER)) {}

Var::Var(const double a): m_doubleValue(a), m_type(int(VarType::DOUBLE)) {}

Var::Var(const bool a): m_boolValue(a), m_type(int(VarType::BOOLEAN)) {}

Var::Var(const char* str): m_type(int(VarType::STRING)) {
  m_strValue = std::shared_ptr<char[]>(new char[std::strlen(str) + 1]);
  std::strcpy(m_strValue.get(), str);
}

Var::~Var() {
  std::cout << "Detroying Var" << "\n";
  if (m_type == VarType::STRING) {
    // delete[] m_strValue;
  }
}

Var& Var::operator=(const Var& a) {
  m_type = a.m_type;
  if (a.m_type == VarType::INTEGER) {
    m_intValue = a.m_intValue;
  } else if (a.m_type == VarType::DOUBLE) {
    m_doubleValue = a.m_doubleValue;
  } else if (a.m_type == VarType::BOOLEAN) {
    m_boolValue = a.m_boolValue;
  } else if (a.m_type == VarType::STRING) {
    m_strValue = a.m_strValue;
  } else {
    std::cout << "Type mismatch when adding" << "\n";
  }
  return *this;
}

Var& Var::operator+(const int& a) {
  m_intValue += a;
  return *this;
}

Var& Var::operator+(const double& a) {
  m_doubleValue += a;
  return *this;
}

Var& Var::operator+(const char* a) {
  stringConcat(a);
  return *this;
}

Var& Var::operator+(Var& a) {
  if (a.m_type == VarType::INTEGER && m_type == VarType::INTEGER) {
    m_intValue += a.m_intValue;
  } else if (a.m_type == VarType::DOUBLE && m_type == VarType::DOUBLE) {
    m_doubleValue += a.m_doubleValue;
  } else if (a.m_type == VarType::STRING && m_type == VarType::STRING) {
    stringConcat(a.m_strValue.get());
  } else {
    std::cout << "Type mismatch when adding" << "\n";
  }
  return *this;
}

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

 void Var::display() {
  if (m_type == VarType::INTEGER) {
    std::cout << m_intValue << std::endl;
  } else if (m_type == VarType::DOUBLE) {
    std::cout << m_doubleValue << std::endl;
  } else {
    std::cout << m_strValue << std::endl;
  }
 }

int Var::getInt() {
  return m_intValue;
}

double Var::getDouble() {
  return m_doubleValue;
}

std::shared_ptr<char[]> Var::getString() {
  return m_strValue;
}

bool Var::getBool() {
  return m_boolValue;
}

void Var::stringConcat(const char* a) {
  int newLen = strlen(a) + strlen(m_strValue.get()) + 1;
  std::shared_ptr<char[]> temp(new char[newLen]);
  strcpy(temp.get(), m_strValue.get());
  strcat(temp.get(), a);
  m_strValue = temp;
}