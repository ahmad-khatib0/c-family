//
// Purpose: To illustrate an alternate implmenentation of the Factory Method Pattern
// Implemented with the Factory Method in an Object Factory Class.
// Here, the Product of the Factory Method is Student.
// Concrete Products are GraduateStudent, UnderGraduateStudent, NonDegreeStudent

#include <iomanip>
#include <iostream>

using std::cout; // preferred to: using namespace std;
using std::endl;
using std::setprecision;
using std::string;
using std::to_string;

constexpr int MAX = 3;

class Person {
private:
  string firstName;
  string lastName;
  char middleInitial = '\0'; // in-class initialization -- value to be used in default constructor
  string title;              // Mr., Ms., Mrs., Miss, Dr., etc.

protected:
  void ModifyTitle(const string &);

public:
  Person() = default; // default constructor
  Person(const string &, const string &, char, const string &);
  // prototyping default copy constructor is not necessary
  // Person(const Person &) = default;  // copy constructor
  virtual ~Person() = default; // virtual destructor

  const string &GetFirstName() const { return firstName; }
  const string &GetLastName() const { return lastName; }
  const string &GetTitle() const { return title; }
  char GetMiddleInitial() const { return middleInitial; }

  virtual void Print() const;
  virtual string IsA() const;
  virtual void Greeting(const string &) const;
};

// Remember, we are using the system-supplied default constructor and in-class initialization

Person::Person(const string &fn, const string &ln, char mi, const string &t)
    : firstName(fn), lastName(ln), middleInitial(mi), title(t) {}

// Remember, we are also using the system-supplied copy constructor as well as system-supplied
// default destructor definitions

void Person::ModifyTitle(const string &newTitle) { title = newTitle; }

void Person::Print() const {
  cout << title << " " << firstName << " ";
  cout << middleInitial << ". " << lastName << endl;
}

string Person::IsA() const { return "Person"; }

void Person::Greeting(const string &msg) const { cout << msg << endl; }

// Student is now an Abstract class (see pure virtual Graduate() method)
// MatriculateStudent() is the Factory Method (Creation)
class Student : public Person {
private:
  float gpa = 0.0; // in-class initialization
  string currentCourse;
  const string studentId;
  static int numStudents; // static data member is initialized outside of class definition

public:
  Student(); // default constructor
  Student(
      const string &, const string &, char, const string &, float, const string &, const string &);
  Student(const Student &); // copy constructor
  ~Student() override;      // virtual destructor

  float GetGpa() const { return gpa; }
  const string &GetCurrentCourse() const { return currentCourse; }
  const string &GetStudentId() const { return studentId; }
  void SetCurrentCourse(const string &); // prototype only

  void Print() const override;
  string IsA() const override { return "Student"; }

  virtual void Graduate() = 0; // Now Student is abstract
  static int GetNumStudents() { return numStudents; }
};

// definition for static data member (which is implemented as external variable)
int Student::numStudents = 0; // notice initial value of 0

inline void Student::SetCurrentCourse(const string &c) { currentCourse = c; }

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

// Copy constructor definition
Student::Student(const Student &s)
    : Person(s), gpa(s.gpa), currentCourse(s.currentCourse), studentId(s.studentId) {
  numStudents++;
}

// destructor definition
Student::~Student() { numStudents--; }

void Student::Print() const {
  cout << "  " << GetTitle() << " " << GetFirstName() << " ";
  cout << GetMiddleInitial() << ". " << GetLastName();
  cout << " with id: " << studentId << " GPA: ";
  cout << setprecision(3) << " " << gpa;
  cout << " Course: " << currentCourse << endl;
}

class GradStudent : public Student {
private:
  string degree; // PhD, MS, MA, etc.
public:
  // member function prototypes
  GradStudent() = default; // default constructor
  GradStudent(const string &,
              const string &,
              const string &,
              char,
              const string &,
              float,
              const string &,
              const string &);

  // prototyping default copy constructor is not necessary
  GradStudent(const GradStudent &) = default; // copy constructor
  // Since most base class has virtual specified on destructor, it is not necessary at
  // this level if you want the default ~GradStudent() override = default;
  void EarnPhD();
  string IsA() const override { return "GradStudent"; }
  void Graduate() override;
};

GradStudent::GradStudent(const string &deg,
                         const string &fn,
                         const string &ln,
                         char mi,
                         const string &t,
                         float avg,
                         const string &course,
                         const string &id)
    : Student(fn, ln, mi, t, avg, course, id), degree(deg) {}

