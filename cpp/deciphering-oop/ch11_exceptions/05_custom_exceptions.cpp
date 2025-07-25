//
// Purpose: To illustrate a user defined exception class derived from exception

#include <iomanip>
#include <iostream>

using std::cout;
using std::endl;
using std::exception;
using std::set_terminate;
using std::setprecision;
using std::string;
using std::to_string;

constexpr int MAX = 5;

void AppSpecificTerminate() {
  cout << "Uncaught exception. Program terminating" << endl;
  exit(1);
}

class StudentException : public exception {
private:
  // (will be over written with bonified value after successful alt constructor)
  int errCode = 0;
  string details;

public:
  StudentException(const string &det, int num) : errCode(num), details(det) {}
  // Base class destructor (exception) is virtual. Override at this level if
  // you have work to do. We can omit the default destructor prototype
  // ~StudentException() override = default;
  const char *what() const noexcept override
  // note: what() returns a const char * (we must override with the same signature)
  {
    return "Student Exception";
  }

  int GetCode() const { return errCode; }
  const string &GetDetails() const { return details; }
};

class Person {
private:
  string firstName;
  string lastName;
  char middleInitial = '\0';
  string title;

protected:
  void ModifyTitle(const string &);

public:
  Person() = default; // default constructor
  Person(const string &, const string &, char, const string &);
  virtual ~Person() = default; // virtual destructor

  const string &GetFirstName() const { return firstName; }
  const string &GetLastName() const { return lastName; }
  const string &GetTitle() const { return title; }
  char GetMiddleInitial() const { return middleInitial; }

  virtual void Print() const;
  virtual void IsA() const;
  virtual void Greeting(const string &) const;
};

Person::Person(const string &fn, const string &ln, char mi, const string &t)
    : firstName(fn), lastName(ln), middleInitial(mi), title(t) {}

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
  ~Student() override;      // destructor
  void EarnPhD();
  bool TakePrerequisites();

  float GetGpa() const { return gpa; }
  const string &GetCurrentCourse() const { return currentCourse; }
  const string &GetStudentId() const { return studentId; }
  void SetCurrentCourse(const string &); // prototype only

  void Print() const override;
  void IsA() const override;
  virtual void Validate(); // newly introduced virtual functions in Student
  virtual void Graduate();

  static int GetNumberStudents(); // static member function
};

int Student::numStudents = 0; // notice initial value of 0

inline void Student::SetCurrentCourse(const string &c) { currentCourse = c; }

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

Student::Student(const Student &s)
    : Person(s), gpa(s.gpa), currentCourse(s.currentCourse), studentId(s.studentId) {
  numStudents++;
}

Student::~Student() { numStudents--; }

void Student::EarnPhD() { ModifyTitle("Dr."); }

void Student::Print() const { // need to use access functions as these data members are
  // defined in Person as private
  cout << GetTitle() << " " << GetFirstName() << " ";
  cout << GetMiddleInitial() << ". " << GetLastName();
  cout << " with id: " << studentId << " GPA: ";
  cout << setprecision(3) << " " << gpa;
  cout << " Course: " << currentCourse << endl;
}

void Student::IsA() const { cout << "Student" << endl; }

void Student::Validate() {
  // check Student instance to see if standards are met; if not, throw an exception
  throw string("Student does not meet prerequisites");
}

bool Student::TakePrerequisites() {
  // Assume this function can correct the issue at hand if not, it returns false
  return false;
}

void Student::Graduate() {
  // if something goes wrong, instantiate a StudentException,
  // pack it with relevant data during construction, and then
  // throw the StudentException (it will be caught as a referenceable object)
  throw StudentException("Missing Credits", 4);
}

int main() {
  set_terminate(AppSpecificTerminate); // register fn.

  Student s1("Alexandra", "Doone", 'G', "Miss", 3.95, "C++", "231GWU");

  try {
    s1.Graduate();
  } catch (const StudentException &e) // catch the exception by ref
  {
    cout << e.what() << endl;
    cout << e.GetCode() << " " << e.GetDetails() << endl;
    // Grab useful info from e and try to fix the problem
    // if we can fix the problem, and continue the application
    exit(1); // only exit if necessary!
  }

  cout << "Moving onward with remainder of code." << endl;

  return 0;
}
