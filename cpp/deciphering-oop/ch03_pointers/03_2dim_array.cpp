
#include <iostream>

using std::cin;
using std::cout; // preferred to: using namespace std;
using std::endl;
using std::flush;

constexpr int NUMROWS = 5;

int main(int argc, char *argv[]) {
  // float *TwoDimArray[NUMROWS];   // caution - this array is uninitialized, so
  // the following declaration is preferrred.. // alternatively, initialize each
  // element to nullptr
  float *TwoDimArray[NUMROWS] = {nullptr, nullptr, nullptr, nullptr, nullptr};
  int numColumns = 0;

  cout << "Enter number of columns: " << flush;
  cin >> numColumns;

  for (int i = 0; i < NUMROWS; i++) {
    TwoDimArray[i] = new float[numColumns];

    // load each column entry with dta
    for (int j = 0; j < numColumns; j++) {
      TwoDimArray[i][j] = i + j + .05;
      cout << TwoDimArray[i][j] << " ";
    }
    cout << endl;
  }

  // delete column quantities for each row... note: delete TwoDimArray[i]; would
  // also work since this is of a standard type (the []'s ensure a clean up fn
  // is called on each element -- useful for user defined types) more on that
  // when we talk about classes in detail in Chapter 5
  for (int i = 0; i < NUMROWS; i++)
    delete[] TwoDimArray[i];

  return 0;
}
