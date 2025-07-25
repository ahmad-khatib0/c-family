//
// Purpose: To illustrate a nested exception class within a user defined class.

#include <iomanip>
#include <iostream>

using std::cout; // preferred to: using namespace std;
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
  static int numStudents;

public:
  Student(); // default constructor
  Student(
      const string &, const string &, char, const string &, float, const string &, const string &);
  Student(const Student &); // copy constructor
  ~Student() override;      // virtual destructor

  void EarnPhD();
  bool TakePrerequisites();
  float GetGpa() const { return gpa; }
  const string &GetCurrentCourse() const { return currentCourse; }
  const string &GetStudentId() const { return studentId; }
  void SetCurrentCourse(const string &); // prototype only

  void Print() const override;
  void IsA() const override;

  virtual void Validate(); // newly introduced virtual fns in Student
  virtual void Graduate();

  static int GetNumberStudents(); // static member function

  class StudentException // over-simplified nested exception class
  {
  private:
    // will be over written after successful alt. constructor
    // (we aren't offering default constuctor)
    int number = 0;

  public:
    StudentException(int num) : number(num) {}
    // Remember, it is not necessary to prototype the default destructor
    // ~StudentException() = default;
    int GetNum() const { return number; }
  };
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
  cout << GetTitle() << " " << GetFirstName() << " ";
  cout << GetMiddleInitial() << ". " << GetLastName();
  cout << " with id: " << studentId << " GPA: ";
  cout << setprecision(3) << " " << gpa;
  cout << " Course: " << currentCourse << endl;
}

void Student::IsA() const { cout << "Student" << endl; }

void Student::Validate() {
  // check Student instance to see if standards are met; if not, throw an exception
  throw "Student does not meet prerequisites";
}

bool Student::TakePrerequisites() {
  // Assume this function can correct the issue at hand if not, it returns false
  return false;
}

void Student::Graduate() {
  // Assume this method is fully implemented. Here, I'm forcing a throw of a Course
  // unless the bad gpa requirement is first triggered

  if (gpa < 2.0) // if Student doesn’t meet gpa requirements, throw bad gpa
    throw gpa;
  // if Student is short credits, throw how many are missing
  // throw numCreditsMissing;  // assume this is an integer
  // or if Student is missing a course, construct and
  // then throw the missing Course as a referenceable object
  // or throw a string containing a diagnostic message
  // throw (“Does not meet requirements”);

  throw StudentException(5);
}

int main() {
  set_terminate(AppSpecificTerminate); // register fn.

  Student s1("Ling", "Mau", 'I', "Ms.", 3.1, "C++", "55UD");

  try {
    s1.Graduate();
  } catch (float err) {
    cout << "Too low gpa: " << err << endl;
    exit(1); // only if you can’t fix, exit gracefully
  } catch (int err) {
    cout << "Missing " << err << " credits" << endl;
    exit(2);
  } catch (const char *err) {
    cout << err << endl;
    exit(4);
  } catch (const Student::StudentException &err) {
    cout << "Error: " << err.GetNum() << endl;
    // if you can correct the error, continue the application
    exit(5); // otherwise exit
  } catch (...) {
    cout << "Exiting" << endl;
    exit(6);
  }

  cout << "Moving onward with remainder of code." << endl;

  return 0;
}
