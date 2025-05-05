#include <iostream>

using std::cout;
using std::endl;

[[nodiscard]] int Maximum(double, double);

int main() {
  int result = 0;
  int m = 6, n = 10;
  float x = 5.7, y = 9.89;

  // standard type conversion.
  result = Maximum(x, y);
  cout << "Result is: " << result << endl;
  cout << "The maximum is: " << Maximum(m, n) << endl;

  return 0;
}

[[nodiscard]] int Maximum(double a, double b) { return (a > b) ? a : b; }
