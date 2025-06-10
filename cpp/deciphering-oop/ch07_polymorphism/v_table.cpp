

#include <iostream>
#include <string>
using std::string;

class Person {
private:
  string name;

protected:
public:
  Person();
  Person(const string &);
  // 4 virt fns introduced in Person class
  virtual ~Person();
  virtual void Print() const;
  virtual void IsA() const;
  virtual void Greeting(const string &) const;
};

Person::Person(const string &n) : name(n) {}
void Person::Print() const { std::cout << name << "\n"; }

class Student : public Person {
private:
  string name;

public:
  Student(const string &);
  ~Student() override; // 3 virt fns are overridden
  void Print() const override;
  void IsA() const override;
};

Student::Student(const string &n) : name(n) {}
void Student::Print() const { std::cout << name << "\n"; }

constexpr int MAX = 3;
int main() {
  Person *people[MAX] = {}; // init. with nullptrs
  people[0] = new Person("Joy");
  people[1] = new Student("Renee");
  people[2] = new Student("Gabby");
  for (int i = 0; i < MAX; i++) {
    // at compile time, modified to:
    people[i]->Print(); // *(people[i]->vptr[1])()
    delete people[i];
  }
  return 0;
}
