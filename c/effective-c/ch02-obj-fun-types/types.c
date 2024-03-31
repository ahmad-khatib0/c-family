#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// If you include the header <stdbool.h> , you can also spell this type as
// bool and assign it the values true (which expands to the integer constant 1)
// and false (which expands to the integer constant 0)
_Bool flag1 = 0;
bool flag2 = false;

//
enum day { sun, mon, tue, wed, thu, fri, sat };
enum cardinal_points { north = 0, east = 90, south = 180, west = 270 };
enum months { jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };

int *fip();
// accepting any number of arguments of any type and returning an int *

void g(int i, int j);
// Specifying parameters with identifiers (as done here with g) can be
// problematic if an identifier is a macro. However, providing parameter names
// is good practice for self-documenting code

int *ip;
char *cp;
void *vp;
int i = 17;
int *ip = &i; // addr in memory ptr
//
// ip = &*ip;

//
int ia[11];
float *afp[17]; // type pointer to float

void array(void) {
  char str[11];
  for (unsigned int i = 0; i < 10; i++) {
    str[i] = '0' + i;
  };
  str[10] = '\0';
}

void func(int arr[5]);

void matrix(void) {
  unsigned int i = 0;
  unsigned int j = 0;
  int arr[3][5];

  func(arr[i]);
  int x = arr[i][j];
}

typedef unsigned int uint_type;
typedef signed char schar_type, *schar_p, (*fp)(void);
// declare schar_type as an alias for signed char,
// schar_p as an alias for signed char * (pointer)
// fp as an alias for signed char(*) (void)
//

struct sigrecord {
  int signum;
  char signame[20];
  char sigdesc[100];
} sigline, *sigline_p;

//
// This union might be used in a tree, graph, or other data structure that has
// some nodes that contain integer values (ni) and other nodes that contain
// floating-point values (nf)
//
union {
  struct {
    int type;
  } n;
  struct {
    int type;
    int intnode;
  } ni;
  struct {
    int type;
    double doublenode;
  } nf;
} u;

//
//
// s is called a tag
// Tags are a special naming mechanism for structs, unions, and enumerations.
struct s {
  //---snip---
};

typedef struct another_s {
  int x;
} t;

typedef struct {
  int x;
} another_t; // The tag name in struct, union, and enum is optional

// here you can't omit the tag name
typedef struct tnode {
  int count;
  struct tnode *left;
  struct tnode *right;
} tnode;

// Most C programmers use a different name for the tag and the typedef,
// but the same name works just fine
typedef struct another_tnode another_tnode;
struct another_tnode {
  int count;
  another_tnode *left;
  another_tnode *right;
} atnode;

// Type definitions can improve code readability beyond their use with
// structures. For example, all three of the following declarations of the
// signal function specify the same type:
typedef void fv(int), (*pfv)(int);

void (*signal(int, void (*)(int)))(int);
fv *signal(int, fv *);
pfv signal(int, pfv);

// Type Qualifiers:
const int unchangeable = 0;
// unchangeable = 4; error
// NOTE: It’s possible to accidentally convince your compiler to change a const
// qualified object for you. In the following example, we take the address of a
// const-qualified object unchangeable and tell the compiler that this is
// actually a pointer to an int:
int *changeable = (int *)&unchangeable;
// *changeable =  2;  // undefined behavior
//

volatile int port;

// The following function copies n bytes from the storage referenced by
// q to the storage referenced by p. The function parameters p and q are both
// restrict-qualified pointers:
void restrict_demo(unsigned int n, int *restrict p, int *restrict q) {
  while (n-- > 0) {
    *p++ = *q++;
  }
  // Because both p and q are restrict-qualified pointers, the compiler
  // can assume that an object accessed through one of the pointer parameters
  // is not also accessed through the other. The compiler can make this
  // assessment based solely on the parameter declarations without analyzing the
  // function body.
}

int main(void) {
  array();

  // using the dot to assign for non-pointer struct (directly)
  sigline.signum = 5;
  strcpy(sigline.signame, "SIGINT");
  strcpy(sigline.sigdesc, "Interrupt by keyboard");

  sigline_p = &sigline;
  // using the -> to assign to a pointer struct (indirectly)
  sigline_p->signum = 5;
  strcpy(sigline_p->signame, "SIGINT");
  strcpy(sigline_p->sigdesc, "Interrupt by keyboard");

  u.nf.type = 1;
  u.nf.doublenode = 34.55;

  // By itself, a tag is not a type name and cannot be used to declare a
  // variable (Saks 2002). Instead, you must declare variables of this type as
  struct s v;  // instance of struct s
  struct s *p; // pointer to struct s
  // The names of unions and enumerations are also tags and not types
  // meaning that they cannot be used alone to declare a variable
  // day today; // incorrect
  enum day today;

  // The tags of structures, unions, and enumerations are defined in a separate
  // namespace from ordinary identifiers. This allows a C program to have
  // both a tag and another identifier with the same spelling in the same scope:
  enum status status(void); // function
  enum status { ok, fail }; // enumeration
  //

  // C allows you to modify an object that is pointed to by a const-qualified
  // pointer by casting the const away, provided that the original object was
  // not declared const:
  int num = 1;
  const int j = 3;
  const int *num_ptr = &num;
  const int *j_ptr = &j;
  *(int *)num_ptr = 33; // works
  *(int *)j_ptr = 33;   // undefined behavior

  return EXIT_SUCCESS;
}
