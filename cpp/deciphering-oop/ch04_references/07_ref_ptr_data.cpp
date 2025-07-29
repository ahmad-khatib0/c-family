#include <iostream>
#include <ostream>

using std::cout; // preferred to: using namespace std;
using std::endl;

int main() {
  int *ptr = new int;
  *ptr = 30;

  int *&refPtr = ptr; // establish a reference to a pointer
  // It helps to read the declaration from right to left. As such, we use ptr to
  // initialize refPtr, which is a reference to a pointer to an int
  cout << *ptr << " " << *refPtr << endl;

  delete ptr;
  return 0;
}
