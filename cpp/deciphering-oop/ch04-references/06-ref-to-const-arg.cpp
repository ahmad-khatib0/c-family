#include <iostream>

using std::cin;
using std::cout; // preferred to: using namespace std;
using std::endl;

struct collection {
  int x;
  float y;
};

void Update(collection &);
void Print(const collection &);

int main() {
  collection col1, *col2 = nullptr;

  // allocate memory for collect2 from the heap
  col2 = new collection;

  Update(col1);  // a reference to the object is passes
  Update(*col2); // same here because *col2 is also an object

  Print(col1);
  Print(*col2);

  delete col2;

  return 0;
}

void Update(collection &c) {
  cout << "Enter <int> and <float> members: ";
  cin >> c.x >> c.y;
}

void Print(const collection &c) {
  cout << "x member: " << c.x << "   y member: " << c.y << endl;
}
