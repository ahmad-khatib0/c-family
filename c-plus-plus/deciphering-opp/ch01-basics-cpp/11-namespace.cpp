#include <iostream>

// using namespace std;   // This statement brings in entire namespace std
using std::cout; // Instead, we can bring in individual elements....
using std::endl;

namespace DataTypes {
int total;

// full class definition ...
class LinkList {};

// full class definition ...
class Stack {};

}; // namespace DataTypes

namespace AbstractDataTypes {
// full class definition ...
class Stack {};

// full class definition ...
class Queue {};
}; // namespace AbstractDataTypes

namespace AbstractDataTypes {
int total;

// full class definition ...
class Tree {};
}; // namespace AbstractDataTypes

int main() {
  using namespace AbstractDataTypes; // activate namespace
  using DataTypes::LinkList;         // activate only LinkList

  LinkList list1; // LinkList is found in DataTypes
  Stack stack1;   // Stack is found in AbstractDataTypes

  total = 5;             // assing, from active AbstractDataTypes
  DataTypes::total = 85; // specify non-active member

  cout << "total " << total << "\n";
  cout << "DataTypes::total " << DataTypes::total << endl;

  return 0;
}
