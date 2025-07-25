//
// Purpose: To illustrate an assortment of exception handlers.

#include <iomanip>
#include <iostream>

using std::cout;
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

class Course {
private:
  string title;
  int number = 0;

public:
  Course(const string &title, int num) : number(num) { this->title = title; }

  int GetCourseNum() const { return number; }
  const string &GetTitle() const { return title; }
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

void Person::ModifyTitle(const string &newTitle) { title = newTitle; }

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
  ~Student() override;      // destructor

  void EarnPhD();
  bool TakePrerequisites(); // new member function

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

// Definition for static member function (it is also inline)
inline int Student::GetNumberStudents() { return numStudents; }

Student::Student() : studentId(to_string(numStudents + 100) + "Id") { numStudents++; }

// Alternate constructor member function definition
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

void Student::Print() const {
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
  // Assume this function can correct the issue at hand
  // if not, it returns false
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
  throw Course("Intro. to Programming", 1234);
  // Note: had we dynamically allocated the Course to be thrown on the heap, it would look like
  // this: throw *(new Course("Intro. to Programming", 1234));  // but, we'd then need to remember
  // to delete it in our catch! or throw a string containing a diagnostic message throw string(“Does
  // not meet requirements”);
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
  } catch (const Course &err) {
    cout << "Needs to take: " << err.GetTitle() << endl;
    cout << "Course #: " << err.GetCourseNum() << endl;
    // NOTE APPLICABLE ONLY if we dynamically allocated the Course that was thrown
    // (you can see why it would not be recommended) if we fix the problem and don't
    // exit, be sure to: delete &err; // we're taking address of a ref for delete -- again,
    // this isn't applicable unless Course was a heap object END OF NOTE: this is an
    // example as to why a smart pointer may be helpful!
    exit(3); // otherwise, memory will be reclaimed upon exit()
  } catch (const string &err) {
    cout << err << endl;
    exit(4);
  } catch (...) {
    cout << "Exiting" << endl;
    exit(5);
  }

  cout << "Moving onward with remainder of code." << endl;

  return 0;
}
