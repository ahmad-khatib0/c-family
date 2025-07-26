//
// Purpose: To illustrate STL queue

#include <iomanip>
#include <iostream>
#include <queue>

using std::cout;
using std::endl;
using std::queue;
using std::setprecision;
using std::string;
using std::to_string;

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
  Person(const Person &) = default;  // copy constructor
  Person &operator=(const Person &); // overloaded assignment operator
  virtual ~Person() = default;       // virtual destructor

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

Person &Person::operator=(const Person &p) {
  if (this != &p) {
    firstName = p.firstName;
    lastName = p.lastName;
    middleInitial = p.middleInitial;
    title = p.title;
  }
  return *this; // allow for cascaded assignments
}

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
  string studentId;
  static int numStudents;

public:
  Student(); // default constructor
  Student(
      const string &, const string &, char, const string &, float, const string &, const string &);
  Student(const Student &);            // copy constructor
  Student &operator=(const Student &); // overloaded assignment operator
  ~Student() override;                 // virtual destructor

  void EarnPhD();
  float GetGpa() const { return gpa; }
  const string &GetCurrentCourse() const { return currentCourse; }
  const string &GetStudentId() const { return studentId; }
  void SetCurrentCourse(const string &); // prototype only

  void Print() const override;
  void IsA() const override;
  static int GetNumberStudents() { return numStudents; }
};

int Student::numStudents = 0; // definition of static data member

inline void Student::SetCurrentCourse(const string &c) { currentCourse = c; }

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

Student &Student::operator=(const Student &s) {
  // make sure we're not assigning an object to itself
  if (this != &s) {
    Person::operator=(s);

    // delete any dynamically allocated data members in destination Student (or call ~Student() -
    // unconventional)

    // remember to allocate any memory in destination for copies of source members

    // copy data members from source to desination object
    gpa = s.gpa;
    currentCourse = s.currentCourse;
    studentId = s.studentId;
  }
  return *this; // allow for cascaded assignments
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

bool operator<(const Student &s1, const Student &s2) { return (s1.GetGpa() < s2.GetGpa()); }

bool operator==(const Student &s1, const Student &s2) { return (s1.GetGpa() == s2.GetGpa()); }

int main() {
  queue<Student> studentBody;

  studentBody.push(Student("Hana", "Sato", 'U', "Dr.", 3.8, "C++", "178PSU"));
  studentBody.push(Student("Sara", "Kato", 'B', "Dr.", 3.9, "C++", "272PSU"));
  studentBody.push(Student("Giselle", "LeBrun", 'R', "Ms.", 3.4, "C++", "299TU"));

  while (!studentBody.empty()) {
    studentBody.front().Print();
    studentBody.pop();
  }
  return 0;
}
