//
// Purpose: To demonstrate a simple template function.

#include <iostream>

using std::cout; // preferred to: using namespace std;
using std::endl;

//  template function prototype
template <class Type1, class Type2> Type2 ChooseFirst(Type1, Type2);

template <class Type1, class Type2> // template preamble
Type2 ChooseFirst(Type1 x, Type2 y) // template function
{
  if (x < y)
    // Note: cast here is optional - it will happen automatically with return statement
    return static_cast<Type2>(x);
  else
    return y;
}

int main() {
  int value1 = 4, value2 = 7;
  float value3 = 5.67f;
  cout << "First: " << ChooseFirst(value1, value3) << endl;
  cout << "First: " << ChooseFirst(value2, value1) << endl;
}
