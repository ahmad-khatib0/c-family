#include <iostream>

using std::cout; // preferred to: using namespace std;
using std::endl;

struct collection {
  int x;
  float y;
};

int main() {
  collection *item = nullptr; // pointer declaration and initialization

  item = new collection; // mem alocation
  item->x = 9;           // use -> to access data member x
  (*item).y = 120.77;    // alternative notation to access member y
  cout << (*item).x << " " << item->y << endl;

  delete item;
  return 0;
}
