#include <cstring>
#include <string>

int main() {
  int x = 5;
  float y = 9.87;
  float y2 = 10.76f; // optional 'f' suffix on float literal
  double yy = 123456.78;
  char z = 'Z';
  bool test = true;

  char name[10] = "Dorothy"; // size is larger than needed
  float grades[20];          // array is not initialized; caution!
  grades[0] = 4.0;           // assign a value to one element of array
  float scores[] = {3.3, 4.3, 4.0, 3.7}; // initialized array
  //
  //

  char book1[] = "C++ Programming"; // size calculated by initializer
  char book2[25];                   // this string is uninitialized; caution!
  strcpy(book2, "OO Programming with C++");
  strcmp(book1, book2);
  int length = strlen(book2);
  std::string book3 = "Advanced C++ Programming"; // safer usage
  std::string book4("OOP with C++");              // alt. way to init. string
  std::string book5(book4); // create book5 using book4 as a basis

  return 0;
}
