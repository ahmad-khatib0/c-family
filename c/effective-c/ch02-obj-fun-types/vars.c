#include <stdio.h>

// void swap(int, int);
void swap(int *, int *);

// This kind of code block ( which is:  {} ) is also known as a compound
// statement
int main(void) {
  // a and b has automatic storage duration  meaning that they exist until
  // execution leaves the block in which they’re defined
  int a = 22;
  int b = 33;

  swap(&a, &b);
  printf("main: a=%d, b=%d\n", a, b);
  return 0;
}

// void swap(int a, int b) { // pass by value
void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
  printf("swap: a = %d, b = %d\n", a, b);
}
