#include <iostream>

using std::cout;
using std::endl;
using std::string;

// A C++ structure in its simplest form can be used to collect common data
// elements together in a single unit.
struct Student {
  string name;
  float semesterGrades[5];
  float gpa;
};

typedef float dollars;
using money = float;
// the new type dollars can be used interchangeably with the type float.
// Likewise, the new alias money can also be used interchangeably with type
// float.

int main() {
  // the tag student also becomes the type name (unlike in C, where a variable
  // declaration would need the word struct to precede the type)
  Student s1;
  s1.name = "George Katz";
  s1.semesterGrades[0] = 3.0;
  s1.semesterGrades[1] = 4.0;
  s1.gpa = 3.5;

  cout << s1.name << " has GPA: " << s1.gpa << endl;
  return 0;
}
