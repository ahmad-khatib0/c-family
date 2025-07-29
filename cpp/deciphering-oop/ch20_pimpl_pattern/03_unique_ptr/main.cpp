
// Purpose: To illustrate use of pImpl pattern - in this version, the implementation uses smart
// pointers! Note: this driver can be used with non-pImpl Person class or pImpl class with raw
// pointers -- works the same! However, the implementation of this version (Person.h and
// PersonImpl.cpp uses smart pointers)

#include "person.h"
#include <iostream>

constexpr int MAX = 3;

int main() {
  Person *people[MAX] = {}; // initialized to nullptrs
  people[0] = new Person("Giselle", "LeBrun", 'R', "Ms.");
  people[1] = new Person("Zack", "Moon", 'R', "Dr.");
  people[2] = new Person("Gabby", "Doone", 'A', "Dr.");

  // preferred looping style here:
  for (auto *individual : people)
    individual->Print();

  for (auto *individual : people)
    delete individual;

  // less desirable looping style
  /*
  for (int i = 0; i < MAX; i++)
     people[i]->Print();

  for (int i = 0; i < MAX; i++)
     delete people[i];
  */

  return 0;
}
