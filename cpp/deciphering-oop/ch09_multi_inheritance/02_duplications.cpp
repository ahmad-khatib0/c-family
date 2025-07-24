// Purpose: To illustrate how duplications can exist with multiple inheritance
// when two or more base classes of a class share a common ancestor class.
// In this example, two copies of a LifeForm sub-object will exist for each
// instance of a Centaur.

#include <iostream>

using std::cout;
using std::endl;
using std::string;

class LifeForm {
private:
  int lifeExpectancy = 0;

public:
  LifeForm() = default;
  LifeForm(int life) : lifeExpectancy(life) {}
  // We will use the default copy constructor, however, if we wanted to write the
  // copy constructor, this is what it would look like:
  // LifeForm(const LifeForm &form) : lifeExpectancy(form.lifeExpectancy) { }
  // OR
  // LifeForm(const LifeForm &form) { lifeExpectancy = form.lifeExpectancy; }
  virtual ~LifeForm() = default; // prototype necessary to specify virtual destructor
  [[nodiscard]] int GetLifeExpectancy() const { return lifeExpectancy; }

  // Virtual functions will (almost) never be inlined since their method must be
  // determined at run time using the v-table (except a few rare situations).
  virtual void Print() const = 0; // pure virtual functions specify the interface but
  virtual string IsA() const = 0; // most often do not specify a default behavior
  virtual string Speak() const = 0;
};

class Horse : public LifeForm {
private:
  string name;
  static constexpr int HORSE_LIFE = 35; // horse life expectancy

public:
  Horse() : LifeForm(HORSE_LIFE) {}
  Horse(const string &n);
  // Remember, it isn't necessary for us to prototype default copy constructor
  // Horse(const Horse &) = default;
  // Because base class destructor is virtual, ~Horse() is automatically virtual
  // (overridden) whether or not explicitly prototyped ~Horse() override = default;
  const string &GetName() const { return name; }
  void Print() const override;
  string IsA() const override;
  string Speak() const override;
};

Horse::Horse(const string &n) : LifeForm(HORSE_LIFE), name(n) {}

// We are using the default (system supplied) copy constructor, but if we wanted
// to write it, it would look like: Remember to prototype it if you define it yourself.
/* Horse::Horse(const Horse &h) : LifeForm (h), name(h.name) { } */

void Horse::Print() const { cout << name << endl; }
string Horse::IsA() const { return "Horse"; }
string Horse::Speak() const { return "Neigh!"; }

class Person : public LifeForm {
private:
  string firstName;
  string lastName;
  char middleInitial = '\0';
  string title;
  static constexpr int PERSON_LIFE = 80;

protected:
  void ModifyTitle(const string &); // Make this operation available to derived classes
public:
  Person();
  Person(const string &, const string &, char, const string &); // alternate constructor
  // Remember, default copy constructor prototype is not necessary
  // Person(const Person &) = default; copy constructor
  // Because base class destructor is virtual, ~Person() is automatically
  // virtual (overridden) whether or not explicitly prorotyped
  // ~Person() override = default;  // destructor

  // inline function definitions
  // firstName returned as ref to const string
  const string &GetFirstName() const { return firstName; }
  const string &GetLastName() const { return lastName; }
  const string &GetTitle() const { return title; }
  char GetMiddleInitial() const { return middleInitial; }

  // Virtual functions will (most often) not be inlined since their method must
  // be determined at run time using the v-table.
  void Print() const override;
  string IsA() const override;
  string Speak() const override;
};

Person::Person() : LifeForm(PERSON_LIFE) {}

Person::Person(const string &fn, const string &ln, char mi, const string &t)
    : LifeForm(PERSON_LIFE), firstName(fn), lastName(ln), middleInitial(mi), title(t)

{}

// We don't need to write the copy constructor ourselves (there are no ptr data members in class).
// If we did choose to do so, this is how it would look: Remember to prototype it if you
// define it yourself.
/*
Person::Person(const Person &p) : LifeForm(p), firstName(p.firstName),
lastName(p.lastName), middleInitial(p.middleInitial), title(p.title)
{ }
*/

void Person::ModifyTitle(const string &newTitle) { title = newTitle; }

void Person::Print() const {
  cout << title << " " << firstName << " ";
  cout << middleInitial << ". " << lastName << endl;
}

string Person::IsA() const { return "Person"; }
string Person::Speak() const { return "Hello!"; }

class Centaur : public Person, public Horse {
private:
public:
  Centaur() = default;
  Centaur(const string &, const string &, char = ' ', const string & = "Mythological Creature");
  // note default args in alt ctor
  // Let's show copy constructor so we can compare it to the next example
  Centaur(const Centaur &c) : Person(c), Horse(c) {} // same as default copy constructor
  // Because base classes destructors are virtual, ~Centaur() is automatically
  // virtual (overridden) whether or not explicitly prorotyped ~Centaur()
  // override = default;
  void Print() const override;
  string IsA() const override;
  string Speak() const override;
};

Centaur::Centaur(const string &fn, const string &ln, char mi, const string &title)
    : Person(fn, ln, mi, title), Horse(fn) {
  // All initialization has been taken care of in init. list
}

void Centaur::Print() const {
  // GetFirstName is defined in Person.  So is GetTitle()
  cout << "My name is " << GetFirstName();
  cout << ".  I am a " << GetTitle() << endl;
}

string Centaur::IsA() const { return "Centaur"; }

string Centaur::Speak() const { return "Neigh! and Hello!"; }

int main() {
  Centaur beast("Wild", "Man");
  cout << beast.Speak() << " I'm a " << beast.IsA() << endl;

  // Ambiguous member function invocation below!  Two paths exist to LifeForm::GetLifeExpectancy().
  // One via Horse and one via Person. Also, two copies of the LifeForm object exist--one
  // initialized the way Horse dictated, one initialized the way Person dictated.
  // Which of these two LifeForms are you asking to be the 'this' pointer?
  // cout << beast.GetLifeExpectancy();

  cout << "It is unclear how many years I will live: ";
  cout << beast.Person::GetLifeExpectancy();
  cout << " or ";
  cout << beast.Horse::GetLifeExpectancy() << endl;

  return 0;
}
