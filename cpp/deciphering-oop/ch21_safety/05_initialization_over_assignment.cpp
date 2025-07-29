//
// Purpose: To illustrate preferring initialization over assignment
// Notice use of in-class initialization and member initialization lists.

// Here, we've generalized the attributes and behaviors relevant to a Person
// out of Student into the following class definition.

#include <iomanip>
#include <iostream>

using std::cout; // preferred to: using namespace std;
using std::endl;
using std::setprecision;
using std::string;
using std::to_string;

class Person {
private:
  // data members
  string firstName;

  string lastName;
  char middleInitial = '\0';
  string title;

protected:
  void ModifyTitle(const string &); // Make this operation available to derived classes

public:
  Person() = default;                                           // default constructor
  Person(const string &, const string &, char, const string &); // alternate constructor
  // We get the default copy constructor and destructor, even without the =default prototypes.
  // Hence, these are commented out Person(const Person &) = default;  // use default copy
  // constructor ~Person() = default;  // default destructor; note: = default prototype is optional
  // (we'd get default dest w/o any prototype)

  // inline function definitions
  const string &GetFirstName() const { return firstName; } // firstName returned as const string
  const string &GetLastName() const { return lastName; }   // so is lastName (via implicit cast)
  const string &GetTitle() const { return title; }
  char GetMiddleInitial() const { return middleInitial; }
};

// With in-class initialization, writing the default constructor yourself is no longer
// necessary Here's how it would look if you did choose to provide one
// (and also chose not to use in-class initialization)
/* Person::Person() : middleInitial('\0') { } */

Person::Person(const string &fn, const string &ln, char mi, const string &t)
    : firstName(fn), lastName(ln), middleInitial(mi), title(t) {}

// We are using default copy constructor, but if you needed to write it yourself, here is what it
// would look like: Remember to prototype it too!
/* Person::Person(const Person &p):
 * firstName(p.firstName), lastName(p.lastName), middleInitial(p.middleInitial), title(p.title)
{ } */

// We don't need to write the destructor ourselves since we have no heap memory
// to release, but this is what it would look like
/* Person::~Person() { } */

void Person::ModifyTitle(const string &newTitle) {
  title = newTitle; // assignment between strings ensures a deep assignment
}

// Student is derived from Person using public inheritance. (Notice the public access
// label after the : in the class definition). Private inheritance is the default for
// classes (public is the default for inherited structures).

class Student : public Person {
private:
  float gpa = 0.0;
  string currentCourse;
  const string studentId; // studentId is not modifiable
  static int numStudents; // static data member is initialized outside of class (see below)

public:
  // member function prototypes
  Student(); // default constructor
  Student(const string &,
          const string &,
          char,
          const string &,
          float,
          const string &,
          const string &);  // alt. constructor
  Student(const Student &); // copy constructor
  ~Student();               // destructor

  void Print() const;
  void EarnPhD(); // public interface to inherited protected member
  float GetGpa() const { return gpa; }
  const string &GetCurrentCourse() const { return currentCourse; }
  const string &GetStudentId() const { return studentId; }
  void SetCurrentCourse(const string &);
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
// Notice that the member initialization list is used to specify
// that the Person copy constructor should be utilized to copy the
// Person sub-object.  Without this secification, the default constructor
// for Person would be invoked (which would be incorrect since part of
// the copied Student object would be Nulled out).  Notice that
// the input parameter s is implicitly cast to a Person &
Student::Student(const Student &s)
    : Person(s), gpa(s.gpa), currentCourse(s.currentCourse), studentId(s.studentId) {
  // deep copy any pointer data members of derived class here
  numStudents++;
}

// destructor definition
Student::~Student() {
  // release memory for any dynamically allocated data members
  numStudents--;
}

void Student::Print() const {
  // Private members of Person are not directly accessible within
  // the scope of Student, hence access functions are utilized
  // to print these members
  cout << GetTitle() << " " << GetFirstName() << " ";
  cout << GetMiddleInitial() << ". " << GetLastName();
  cout << " with id: " << studentId << " gpa: ";
  cout << setprecision(3) << gpa;
  cout << " course: " << currentCourse << endl;
}

void Student::EarnPhD() {
  // Protected members defined by the base class are accessible within
  // the scope of the derived class.  EarnPhd() provides a public
  // interface to this functionality for derived class instances.
  ModifyTitle("Dr.");
}

int main() {
  Student s1("Jo", "Li", 'U', "Ms.", 3.9, "C++", "178PSU");

  s1.Print();

  s1.SetCurrentCourse("Doctoral Thesis");
  s1.EarnPhD();

  s1.Print();
  cout << "Total number of students: " << Student::GetNumberStudents() << endl;

  return 0;
}
