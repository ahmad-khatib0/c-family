//
// Purpose: To illustrate a 1-many association.
// A University is associated to many students. In this case, let's assume,
// each student has an association to a single university.

// In a generalized aggregation, a part may exist without the whole. A part will be
// created separately and then attached to the whole at a later point in time. When
// the whole goes away, a part may then remain to be salvaged for use with another
// outer or whole object.
//
// In a generalized aggregation, the Has-A relationship certainly applies, as does the
// whole-part designation. The difference is that the whole object will not create nor
// destroy a part subobject. Consider the straightforward example that a Car Has-A(n) Engine.
// A Car object also Has-A set of four Tire objects. The Engine or Tire objects can be
// manufactured separately and then passed to the constructor of the Car to provide these
// parts to the whole. Yet should an Engine be destroyed, a new Engine can easily be
// swapped out (using a member function), without requiring the entire Car to be destroyed
// and then reconstructed.

#include <iomanip>
#include <iostream>

using std::cout;
using std::endl;
using std::setprecision;
using std::string;
using std::to_string;

class Student; // forward declaration

class University {
private:
  string name;
  // maximum students supported by university Association to many students
  static constexpr int MAX = 25;
  // initializes all pointerse to nullptr; could alternatively init
  // all pointers in constructors to nullptr
  Student *studentBody[MAX] = {};
  int currentNumStudents = 0;

public:
  University();
  University(const string &);
  University(const University &) = delete; // prohibit copies
  ~University();

  void EnrollStudent(Student *);
  const string &GetName() const { return name; }
  void PrintStudents() const;
};

University::University() {
  // In lieu of in-class initialization, we could alternatively set each studentBody
  // pointer to nullptr for (int i = 0; i < MAX; i++)
  // let's set each to nullptr for safety studentBody[i] = nullptr;
}

University::University(const string &n)
    : name(n) // remember, currentNumStudents is set with in-class init
{
  // In lieu of in-class initialization, we could alternatively set each studentBody pointer to
  // nullptr for (int i = 0; i < MAX; i++)   // let's set each to nullptr studentBody[i] = nullptr;
}

University::~University() {
  // The students will be deleted by whatever means they were created,
  // however we can null out our pointers to them!
  for (int i = 0; i < MAX; i++)
    studentBody[i] = nullptr;
}

void University::EnrollStudent(Student *s) { studentBody[currentNumStudents++] = s; }

class Id final {
private:
  string idNumber;

public:
  Id() = default; // we do want this interface for construction
  Id(const string &id) : idNumber(id) {}
  // Remember, we get the default copy constructor and destructor, even without the following
  // prototypes: Id(const Id &) = default; ~Id() = default;
  const string &GetId() const { return idNumber; }
};

// We're using the default copy constructor, but if you wrote it yourself,
// this is what it would look like: Remember to prototype it if you define it!
/* Id::Id(const Id &id) : idNumber(id.idNumber) { } */

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
  // We get the default copy constructor, even without the following prototype:
  // Person(const Person &) = default;  // copy constructor
  // However, we need the following destructor prototype to mark the default destructor virtual
  virtual ~Person() = default; // virtual destructor

  // inline function definitions
  const string &GetFirstName() const { return firstName; }
  const string &GetLastName() const { return lastName; }
  const string &GetTitle() const { return title; }
  char GetMiddleInitial() const { return middleInitial; }

  // Virtual functions
  virtual void Print() const;
  virtual void IsA() const;
  virtual void Greeting(const string &) const;
};

// With in-class initialization, writing the default constructor yourself is no
// longer necessary Here's how it would look if you did choose to provide one
// (and also chose not to use in-class initialization)
/* Person::Person() : middleInitial('\0') { } */

Person::Person(const string &fn, const string &ln, char mi, const string &t)
    : firstName(fn), lastName(ln), middleInitial(mi), title(t) {}

