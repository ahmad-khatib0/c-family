
#include <iostream>

using std::cout; // preferred to: using namespace std;
using std::endl;

// Also notice the use of [[nodiscard]] preceding the return type of the
// function. This indicates that the programmer should store the return value or
// otherwise utilize the return value (such as in an expression). The compiler
// will issue a warning if the return value of this function is ignored.
[[nodiscard]] int Minimum(int, int); // prototype

int main(int argc, char *argv[]) {
  int x = 5, y = 33;

  cout << Minimum(x, y) << endl;
  // Minimum(x, y); // function call that ignores return value will issue a warning

  return 0;
}

// function definition with formal parameters
[[nodiscard]] int Minimum(int a, int b) {
  if (a < b)
    return a;
  else
    return b;
}
