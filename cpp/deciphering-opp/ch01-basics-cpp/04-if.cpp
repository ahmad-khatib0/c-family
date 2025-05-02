#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
  int x = 0;
  cout << "Enter an integer: ";
  cin >> x;

  // any non-zero value is considered to be true (so if(x) same as if(x == 0))
  if (x == 0)
    cout << "x is 0" << endl;
  else if (x < 0)
    cout << "x is negative" << endl;
  else {
    cout << "x is positive";
    cout << "and ten times x is: " << x * 10 << endl;
  }

  return 0;
}
