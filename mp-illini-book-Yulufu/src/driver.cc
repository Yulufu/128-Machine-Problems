#include <iostream>
#include <vector>

#include "illini_book.hpp"

int main() {
  IlliniBook mybook(
      "/home/vagrant/src/MPs/mp-illini-book-Yulufu/example/persons.csv",
      "/home/vagrant/src/MPs/mp-illini-book-Yulufu/example/relations.csv");

  // std::cout << mybook.AreRelated(1, 2) << std::endl;         // true
  // std::cout << mybook.AreRelated(3, 2) << std::endl;         // true
  // std::cout << mybook.AreRelated(1, 9) << std::endl;         // false
  // std::cout << mybook.AreRelated(1, 2, "128") << std::endl;  // true
  // std::cout << mybook.AreRelated(1, 2, "124") << std::endl;  // false
  // std::cout << mybook.AreRelated(1, 6, "128") << std::endl;  // true
  // std::cout << mybook.AreRelated(1, 6, "124") << std::endl;  // true

  // std::cout << mybook.GetRelated(1, 1) << std::endl;  // 0
  // std::cout << mybook.GetRelated(1, 2) << std::endl;  // 1
  // std::cout << mybook.GetRelated(3, 2) << std::endl;  // 2
  // std::cout << mybook.GetRelated(1, 8) << std::endl;  // 2
  // std::cout << mybook.GetRelated(7, 6) << std::endl;  // 3
  // std::cout << mybook.GetRelated(7, 8) << std::endl;  // 4
  // std::cout << mybook.GetRelated(1, 9) << std::endl;  //-1

  // std::cout << mybook.GetRelated(1, 2, "128") << std::endl;  // 1
  // std::cout << mybook.GetRelated(1, 2, "124") << std::endl;  // -1
  // std::cout << mybook.GetRelated(1, 6, "128") << std::endl;  // 2
  // std::cout << mybook.GetRelated(1, 6, "124") << std::endl;  // 1

  // std::vector<int> n_steps_away =
  //     // mybook.GetSteps(1, 1);  // { 2, 3, 6 }*
  //     // mybook.GetSteps(1, 2);  //	{ 7, 8 }*
  //     // mybook.GetSteps(1, 3);  //{ }
  //     // mybook.GetSteps(9, 1);  //{ }
  //     // mybook.GetSteps(15, 1);  //{11,13 }
  //     mybook.GetSteps(9, 0);
  // for (size_t i = 0; i < n_steps_away.size(); ++i) {
  //   std::cout << n_steps_away.at(i) << std::endl;
  // }
  // std::cout << mybook.CountGroups() << std::endl;       // 3
  // std::cout << mybook.CountGroups("128") << std::endl;  // 6
  // std::cout << mybook.CountGroups("124") << std::endl;  // 6
  // std::cout << mybook.CountGroups("173") << std::endl;  // 10
  std::cout << mybook.CountGroups(std::vector<std::string>{"128", "173"})
            << std::endl;  // 6
  std::cout << mybook.CountGroups(std::vector<std::string>{"128", "124", "173"})
            << std::endl;  // 3

  return 0;
}
