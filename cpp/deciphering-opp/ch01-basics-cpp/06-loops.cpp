#include <iostream>

using std::cout;
using std::endl;

int main() {
  int i;

  for (i = 0; i < 10; i++)
    cout << i << endl;

  for (int j = 0; j < 10; j++)
    // preferred declaration of loop control variable within loop
    cout << j << endl;

  // nested
  for (int i = 0; i < 10; i++) {
    cout << i << endl;
    for (int j = 0; j < 10; j++)
      cout << j << endl;
    cout << "\n";
  }

  return 0;
}
