#include <iostream>

// using namespace std;

using std::cin; // preferred to: using namespace std;
using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
  char name[20];
  int age = 0;

  cout << "Please enter a name and an age: ";
  // << this called the extraction operator
  cin >> name >> age; // caution, may overflow name var
  cout << "hello " << name;
  cout << ". You are " << age << " years old." << endl;

  return 0;
}
