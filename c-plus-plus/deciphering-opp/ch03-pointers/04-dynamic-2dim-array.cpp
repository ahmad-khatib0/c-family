#include <iostream>

using std::cin;
using std::cout; // preferred to: using namespace std;
using std::endl;
using std::flush;

int main(int argc, char *argv[]) {
  int numRows = 0, numColumns = 0;
  float **TwoDimArray = nullptr;
  // s a pointer to a pointer to float More specifically, we understand that
  // TwoDimArray will contain the address of one or more contiguous pointers,
  // each of which may point to one or more contiguous floating - point numbers.

  cout << "Enter number of rows: " << flush;
  cin >> numRows;
  TwoDimArray = new float *[numRows]; // allocate row (float) pointers

  cout << "Enter number of columns: " << flush;
  cin >> numColumns;

  for (int i = 0; i < numRows; i++) {

    // allocate column quantity for each row
    TwoDimArray[i] = new float[numColumns];
    for (int j = 0; j < numColumns; j++) {
      TwoDimArray[i][j] = i + j + .05;
      cout << TwoDimArray[i][j] << " ";
    }
    cout << endl;
  }

  for (int i = 0; i < numRows; i++)
    // delete columns for each row  -- note: delete
    // TwoDimArray[i]; is also ok since primitive type
    delete[] TwoDimArray[i];
  // delete allocated rows  -- note: delete TwoDimAray;
  // also ok since primitive type
  delete[] TwoDimArray;

  return 0;
}
