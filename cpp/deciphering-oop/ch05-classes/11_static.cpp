//
// Purpose: To illustrate static data members and static member functions.

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
  string currentCourse;
  const char *studentId;
  static int numStudents;

public:
  Student(); // default constructor
  Student(const string &, const string &, char, float, const string &, const char *);
  Student(const Student &);
  ~Student();

  void Print() const;
  const string &GetFirstName() const { return firstName; }
  const string &GetLastName() const { return lastName; }
  char GetMiddleInitial() const { return middleInitial; }
  float GetGpa() const { return gpa; }
  const string &GetCurrentCourse() const { return currentCourse; }
  const char *GetStudentId() const { return studentId; }
  void SetCurrentCourse(const string &);

  static int GetNumberStudents(); // static member function
};

int Student::numStudents = 0;

// Definition for static member function
inline int Student::GetNumberStudents() { return numStudents; }

inline void Student::SetCurrentCourse(const string &c) { currentCourse = c; }

// default constructor definition
Student::Student() : middleInitial('\0'), gpa(0.0), studentId(nullptr) { numStudents++; }

// alternate constructor definition
Student::Student(const string &fn, const string &ln, char mi, float avg, const string &course,
                 const char *id)
    : firstName(fn), lastName(ln), middleInitial(mi), gpa(avg), currentCourse(course) {
  // Because studentId is a const char *, we can not change value pointed
  // to -- that is, directly! So we enlist temp for help.
  char *temp = new char[strlen(id) + 1];
  strcpy(temp, id); // studentId can't be an lvaue,
  studentId = temp; // but temp can!
  numStudents++;
}

// copy constructor definition
Student::Student(const Student &s)
    : firstName(s.firstName), lastName(s.lastName), middleInitial(s.middleInitial), gpa(s.gpa),
      currentCourse(s.currentCourse) {
  delete studentId; // release previously allocated studentId
  // remember to do a deep copy for any data members that are pointers
  char *temp = new char[strlen(s.studentId) + 1];
  strcpy(temp, s.studentId); // studentId can't be an lvaue,
  studentId = temp;          // but temp can!
  numStudents++;
}

// destructor definition
Student::~Student() {
  delete[] studentId;
  // Note that older compilers will instead require:
  // delete const_cast<char *> (studentId); // cast is necessary for delete -- see book discussion
  numStudents--;
}

void Student::Print() const {
  cout << firstName << " " << middleInitial << ". ";
  cout << lastName << " with id: " << studentId;
  cout << " and gpa: " << gpa << " and is enrolled in: ";
  cout << currentCourse << endl;
}

int main() {
  Student s1("Nick", "Cole", 'S', 3.65, "C++", "112HAV");
  Student s2("Alex", "Tost", 'A', 3.78, "C++", "674HOP");

  cout << s1.GetFirstName() << " " << s1.GetLastName();
  cout << " Enrolled in " << s1.GetCurrentCourse() << endl;
  cout << s2.GetFirstName() << " " << s2.GetLastName();
  cout << " Enrolled in " << s2.GetCurrentCourse() << endl;

  // call a static member function in the preferred manner
  cout << "There are " << Student::GetNumberStudents();
  cout << " students" << endl;

  // Though not preferable, we could also use:
  // cout << "There are " << s1.GetNumberStudents();
  // cout << " students" << endl;

  return 0;
}
