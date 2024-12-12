#include <iostream>

enum class VisitType {
  ROUTINE, 
  EMERGENCY,
  YEARLY
};

struct Diagnostic {
  std::string symptom;
  std::string treatment;
  std::string medicine;
};

struct MedicalReport {
  std::string date{};
  std::vector<Diagnostic> symptoms{};
  VisitType visitType{VisitType::ROUTINE};
};

class Patient: public Person {
  public:
    Patient(const int& id, const int& age, const std::string& name): Person(id, age, name) {
    }

  protected:
    std::vector<MedicalReport> m_medicalReports;

  private:


};

class Employee: public Person {
  public:
    Employee(int id, int age, const std::string& name): Person(id, age, name) {}

  protected:

};

class Person {
  public:
    Person(int id, int age, const std::string& name) {
      m_id = id;
      m_age = age;
      m_name = name;
    }

  protected:
    int m_id;
    int m_age;
    std::string m_name;
};

int main() {
  int id = 0;
  
  int age = 20;
  std::string name = "John";

  Patient patient1(id++, age, name);

  return 0;
}