// We're using default copy constructor, but if you wrote it, this is what it would look like:
/* Person::Person(const Person &p) : firstName(p.firstName), lastName(p.lastName),
middleInitial(p.middleInitial), title(p.title) { } */

// We're using default destructor, but if you wrote it, this is what it would look like:
/* Person::~Person() { } */

void Person::ModifyTitle(const string &newTitle) { title = newTitle; }

void Person::Print() const {
  cout << title << " " << firstName << " ";
  cout << middleInitial << ". " << lastName << endl;
}

void Person::IsA() const { cout << "Person" << endl; }

void Person::Greeting(const string &msg) const { cout << msg << endl; }

class Student : public Person // whole
{
private:
  float gpa = 0.0;
  string currentCourse;
  static int numStudents;
  Id studentId;               // part
  University *univ = nullptr; // Association to University object, set with in-class initialization

public:
  // member function prototypes
  Student(); // default constructor
  Student(const string &,
          const string &,
          char,
          const string &,
          float,
          const string &,
          const string &,
          University *);
  Student(const Student &); // copy constructor
  ~Student() override;      // destructor

  void EarnPhD();
  float GetGpa() const { return gpa; } // various inline fns.
  const string &GetCurrentCourse() const { return currentCourse; }
  void SetCurrentCourse(const string &); // prototype only
  void Print() const override;
  void IsA() const override;
  static int GetNumberStudents() { return numStudents; }

  // Access function for associated Id object
  const string &GetStudentId() const { return studentId.GetId(); }
  const string &GetUniversity() const { return univ->GetName(); }
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
                 const string &id,
                 University *univ)
    : Person(fn, ln, mi, t), gpa(avg), currentCourse(course), studentId(id) {
  this->univ = univ; // demonstrating a required use of 'this' to set forward link -- data member
                     // and parameter have same identifiers
  univ->EnrollStudent(this); // another required use of 'this' to create the back link
  numStudents++;
}

Student::Student(const Student &s)
    : Person(s), gpa(s.gpa), currentCourse(s.currentCourse), studentId(s.studentId) {
  this->univ = s.univ; // set forward link -- forward link could also be set in mbr init list if
                       // param name is changed
  univ->EnrollStudent(this); // create back link
  numStudents++;
}

// destructor definition
Student::~Student() {
  numStudents--;
  univ = nullptr; // a Student does not delete its University
                  // the embedded object studentId will also be destructed
}

void Student::EarnPhD() { ModifyTitle("Dr."); }

void Student::Print() const {
  cout << GetTitle() << " " << GetFirstName() << " ";
  cout << GetMiddleInitial() << ". " << GetLastName();
  cout << " with id: " << studentId.GetId() << " GPA: ";
  cout << setprecision(3) << " " << gpa;
  cout << " Course: " << currentCourse << endl;
}

void Student::IsA() const { cout << "Student" << endl; }

void University::PrintStudents() const {
  cout << name << " has the following students:" << endl;

  for (int i = 0; i < currentNumStudents; i++) {
    cout << "\t" << studentBody[i]->GetFirstName() << " ";
    cout << studentBody[i]->GetLastName() << endl;
  }
}

int main() {
  University u1("The George Washington University");
  Student s1("Gabby", "Doone", 'A', "Miss", 3.85, "C++", "4225GWU", &u1);
  Student s2("Giselle", "LeBrun", 'A', "Ms.", 3.45, "C++", "1227GWU", &u1);
  Student s3("Eve", "Kendall", 'B', "Ms.", 3.71, "C++", "5542GWU", &u1);

  cout << s1.GetFirstName() << " " << s1.GetLastName() << " attends ";
  cout << s1.GetUniversity() << endl;

  cout << s2.GetFirstName() << " " << s2.GetLastName() << " attends ";
  cout << s2.GetUniversity() << endl;

  cout << s3.GetFirstName() << " " << s3.GetLastName() << " attends ";
  cout << s3.GetUniversity() << endl;

  u1.PrintStudents();
  return 0;
}
