//
// Purpose: To illustrate STL vector

#include <iomanip>
#include <iostream>
#include <vector>

using std::cout; // preferred to: using namespace std;
using std::endl;
using std::setprecision;
using std::string;
using std::to_string;
using std::vector;

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
  if (this != &s) {
    Person::operator=(s);
    gpa = s.gpa;
    currentCourse = s.currentCourse;
    studentId = s.studentId;
  }
  return *this; // allow for cascaded assignments
}

void Student::EarnPhD() { ModifyTitle("Dr."); }

void Student::Print() const {
  // need to use access functions as these data members are defined in Person as private
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
  vector<Student> studentBody1, studentBody2;

  studentBody1.push_back(Student("Hana", "Sato", 'U', "Dr.", 3.8, "C++", "178PSU"));
  studentBody1.push_back(Student("Sara", "Kato", 'B', "Dr.", 3.9, "C++", "272PSU"));
  studentBody1.push_back(Student("Giselle", "LeBrun", 'R', "Ms.", 3.4, "C++", "299TU"));

  // Here we use traditional element, by element processing. We'll replace this type
  // of looping below with first an iterator and then a range-for loop (preferred)
  for (int i = 0; i < studentBody1.size(); i++)
    studentBody1[i].Print(); // print vector1’s contents

  studentBody2 = studentBody1; // assign one vector to another
  if (studentBody1 == studentBody2)
    cout << "Vectors are the same" << endl;

  cout << "Everyone to earn a PhD" << endl;
  // the auto keyword will allow iter's type to be determined by its first usage (in for loop)
  for (auto iter = studentBody2.begin(); iter != studentBody2.end(); iter++)
    (*iter).EarnPhD();

  // Here, we use the preferred modern looping -- we use a range-for loop AND auto to simplify type
  for (const auto &student : studentBody2)
    student.Print();

  if (!studentBody1.empty()) // clear first vector
    studentBody1.clear();

  return 0;
}
