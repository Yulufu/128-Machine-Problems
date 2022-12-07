#include <iostream>

#include "branched-linked-list.hpp"

// Asan -g -fsanitize=address,null -fno-omit-frame-pointer
// Valgrind valgrind ./bin/exec
int main() {
  /* EXAMPLE INTERACTIONS WITH BLL */
  BLL* first = new BLL();
  first->PushBack('c');
  first->PushBack('s');
  first->PushBack('8');

  //  BLL* copy = new BLL();
  // BLL* copy = first;
  // std::cout << "List 1: " << copy->ToString() << std::endl;
  // first->PushBack('h');
  // first->PushBack('e');
  // first->PushBack('l');
  // first->PushBack('l');
  // first->PushBack('o');
  // first->PushBack('?');
  std::cout << "List 1: " << first->ToString() << std::endl;  // hi //cs
  std::cout << "Size: " << first->Size() << std::endl;        // 2 /3
  // std::cout << "Char At Idx:" << first->GetAt(1) << std::endl;
  //  mastd::cout << first->GetAt(-1) << std::endl;  // exception
  //  first->SetAt(0, 'Y');
  //  first->SetAt(1, 'u');
  //  first->SetAt(2, 'l');  // out of bound
  //  std::cout << "List 1 changed: " << first->ToString() << std::endl;
  //   /////////////////////////////////////

  BLL* second = new BLL();
  second->PushBack('1');
  second->PushBack('2');
  // second->PushBack('8');

  // std::cout << "List 2: " << second->ToString() << std::endl;  // i!@
  // std::cout << "Size: " << second->Size() << std::endl;        // 3 / 2
  // std::cout << "At Idx: " << second->GetAt(1) << std::endl;
  // /////////////////////////////////////
  BLL* third = new BLL();
  third->PushBack('F');
  // third->PushBack('a');
  // third->PushBack('l');
  // third->PushBack('l');

  // std::cout << "List 3: " << third->ToString() << std::endl;  // fall
  // std::cout << "Size: " << third->Size() << std::endl;        // 4
  // std::cout << "At Idx: " << third->GetAt(3) << std::endl;
  //  /////////////////////////////////////

  first->Join(1, second);

  std::cout << "Joined lists: " << first->ToString() << std::endl;  // cs128
  std::cout << "Size: " << first->Size() << std::endl;              // 5

  /*
    std::cout << "List 2: " << second->ToString() << std::endl;  //  12
    std::cout << "Size: " << second->Size() << std::endl;        // 2
  */
  first->Join(3, third);
  std::cout << "Joined lists2: " << first->ToString() << std::endl;

  std::cout << "find location: " << first->FindIdx(4)->data_
            << std::endl;  // shound be 1

  std::cout << "Get location: " << first->GetAt(4) << std::endl;

  std::cout << "Size: " << first->Size() << std::endl;  // 6
  first->SetAt(4, 'S');
  std::cout << "Set At: " << first->ToString() << std::endl;
  // /////////////////////////////////////

  // BLL* first_construc(first);
  // std::cout << first_construc->ToString() << std::endl;
  BLL* first_clone = new BLL();
  *first_clone = *first;

  std::cout << first_clone->ToString() << std::endl;  // hii!@

  // BLL* second_clone = new BLL();
  // *second_clone = *second;

  // std::cout << second_clone->ToString() << std::endl;
  // std::cout << first_clone->Size() << std::endl; // 5

  return 0;
}

/*
1. Create a BLL object
2. do pushback func
3. Gets the data_ of idxth index starting from head_
4. Sets the data_ of idxth index starting from head_ to dat.
5. Join two BLL at the given idx
6. Check if the list is acyclic
7. use ToString() to print out what's in BLLs
*/