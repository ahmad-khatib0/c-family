
// Functions may be prototyped in different scopes with different default
// values. This allows functions to be built generically and customized through
// prototypes within multiple applications or for use in multiple sections of
// code

#include <iostream>

using std::cout; // preferred to: using namespace std;
using std::endl;

[[nodiscard]] int Minimum(int, int); // standard function prototype

void Function1(int x) {
  // local prototype with default value
  [[nodiscard]] int Minimum(int arg1, int arg2 = 500);

  cout << Minimum(x) << endl;
}

void Function2(int x) {
  // local prototype with default value
  [[nodiscard]] int Minimum(int arg1, int arg2 = 90);
  cout << Minimum(x) << endl;
}

// function definition with formal parameters
[[nodiscard]] int Minimum(int a, int b) {
  if (a < b)
    return a;
  else
    return b;
}

int main() {
  Function1(30);
  Function2(450);
  return 0;
}
