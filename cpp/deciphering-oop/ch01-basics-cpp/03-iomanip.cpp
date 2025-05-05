#include <iomanip>
#include <iostream>
#include <ostream>

using std::cin; // preferred to: using namespace std;
using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
  char name[20];
  float gpa = 0.0; // grade point average
  cout << "Please enter a name and a gpa: ";
  cin >> std::setw(20) >> name >> gpa;
  cout << "Hello " << name << std::flush;
  cout << ". GPA is: " << std::setprecision(3) << gpa << std::endl;

  return 0;
}
