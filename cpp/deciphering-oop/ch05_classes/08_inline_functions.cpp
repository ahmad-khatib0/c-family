#include <cstring>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

class Student {
private:
  // data members
  string firstName;
  string lastName;
  char middleInitial;
  float gpa;
  char *currentCourse;

public:
  // member function prototypes
  Student(); // default constructor
  Student(const string &, const string &, char, float, const char *);
  Student(const Student &); // copy constructor
  ~Student();               // destructor
  void Print();

  // inline function definitions
  // firstName is returned as a const string
  const string &GetFirstName() { return firstName; }
  const string &GetLastName() { return lastName; }
  char GetMiddleInitial() { return middleInitial; }
  float GetGpa() { return gpa; }
  const char *GetCurrentCourse() { return currentCourse; }

  // prototype only, see inline function definiton below
  void SetCurrentCourse(const char *);
};

inline void Student::SetCurrentCourse(const char *c) {
  delete[] currentCourse;                  // delete existing course
  currentCourse = new char[strlen(c) + 1]; // copy in new one
  strcpy(currentCourse, c);
}

// default constructor
Student::Student() {
  middleInitial = '\0';
  gpa = 0.0;
  currentCourse = nullptr;
}

// Alternate constructor member function definition
Student::Student(const string &fn, const string &ln, char mi, float avg, const char *course) {
  firstName = fn;
  lastName = ln;
  middleInitial = mi;
  gpa = avg;
  currentCourse = new char[strlen(course) + 1];
  strcpy(currentCourse, course);
}

// Copy constructor definition -implement a deep copy
Student::Student(const Student &s) {
  firstName = s.firstName;
  lastName = s.lastName;
  middleInitial = s.middleInitial;
  gpa = s.gpa;
  currentCourse = new char[strlen(s.currentCourse) + 1];
  strcpy(currentCourse, s.currentCourse);
}

// Member function definition
Student::~Student() { delete[] currentCourse; }

// Member function definition
void Student::Print() {
  cout << firstName << " " << middleInitial << ". ";
  cout << lastName << " has a gpa of: " << gpa;
  cout << " and is enrolled in: " << currentCourse << endl;
}

int main() {
  Student s1("Jo", "Muritz", 'Z', 4.0, "C++");

  cout << s1.GetFirstName() << " " << s1.GetLastName();
  cout << " Enrolled in: " << s1.GetCurrentCourse() << endl;

  s1.SetCurrentCourse("Advanced C++ Programming");

  cout << s1.GetFirstName() << " " << s1.GetLastName();
  cout << " New course: " << s1.GetCurrentCourse() << endl;

  return 0;
}
