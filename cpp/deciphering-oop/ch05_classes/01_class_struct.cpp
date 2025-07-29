#include <iostream>

using std::cout; // preferred to: using namespace std;
using std::endl;
using std::string;

struct student {
  string name;
  float gpa;
  void Initialize(string, float); // function prototype
  void Print();
};

class University {
public:
  string name;
  int numStudents;
  void Initialize(string, int); // function prototype
  void Print();
};

// ::, the scope resolution operator
void student::Print() { cout << name << " GPA: " << gpa << endl; }

void student::Initialize(string n, float avg) {
  name = n;
  gpa = avg;
};

void University::Initialize(string n, int num) {
  name = n;
  numStudents = num;
}

void University::Print() {
  cout << name << " Enrollment: " << numStudents << endl;
}

int main(int argc, char *argv[]) {
  student s1;
  s1.Initialize("John doe", 3.4);
  s1.Print();

  University u1; // instantiate a University (class)
  u1.Initialize("GWU", 25600);
  u1.Print();

  University *u2; // ptr declaration
  u2 = new University();
  u2->Initialize("UMD", 40500);
  u2->Print(); // or alternatively: (*u2).Print();
  delete u2;

  return 0;
}
