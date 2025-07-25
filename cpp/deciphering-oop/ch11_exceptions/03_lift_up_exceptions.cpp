//
// Purpose: To illustrate passing exceptions to outer handlers.

#include <iomanip>
#include <iostream>

using std::cout; // preferred to: using namespace std;
using std::endl;
using std::set_terminate;
using std::setprecision;
using std::string;
using std::to_string;

constexpr int MAX = 5;

void AppSpecificTerminate() {
  cout << "Uncaught exception. Program terminating" << endl;
  exit(1);
}

class Person {
private:
  string firstName;
  string lastName;
  char middleInitial = '\0';
  string title;

protected:
  void ModifyTitle(const string &);

public:
  Person() = default;
  Person(const string &, const string &, char, const string &);
  Person(const Person &) = default; // copy constructor
  virtual ~Person() = default;      // virtual destructor

  // inline function definitions
  const string &GetFirstName() const { return firstName; }
  const string &GetLastName() const { return lastName; }
  const string &GetTitle() const { return title; }
  char GetMiddleInitial() const { return middleInitial; }

  virtual void Print() const;
  virtual void IsA() const;
  virtual void Greeting(const string &) const;
};

Person::Person(const string &fn, const string &ln, char mi, const string &t)
    : firstName(fn), lastName(ln), middleInitial(mi), title(t) {
  // dynamically allocate memory for any pointer data members here
}

void Person::ModifyTitle(const string &newTitle) {
  title = newTitle; // assignment between strings ensures a deep assignment
}

void Person::Print() const {
  cout << title << " " << firstName << " ";
  cout << middleInitial << ". " << lastName << endl;
}

void Person::IsA() const { cout << "Person" << endl; }

void Person::Greeting(const string &msg) const { cout << msg << endl; }

class Student : public Person {
private:
  float gpa = 0.0; // in-class initialization
  string currentCourse;
  const string studentId;
  static int numStudents; // static data member is initialized outside of class (see below)

public:
  Student(); // default constructor
  Student(
      const string &, const string &, char, const string &, float, const string &, const string &);
  Student(const Student &); // copy constructor
  ~Student() override;      // virtual destructor

  void EarnPhD();
  bool TakePrerequisites(); // new member function
  // inline function definitions
  float GetGpa() const { return gpa; }
  const string &GetCurrentCourse() const { return currentCourse; }
  const string &GetStudentId() const { return studentId; }
  void SetCurrentCourse(const string &); // prototype only

  virtual void Print() const override;
  virtual void IsA() const override;
  virtual void Validate(); // newly introduced virtual function in Student

  static int GetNumberStudents(); // static member function
};

// definition for static data member (which is implemented as external variable)
int Student::numStudents = 0; // notice initial value of 0

inline void Student::SetCurrentCourse(const string &c) { currentCourse = c; }

// Definition for static member function (it is also inline)
inline int Student::GetNumberStudents() { return numStudents; }

Student::Student() : studentId(to_string(numStudents + 100) + "Id") { numStudents++; }

Student::Student(const string &fn,
                 const string &ln,
                 char mi,
                 const string &t,
                 float avg,
                 const string &course,
                 const string &id)
    : Person(fn, ln, mi, t), gpa(avg), currentCourse(course), studentId(id) {
  numStudents++;
}

// Copy constructor definition
Student::Student(const Student &s)
    : Person(s), gpa(s.gpa), currentCourse(s.currentCourse), studentId(s.studentId) {
  // deep copy any pointer data members of derived class here
  numStudents++;
}

// destructor definition
Student::~Student() { numStudents--; }

void Student::EarnPhD() { ModifyTitle("Dr."); }

void Student::Print() const {
  cout << GetTitle() << " " << GetFirstName() << " ";
  cout << GetMiddleInitial() << ". " << GetLastName();
  cout << " with id: " << studentId << " GPA: ";
  cout << setprecision(3) << " " << gpa;
  cout << " Course: " << currentCourse << endl;
}

void Student::IsA() const { cout << "Student" << endl; }

void Student::Validate() { throw string("Student does not meet prerequisites"); }

bool Student::TakePrerequisites() {
  // Assume this function can correct the issue at hand
  // if not, it returns false
  return false;
}

int main() {
  set_terminate(AppSpecificTerminate); // register fn.

  Student s1("Alex", "Ren", 'Z', "Dr.", 3.9, "C++", "89CU");

  try // illustrates a nested try block
  {
    // Assume another important task occurred in this
    // scope, which may have also raised an exception
    try {
      s1.Validate(); // may raise an exception
    } catch (const string &err) {
      cout << err << endl;
      // try to correct (or partially handle) error.
      // If you cannot, pass exception to outer scope
      if (!s1.TakePrerequisites())
        throw;
    }
  } catch (const string &err) {
    cout << err << endl;
    // try to fix problem here…
    exit(1); // only if you can’t fix, exit gracefully
  }

  cout << "Moving onward with remainder of code." << endl;

  return 0;
}
