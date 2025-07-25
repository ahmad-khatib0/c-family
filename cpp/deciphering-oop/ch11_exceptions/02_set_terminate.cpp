//
// Purpose: To illustrate registering a user defined function with terminate()
// using set_terminate(), This function will be called instead of abort()

#include <iomanip>
#include <iostream>

using std::cout; // preferred to: using namespace std;
using std::endl;
using std::set_terminate;
using std::setprecision;
using std::string;
using std::to_string;

constexpr int MAX = 5;

// AppSpecificTerminate is called in lieu of abort() since there is no matching catch block.
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
  Person() = default; // default constructor
  Person(const string &, const string &, char, const string &);
  virtual ~Person() = default; // virtual destructor

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
  float gpa = 0.0;
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

  // inline function definitions
  float GetGpa() const { return gpa; }
  const string &GetCurrentCourse() const { return currentCourse; }
  const string &GetStudentId() const { return studentId; }
  void SetCurrentCourse(const string &); // prototype only

  void Print() const override;
  void IsA() const override;
  virtual void Validate(); // newly introduced virtual function in Student

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
  // dynamically allocate memory for any pointer data members here
  numStudents++;
}

// Copy constructor definition
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

void Student::Validate() { throw string("Student does not meet prerequisites"); }

int main() {
  set_terminate(AppSpecificTerminate); // register fn.

  Student s1("Sara", "Kato", 'B', "Dr.", 3.9, "C++", "272PSU");

  try {
    s1.Validate();
  } catch (float err) {
    cout << err << endl;
    // try to fix problem here…
    exit(1); // only if you can’t fix, exit gracefully
  }
  cout << "Moving onward with remainder of code." << endl;

  return 0;
}
