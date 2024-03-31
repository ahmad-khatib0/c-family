#include <stdio.h>
#include <stdlib.h>

// int *func(int i) {
//   const int j = i;  // ok
//   static int k = j; // error
//   return &k;
// }

void increment(void) {
  static unsigned int counter = 0;
  counter++;
  printf("counter %d\n", counter);
}

int main(void) {

  for (int i = 0; i < 9; i++) {
    increment();
  }

  return EXIT_SUCCESS;
}
