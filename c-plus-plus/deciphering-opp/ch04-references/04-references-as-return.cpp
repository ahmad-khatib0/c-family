#include <iostream>
using std::cout; // preferred to: using namespace std;
using std::endl;

int &CreateId(); // returns references

int main() {
  int &id1 = CreateId(); // reference established
  int &id2 = CreateId();
  cout << "Id1: " << id1 << " Id2: " << id2 << endl;
  // Id1: 100 Id2: 101 ,, remove static keyword and they both will print 100

  delete &id1;
  delete &id2;
  // Here, '&' is address-of not reference It is very unusual we'd delete in
  // this fashion, but now you know you can take the address of a ref variable
  // Also, allocating and deleting in diff scopes can lead to errors. This will
  // motivate use of smart pointers later

  return 0;
}

// Remember, it is not typical or recommended to allocate heap memory within a
// function and return it using a reference. The goal here is to demonstrate
// syntactically how it is done (with the return by reference) and how the
// subsequent deletion is done (in main)
int &CreateId() {
  static int count = 100; // initialize to 100 with first id
  int *memory = new int;
  *memory = count++; // use count as id, then increment
  return *memory;
}
