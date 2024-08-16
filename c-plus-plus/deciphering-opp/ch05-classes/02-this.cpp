
#include <cstring>
#include <iostream>
// though we'll prefer std::string, we will need to illustrate one dynamically
// allocated data member to show several important concepts in this chapter (so
// we'll use a single char *)

using std::cout;
using std::endl;
using std::string;

class Student {
public:
  string firstName; // data members
  string lastName;
  char middleInitial;
  float gpa;
  char *currentCourse; // though we'll prefer std::string, this data member will
                       // help us illustrate a few important ideas
  // member function prototypes
  void Initialize(string, string, char, float, const char *);
  void Print();
};

void Student::Initialize(string fn, string ln, char mi, float gpa,
                         const char *course) {

  firstName = fn;
  lastName = ln;
  this->middleInitial = mi; // optional use of this
  this->gpa = gpa;          // required, explicit use of this (same name)
  // remember to allocate the memory for data members that are pointers
  // plus one for the terminating null character
  currentCourse = new char[strlen(course + 1)];
  strcpy(currentCourse, course);
}
// This is internally how functions are represented, and consequentially,
// allows func overloading. It is as if Student::Initialize() is written as:
//
// notice that the THIS is the first implicit param internally
// void Student_Initialize_string_string_char_float_constchar*
//          (Student *const this, string fn, string ln,
//           char mi, float avg, const char *course)
// {
//    this->firstName = fn;
//    this->lastName = ln;
//    this->middleInitial = mi;
//    this->gpa = avg;
//    this->currentCourse = new char [strlen(course) + 1];
//    strcpy(this->currentCourse, course);
// }

void Student::Print() {
  cout << firstName << " ";
  cout << middleInitial << ". ";
  cout << lastName << " has a gpa of: ";
  cout << gpa << " and is enrolled in: ";
  cout << currentCourse << endl;
}
// It is as if Student::Print() is written as:
// void Student_Print(Student *const this)
// {
//    cout << this->firstName << " ";
//    cout << this->middleInitial << ". "
//    cout << this->lastName << " has a gpa of: ";
//    cout << this->gpa << " and is enrolled in: ";
//    cout << this->currentCourse << endl;
// }

int main() {
  Student s1;
  Student *s2 = new Student;

  s1.Initialize("Mary", "Jacobs", 'I', 3.9, "C++");
  s2->Initialize("Sam", "Nelson", 'B', 3.2, "C++");
  s1.Print();
  s2->Print(); // or use (*s2).Print();

  delete[] s1.currentCourse; // delete dynamically allocated data members
  delete[] s2->currentCourse;

  delete s2;
  return 0;
}
