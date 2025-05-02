#include <cstring>
#include <iomanip>
#include <iostream>

using std::cout; // preferred to: using namespace std;
using std::endl;

char suffix = 'A';

const char *GenId(const char *);

int main() {
  const char *newID1 = nullptr, *newID2 = nullptr;
  newID1 = GenId("Group"); // fn call will allocate memory
  newID2 = GenId("Group"); // fn call will allocate memory

  cout << "New ids: " << newID1 << " " << newID2 << endl;

  delete[] newID1;
  delete[] newID2;
  // notice that we are deallocating in a different scope than we allocated.
  // this will give us motivation later to use a smart pointer for safety. note:
  // delete newId1; or delete newId2; would also be ok (primitive type)
  return 0;
}

const char *GenId(const char *base) {
  char *temp =
      new char[strlen(base) + 2]; // One extra space for suffix plus null
  strcpy(temp, base);
  temp[strlen(base)] = suffix++; // append suffix to base
  temp[strlen(base) + 1] = '\0'; // add null char
  return temp;
  // temp will be up-cast to a const char * to be
  // treated more restrictively than it was defined
}
