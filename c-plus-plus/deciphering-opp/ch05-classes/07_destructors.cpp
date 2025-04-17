#include <cstring>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

class University {
private:
  char *name;
  // though we'll prefer std::string, this data member will help us illustrate destructor purpose
  int numStudents;

public:
  // constructor prototypes
  University();                   // default constructor
  University(const char *, int);  // alternate constructor
  University(const University &); // copy constructor
  ~University();                  // destructor prototype
  void Print();
};

University::University() // default constructor
{
  name = nullptr;
  numStudents = 0;
}

University::University(const char *n, int num) // alt constructor
{
  name = new char[strlen(n) + 1]; // allocate memory for ptr data members
  strcpy(name, n);
  numStudents = num;
}

University::University(const University &u) // copy const
{
  name = new char[strlen(u.name) + 1]; // deep copy data members that are pointers
  strcpy(name, u.name);
  numStudents = u.numStudents;
}

// destructor definition
University::~University() {
  delete[] name; // be sure to deallocate any dynamically allocoated memory
  cout << "Destructor called " << this << endl;
}

void University::Print() {
  cout << "University: " << name;
  cout << " Enrollment: " << numStudents << endl;
}

int main() {
  University u1("Temple University", 39500);
  University *u2 = new University("Boston U", 32500);
  u1.Print();
  u2->Print();
  delete u2; // destructor will be called before delete()
             // destructor for u1 will be called before

  return 0;
}
