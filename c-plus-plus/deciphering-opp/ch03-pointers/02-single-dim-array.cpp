#include <iostream>

using std::cin;
using std::cout; // preferred to: using namespace std;
using std::endl;
using std::flush;

struct collection {
  int x;
  float y;
};

int main(int argc, char *argv[]) {
  int numElements = 0, *intArray = nullptr;
  collection *collectionArray = nullptr;

  cout << "How many elements would you like? " << flush;
  cin >> numElements;

  intArray = new int[numElements];
  collectionArray = new collection[numElements];

  for (int i = 0; i < numElements; i++) {
    intArray[i] = i;
    collectionArray[i].x = i;
    collectionArray[i].y = i + .5;

    // alternatively use pointer notation to print values
    cout << *(intArray + i) << " "; // intArray print 0
    cout << (*(collectionArray + i)).y << endl;
  }

  // mark memory for deletion
  delete[] intArray;
  // for an array of primitive types, delete intArray; is also ok, the []'s on
  // delete first call a 'cleanup' function on each element before reclaiming
  // the heap memory (useful for user defined types)
  delete[] collectionArray;
  return 0;
}
