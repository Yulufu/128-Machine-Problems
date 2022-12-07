#include <iostream>

#include "circular-linked-list.hpp"

int main() {
  CircularLinkedList<int> newlist;
  const int kTestInt = 5;
  const int kTestIntPushBack = 7;
  const int kTestIntPushBack1 = 9;
  const int kTestIntAtFront = 4;
  const int kTestIntAtFront1 = 1;
  const int kTestIntEqualNum = 5;
  // const int kTestIntEqualNum1 = 7;

  // CircularLinkedList<char> newlist;
  // newlist.InsertInOrder('a');

  newlist.InsertInOrder(kTestInt);
  newlist.InsertInOrder(kTestIntPushBack);
  newlist.InsertInOrder(kTestIntPushBack1);
  newlist.InsertInOrder(kTestIntAtFront);
  newlist.InsertInOrder(kTestIntAtFront1);
  newlist.InsertInOrder(kTestIntEqualNum);

  newlist.Reverse();
  newlist.InsertInOrder(kTestIntAtFront);

  std::cout << "Original: " << newlist << std::endl;

  newlist.Reverse();
  std::cout << "Reverse 1st: " << newlist << std::endl;
  newlist.InsertInOrder(kTestIntAtFront);

  // std::cout << "Insert After Reverse: " << newlist << std::endl;

  // std::cout << "Reverse 2nd: " << newlist << std::endl;
  // newlist.InsertInOrder(kTestIntPushBack1);
  // std::cout << "Insert After Reverse:" << newlist << std::endl;
  // newlist.Reverse();
  // std::cout << "Reverse 3nd: " << newlist << std::endl;
  // newlist.InsertInOrder(kTestIntAtFront1);
  // newlist.InsertInOrder(kTestIntEqualNum);
  // std::cout << "Insert After Reverse: " << newlist << std::endl;
  // newlist.Reverse();
  // std::cout << "Reverse 4nd: " << newlist << std::endl;
  // newlist.InsertInOrder(kTestIntEqualNum1);
  // std::cout << "Insert After Reverse: " << newlist << std::endl;

  CircularLinkedList<int> copylist(newlist);
  std::cout << "Copy Linked LIst: " << copylist << std::endl;
  CircularLinkedList<int> copyassign;
  copyassign.operator=(newlist);
  std::cout << "Copy Assignment Linked LIst: " << copyassign << std::endl;
}

/*
1. create a circular linked list
2. implement copy constructor and copy assignment
3. implement destructor
4. do Insert in assending order or desending order
    a. when Empty list
    b. single node
    c. equal values
    d.Adding before head_ or after tail_
5. do Reverse
*/
/*
-g -fsanitize=address,null -fno-omit-frame-pointer
*/