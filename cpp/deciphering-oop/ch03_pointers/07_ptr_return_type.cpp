#include <iomanip>
#include <iostream>

using std::cin; // preferred to: using namespace std;
using std::cout;
using std::endl;
using std::flush;
using std::setw;

constexpr int MAX = 20;

[[nodiscard]] char *createName();

int main() {
  char *name = nullptr;
  name = createName();
  cout << "Name: " << name << endl;
  delete[] name;

  // notice that we delete in a different scope than that which we allocated.
  // this is a motivation for us later choosing a smart pointer (to alleviate
  // unintentional errors) Also note that delete name; would have been ok
  // (primitive type)
  return 0;
}

[[nodiscard]] char *createName() {
  // Functions may return pointers to data via their return statements. When
  // returning a pointer via the return statement of a function, be sure that
  // the memory that is pointed to will persist after the function call is
  // completed. Do not return a pointer to stack memory that is local to the
  // function. That is, do not return a pointer to local variables defined on
  // the stack within the function. However, returning a pointer to memory
  // allocated using new() within the function is acceptable. As the allocated
  // memory will be on the heap, it will exist past the function call.
  char *name = new char[MAX];

  cout << "Enter a name" << flush;
  cin >> setw(MAX) >> name;
  // setw ensures we don't overflow the input buffer
  return name;
}
