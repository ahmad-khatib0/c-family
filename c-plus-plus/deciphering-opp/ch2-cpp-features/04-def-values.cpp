#include <iostream>

using std::cout; // preferred to: using namespace std;
using std::endl;

[[nodiscard]] int Minimum(int arg1, int arg2 = 100000);
// function prototype with one default value

int main() {
  int x = 5;
  int y = 89;
  cout << Minimum(x) << endl;
  cout << Minimum(x, y) << endl;

  return 0;
}

[[nodiscard]] int Minimum(int a, int b) {
  if (a < b)
    return a;
  else
    return b;
}
