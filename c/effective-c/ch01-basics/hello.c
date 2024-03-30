#include <stdio.h>  // preprocessor directive
#include <stdlib.h> // preprocessor directive

// void inside the parenthesis to indicate that the function does not accept
// arguments
int main(void) {
  if (puts("hello world") == EOF) {
    return EXIT_FAILURE;
  }

  printf("%s\n", "hello from printf");

  return EXIT_SUCCESS; // this is called macro
}
