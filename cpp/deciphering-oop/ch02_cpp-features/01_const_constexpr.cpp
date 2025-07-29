#include <cstring>
#include <iomanip>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::setw;

const int MAX = 60;

constexpr int LARGEST = 60; // simple constexpr variable declaration and initialization

// function's return value is a constexpr
constexpr int Minimum(int a, int b) { return (a < b) ? a : b; }

int main() {
  int x = 0, y = 0;
  constexpr int a = 10, b = 15;

  cout << "Enter two <int> values: ";
  cin >> x >> y;

  const int min = Minimum(x, y);
  cout << "Minimum is: " << min << endl;

  constexpr int smallest = Minimum(a, b);
  cout << "Smallest of " << a << " " << b << " is: " << smallest << endl;

  char bigName[MAX] = {""};       // const variable used to size an array
  char largeName[LARGEST] = {""}; // constexpr used to size an array
  cout << "Enter two names: ";
  cin >> setw(MAX) >> bigName >> setw(LARGEST) >> largeName;

  const int namelen = strlen(bigName); // a const can be initialized with a calculated value
  cout << "Length of name 1: " << namelen << endl;
  cout << "Length of name 2: " << strlen(largeName) << endl;

  return 0;
}