void GradStudent::EarnPhD() {
  if (!degree.compare("PhD")) // only PhD candidates can EarnPhD()
    ModifyTitle("Dr.");       // not MA and MS candidates
}

void GradStudent::Graduate() {
  // Here, we can check that the required number of credits
  // have been met with a passing gpa, and that their
  // doctoral or master’s thesis has been completed.
  EarnPhD();
  cout << "GradStudent::Graduate()" << endl;
}

class UnderGradStudent : public Student {
private:
  string degree; // BS, BA, etc
public:
  // member function prototypes
  UnderGradStudent() = default; // default constructor
  UnderGradStudent(const string &,
                   const string &,
                   const string &,
                   char,
                   const string &,
                   float,
                   const string &,
                   const string &);

  string IsA() const override { return "UnderGradStudent"; }
  void Graduate() override;
};

UnderGradStudent::UnderGradStudent(const string &deg,
                                   const string &fn,
                                   const string &ln,
                                   char mi,
                                   const string &t,
                                   float avg,
                                   const string &course,
                                   const string &id)
    : Student(fn, ln, mi, t, avg, course, id), degree(deg) {}

void UnderGradStudent::Graduate() {
  // Verify that number of credits and gpa requirements have
  // been met for major and any minors or concentrations.
  // Have all applicable university fees been paid?
  cout << "UnderGradStudent::Graduate()" << endl;
}

class NonDegreeStudent : public Student {
private:
public:
  NonDegreeStudent() = default; // default constructor
  NonDegreeStudent(
      const string &, const string &, char, const string &, float, const string &, const string &);

  string IsA() const override { return "NonDegreeStudent"; }
  void Graduate() override;
};

// Remember, we're using system-supplied default constructor, copy constructor and destructor

// Alternate constructor member function definition
NonDegreeStudent::NonDegreeStudent(const string &fn,
                                   const string &ln,
                                   char mi,
                                   const string &t,
                                   float avg,
                                   const string &course,
                                   const string &id)
    : Student(fn, ln, mi, t, avg, course, id) {}

void NonDegreeStudent::Graduate() {
  // Check if applicable tuition has been paid.
  // There is no credit or gpa requirement.
  cout << "NonDegreeStudent::Graduate()" << endl;
}

class StudentFactory {
public:
  // Creates a student based on the degree they seek
  Student *MatriculateStudent(const string &degree,
                              const string &fn,
                              const string &ln,
                              char mi,
                              const string &t,
                              float avg,
                              const string &course,
                              const string &id) {
    if (!degree.compare("PhD") || !degree.compare("MS") || !degree.compare("MA"))
      return new GradStudent(degree, fn, ln, mi, t, avg, course, id);
    else if (!degree.compare("BS") || !degree.compare("BA"))
      return new UnderGradStudent(degree, fn, ln, mi, t, avg, course, id);
    else if (!degree.compare("None"))
      return new NonDegreeStudent(fn, ln, mi, t, avg, course, id);
  }
};

int main() {
  Student *scholars[MAX] = {}; // will be initialized to nullptrs
  StudentFactory *UofD = new StudentFactory();

  // Student is now abstract....can not instantiate directly
  // Student("Sara", "Kato", 'B', "Dr.", 3.9, "C++", "272PSU");

  scholars[0] = UofD->MatriculateStudent("PhD", "Sara", "Kato", 'B', "Ms.", 3.9, "C++", "272PSU");
  scholars[1] = UofD->MatriculateStudent("BS", "Ana", "Sato", 'U', "Ms.", 3.8, "C++", "178PSU");
  scholars[2] =
      UofD->MatriculateStudent("None", "Elle", "LeBrun", 'R', "Miss", 3.5, "c++", "111BU");

  // less preferred looping style -- see preferred method below this grouping:
  /*
  for (int i = 0; i < MAX; i++)
  {
     scholars[i]->Graduate();
     scholars[i]->Print();
  }
  for (int i = 0; i < MAX; i++)
     delete scholars[i];   // engage virtual dest. sequence
  */

  // preferred looping style:
  for (auto *oneStudent : scholars) {
    oneStudent->Graduate();
    oneStudent->Print();
  }

  // preferred style
  for (auto *oneStudent : scholars)
    delete oneStudent; // engage virtual dest. sequence

  delete UofD; // delete the factory that creates various types of students

  return 0;
}
