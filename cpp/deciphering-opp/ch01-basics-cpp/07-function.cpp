#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int Minimum(int a, int b) {
  if (a < b)
    return a;
  else
    return b;
}

int main() {
  int x = 0, y = 0;

  cout << "Enter two integers: ";
  cin >> x >> y;
  cout << "The minimum is: " << Minimum(x, y) << endl;

  return 0;
}

// Notice that the function is first defined in the file and then called later
// in the file in the main() function. Strong type checking is performed on the
// call to the function by comparing the parameter types and their usage in the
// call to the function’s definition. What happens, however, when the function
// call precedes its definition? Or if the call to the function is in a separate
// file from its definition? <In these cases, the default action is for the
// compiler to assume a certain signature to the function, such as an integer
// return type, and that the formal parameters will match the types of arguments
// in the function call. Often, the default assumptions are incorrect; when the
// compiler then encounters the function definition later in the file (or when
// another file is linked in), an error will be raised indicating that the
// function call and definition do not match. These issues have historically
// been solved with a forward declaration of a function included at the top of a
// file where the function will be called. Forward declarations consist of the
// function return type, function name and types, and the number of parameters.
// In C++, a forward declaration has been improved upon and is instead known as
// a function prototype. Since there are many interesting details surrounding
// function prototyping, this topic will be covered in reasonable detail in the
// next chapter.
