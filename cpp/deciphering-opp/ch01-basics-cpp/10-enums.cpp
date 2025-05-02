#include <iostream>

using std::cout;
using std::endl;
using std::string;

// traditional enumerated types
enum day { Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday };
enum workDay { Mon = 1, Tues, Wed, Thurs, Fri };

// strongly typed enums default to int, but can be any integral type:
// int, char, short int, long int, bool

// strongly-typed enumerated types can be a struct or class
//
enum struct WinterHoliday {
  Diwali,
  Hanukkah,
  ThreeKings,
  WinterSolstice,
  StLucia,
  StNicholas,
  Christmas,
  Kwanzaa
};

enum class Holiday : short int {
  NewYear = 1,
  MLK,
  Memorial,
  Independence,
  Labor,
  Thanksgiving
};

int main() {
  day birthday = Monday;
  workDay payday = Fri;

  WinterHoliday myTradition = WinterHoliday::StNicholas;
  Holiday favorite = Holiday::NewYear;

  cout << "Birthday is " << birthday << endl;
  cout << "Payday is " << payday << endl;

  // we are casting because the insertion operator knows how to handle selected
  // types, but these types do not include strongly-typed enums; therefore, we
  // cast our enumerated type to a type understood by the insertion operator.
  cout << "Traditional Winter holiday is " << static_cast<int>(myTradition)
       << endl;
  cout << "Favorite holiday is " << static_cast<short int>(favorite) << endl;

  return 0;
}
