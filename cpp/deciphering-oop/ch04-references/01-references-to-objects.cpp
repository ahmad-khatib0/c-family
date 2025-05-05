#include <iostream>

using std::cout; // preferred to: using namespace std;
using std::endl;

int main() {
  int x = 0;
  int *p = new int;

  *p = 20;

  // References must be initialized to the object they are referencing
  // and may never be assigned another object to reference.
  // The reference and the referenced object must be the same type.
  //
  // A reference variable, behind the scenes, can be compared to a pointer
  // variable in that it holds the address of the variable that it is
  // referencing. Unlike a pointer variable, any usage of the reference variable
  // automatically dereferences the variable to go to the address that it
  // contains; the dereference operator * is simply not needed with references.
  // Dereferencing is automatic and implied with each use of a reference
  // variable.
  //
  int &refInt1 = x;
  int &refInt2 = *p;

  cout << x << " " << *p << " " << refInt1 << " " << refInt2 << endl;
  // 0 20 0 20

  x++;    // update x and refInt1
  (*p)++; // updates *p and refInt2

  cout << x << " " << *p << " " << refInt1 << " " << refInt2 << endl;
  // 1 21 1 21

  refInt1++; // updates refInt1 and x
  refInt2++; // updates refInt2 and *p

  cout << x << " " << *p << " " << refInt1 << " " << refInt2 << endl;
  // 2 22 2 22
  delete p;

  return 0;
}
