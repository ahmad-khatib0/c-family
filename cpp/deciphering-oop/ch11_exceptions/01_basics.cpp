//
// Purpose: To illustrate exception handling basics

#include <iomanip>
#include <iostream>

using std::cout; // preferred to: using namespace std;
using std::endl;
using std::setprecision;
using std::string;
using std::to_string;

constexpr int MAX = 5;

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
  // Remember, it isn't necessary to prototype the default copy constructor
  // Person(const Person &) = default;  // copy constructor
  // It is, however, important to prototype the default destructor if we want it to be virtual
  virtual ~Person() = default; // virtual destructor

  // inline function definitions
  const string &GetFirstName() const { return firstName; }
  const string &GetLastName() const { return lastName; }
  const string &GetTitle() const { return title; }
  char GetMiddleInitial() const { return middleInitial; }

  // Virtual functions will (usually) not be inlined since their method must be determined at run
  // time using v-table (except rare cases)
  virtual void Print() const;
  virtual void IsA() const;
  virtual void Greeting(const string &) const;
};

// With in-class initialization, writing the default constructor yourself is no
// longer necessary Here's how it would look if you did choose to provide one
// (and also chose not to use in-class initialization)
/* Person::Person() : middleInitial('\0') { } */

Person::Person(const string &fn, const string &ln, char mi, const string &t)
    : firstName(fn), lastName(ln), middleInitial(mi), title(t) {
  // dynamically allocate memory for any pointer data members here
}

// We are using default copy constructor, but if you needed to write it yourself,
// here is what it would look like:
/*
Person::Person(const Person &p) :
               firstName(p.firstName), lastName(p.lastName),
               middleInitial(p.middleInitial), title(p.title)
{ // deep copy any pointer data members here } */

// We're using default destructor, but if you wanted to write it yourself,
// this is what it would look like:
/* Person::~Person() { // release memory for any dynamically allocated data members } */

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
  static int numStudents;

public:
  Student(); // default constructor
  Student(
      const string &, const string &, char, const string &, float, const string &, const string &);
  Student(const Student &); // copy constructor
  ~Student() override;      // virtual destructor
  void EarnPhD();

  float GetGpa() const { return gpa; }
  const string &GetCurrentCourse() const { return currentCourse; }
  const string &GetStudentId() const { return studentId; }
  void SetCurrentCourse(const string &); // prototype only

  // In the derived class, the keyword virtual is optional for overridden
  // (polymorphic) methods, as is the keyword "override" Currently, "override"
  // is recommended for internal documentation, however "virtual" is not recommended
  void Print() const override;
  void IsA() const override;
  // note: we choose not to redefine Person::Greeting(const string &) const
  virtual void Validate(); // newly introduced virtual function in Student

  static int GetNumberStudents(); // static member function
};

int Student::numStudents = 0;

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

void Student::Validate() {
  // check Student instance to see if standards are met; if not, throw an exception
  throw string("Student does not meet prerequisites");
}

int main() {
  Student s1("Sara", "Lin", 'B', "Dr.", 3.9, "C++", "23PSU");

  try // ‘try’ this block of code -- Validate() may throw an exception
  {
    s1.Validate();            // see if Student meets admission stds
  } catch (const string &err) // catching a simple native string for now
  {
    cout << err << endl;
    // try to fix problem here…
    exit(1); // only if you can’t fix, exit gracefully
  }
  cout << "Moving onward with remainder of code." << endl;

  return 0;
}
