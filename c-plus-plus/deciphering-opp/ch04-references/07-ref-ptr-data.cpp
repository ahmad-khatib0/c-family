#include <iostream>
#include <ostream>

using std::cout; // preferred to: using namespace std;
using std::endl;

int main() {
  int *ptr = new int;
  *ptr = 30;

  int *&refPtr = ptr; // establish a reference to a pointer
  cout << *ptr << " " << *refPtr << endl;

  delete ptr;
  return 0;
}
