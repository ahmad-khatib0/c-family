#include <string>

using std::string;

class Person {
public:
  virtual void Print() const;
};

class Student : public Person {
public:
  // Override the base class method so that this
  // interface is not hidden by overloaded fn. below
  void Print() const override;
  // add the additional interface (which is overloaded)
  // Note: this additional Print() is virtual
  // from this point forward in the hierarchy
  virtual void Print(const string &) const;
};

int main() {
  Student s1{};
  s1.Print();              // this version is no longer hidden.
  s1.Print("I got an A!"); // also works
  s1.Person::Print();      // this is no longer necessary
}
