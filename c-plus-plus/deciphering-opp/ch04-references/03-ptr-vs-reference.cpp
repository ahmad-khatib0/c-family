#include <iostream>

using std::cout; // preferred to: using namespace std;
using std::flush;

void AddOne(int &);
void AddOne(int *);
void Display(int &);

int main() {
  int x = 10, *y = nullptr;

  y = new int;
  *y = 15; // dereferencing the pointer
  Display(x);
  Display(*y);

  // calls reference version
  AddOne(x);
  AddOne(*y);
  Display(x);
  Display(*y);

  // calls pointer version
  AddOne(&x);
  AddOne(y);
  Display(x);
  Display(*y);

  return 0;
}

void AddOne(int &arg) { arg++; }

void AddOne(int *arg) { (*arg)++; }

void Display(int &arg) { cout << arg << " " << flush; }
