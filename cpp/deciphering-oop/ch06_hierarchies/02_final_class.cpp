#include "01_single_inheritance.cpp"

/// (unextendible) class or leaf-node.
///
/// GradStudent Is-A final derived class of Student:
class GradStudent final : public Person {
  // class definition
};

//
// error: GradStudent is marked as final
// class NotAllowed : public GradStudent { };
//
