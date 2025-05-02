#include <cmath>
#include <iostream>

using std::cout; // preferred to: using namespace std;
using std::endl;

constexpr float PI = 3.14159;

// user defined type declarations
class Circle {
public:
  float radius;
  float area;
};

class Rectangle {
public:
  float length;
  float width;
  float area;
};

void Display(Circle);
void Display(Rectangle);
// function prototypes These functions are
// overloaded since they differ in signature

int main() {
  Circle myCircle;
  Rectangle myRect;
  Rectangle mySquare;

  myCircle.radius = 5.0;
  myCircle.area = PI * pow(myCircle.radius, 2.0);

  myRect.length = 2.0;
  myRect.width = 4.0;
  myRect.area = myRect.length * myRect.width;

  mySquare.length = 4.0;
  mySquare.width = 4.0;
  mySquare.area = mySquare.length * mySquare.width;

  Display(myCircle);
  Display(myRect);
  Display(mySquare);

  return 0;
}

void Display(Circle c) {
  cout << "Circle with radius " << c.radius << " has an area of ";
  cout << c.area << endl;
}

void Display(Rectangle r) {
  cout << "Rectangle with length " << r.length << " and width ";
  cout << r.width << " has an area of " << r.area << endl;
}
