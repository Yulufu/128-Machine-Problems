#ifndef BRANCHED_LINKED_LIST_HPP
#define BRANCHED_LINKED_LIST_HPP

#include <cstddef>
#include <stdexcept>
#include <string>

#include "node.hpp"

class BLL {
public:
  BLL();
  BLL(const BLL& to_copy);
  ~BLL();

  BLL& operator=(const BLL& rhs);
  Node* PushBack(char dat);
  char GetAt(size_t idx) const;
  void SetAt(size_t idx, char dat);
  void Join(size_t idx, BLL* list);
  std::string ToString() const;
  size_t Size() const;

  // helpers
  Node* InsertAtEmpty(char dat);
  Node* InsertNotEmpty(char dat);
  Node* FindIdx(size_t idx) const;
  size_t CalculateSize(const BLL* bll) const;
  std::string PrintMultiLevel(std::string& printout, Node* curr) const;
  void Clear();

private:
  Node* head_ = nullptr;
  bool IsBLLAcyclic() const;
};

#endif
