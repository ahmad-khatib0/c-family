// Purpose: To illustrate single inheritance, how the member initialization list
// is used to specify which base class constructor should be implicitly invoked,
// and the significance of the protected access region.

// Here, we've generalized the attributes and behaviors relevant
// to a Person out of Student into the following class definition.

#include <iomanip>
#include <iostream>

using std::cout;
using std::endl;
using std::setprecision;
using std::string;
using std::to_string;

class Person {
private:
  // data members
  string firstName;
  string lastName;
  char middleInitial = '\0'; // in-class initialization -- value to be used in default constructor
  string title;              // Mr., Ms., Mrs., Miss, Dr., etc.

protected:
  void ModifyTitle(const string &); // Make this operation available to derived classes

public:
  // Person() = default;
  Person();
  Person(const string &, const string &, char, const string &);
  // We get the default copy constructor and destructor, even without the = default
  // prototypes. Hence, these are commented out Person(const Person &) = default;
  // use default copy constructor
  // ~Person() = default;
  ~Person();
  // default destructor; note: = default prototype is optional
  // (we'd get default dest w/o any prototype)

  // inline function definitions
  const string &GetFirstName() const { return firstName; }
  const string &GetLastName() const { return lastName; }
  const string &GetTitle() const { return title; }
  char GetMiddleInitial() const { return middleInitial; }
};

// With in-class initialization, writing the default constructor yourself is no
// longer necessary Here's how it would look if you did choose to provide one
// (and also chose not to use in-class initialization)

Person::Person() { cout << "Person (parent class) initialized \n"; }

Person::Person(const string &fn, const string &ln, char mi, const string &t)
    : firstName(fn), lastName(ln), middleInitial(mi), title(t) {
  cout << "Person (parent class) initialized \n";
}

// We are using default copy constructor, but if you needed to write it yourself,
// here is what it would look like: Remember to prototype it too!
/*
Person::Person(const Person &p) :
               firstName(p.firstName), lastName(p.lastName),
               middleInitial(p.middleInitial), title(p.title)
{
   // deep copy any pointer data members here
}
*/

// We don't need to write the destructor ourselves since we have no heap memory
// to release, but this is what it would look like

Person::~Person() { cout << "Person (parent class) dealocated \n"; }

void Person::ModifyTitle(const string &newTitle) {
  title = newTitle; // assignment between strings ensures a deep assignment
}

// Private inheritance is the default for classes
// (public is the default for inherited structures).
class Student : public Person {
private:
  float gpa = 0.0;
  string currentCourse;
  const string studentId;
  static int numStudents;

public:
  Student();
  Student(const string &, const string &, char, const string &, float, const string &,
          const string &);
  Student(const Student &); // copy constructor
  ~Student();
  void Print() const;

  void EarnPhD(); // public interface to inherited protected member

  // inline function definitions
  float GetGpa() const { return gpa; }
  const string &GetCurrentCourse() const { return currentCourse; }
  const string &GetStudentId() const { return studentId; }
  void SetCurrentCourse(const string &);

  static int GetNumberStudents(); // static member function
};

int Student::numStudents = 0;

inline void Student::SetCurrentCourse(const string &c) { currentCourse = c; }

inline int Student::GetNumberStudents() { return numStudents; }

Student::Student() : studentId(to_string(numStudents + 100) + "Id") {
  // Note: since studentId is const, we need to set it at construction.
  numStudents++;
}

Student::Student(const string &fn, const string &ln, char mi, const string &t, float avg,
                 const string &course, const string &id)
    : Person(fn, ln, mi, t), gpa(avg), currentCourse(course), studentId(id) {
  cout << "Student (child class) initialized \n";
  numStudents++;
}

// Copy constructor definition
// Notice that the selected constructor will match the signature
// Person::Person(const string &, const string &, char, const string &), and that
// selected input parameters from the Student constructor (namely fn, ln, mi, and t)
// will be passed as parameters to the Person alternate constructor. The Student
// constructor’s member initialization list is then used to initialize additional
// data members introduced by the Student class.
Student::Student(const Student &s)
    : Person(s), gpa(s.gpa), currentCourse(s.currentCourse), studentId(s.studentId) {
  // deep copy any pointer data members of derived class here
  numStudents++;
}

Student::~Student() {
  cout << "Student (child class) dealocated \n";
  numStudents--;
}

void Student::Print() const {
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

  // Person (parent class) initialized
  // Student (child class) initialized
  // Ms. Jo U. Li with id: 178PSU gpa: 3.9 course: C++
  // Dr. Jo U. Li with id: 178PSU gpa: 3.9 course: Doctoral Thesis
  // Total number of students: 1
  // Student (child class) dealocated
  // Person (parent class) dealocated

  return 0;
}
