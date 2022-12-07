#include "branched-linked-list.hpp"

#include <string>
BLL::BLL() = default;

BLL::BLL(const BLL& to_copy) {
  if (to_copy.head_ == nullptr) {
    head_ = nullptr;
    return;
  }
  Node* temp = new Node();
  Node* curr = temp;
  Node* copy_curr = to_copy.head_;
  while (copy_curr != nullptr) {
    curr->next_node_ = new Node(copy_curr->data_);
    if (copy_curr->next_bll_ != nullptr) {
      curr->next_node_->next_bll_ = new BLL(*copy_curr->next_bll_);
    }
    curr = curr->next_node_;
    copy_curr = copy_curr->next_node_;
  }
  head_ = temp->next_node_;
  delete temp;
}

BLL& BLL::operator=(const BLL& rhs) {
  if (this == &rhs) {
    return *this;
  }
  Clear();
  if (rhs.head_ == nullptr) {
    head_ = nullptr;
    return *this;
  }
  Node* temp = new Node();
  Node* curr = temp;
  Node* copy_curr = rhs.head_;
  while (copy_curr != nullptr) {
    curr->next_node_ = new Node(copy_curr->data_);
    if (copy_curr->next_bll_ != nullptr) {
      curr->next_node_->next_bll_ = new BLL(*copy_curr->next_bll_);
    }
    curr = curr->next_node_;
    copy_curr = copy_curr->next_node_;
  }
  head_ = temp->next_node_;
  delete temp;
  return *this;
}

BLL::~BLL() { Clear(); }

void BLL::Clear() {
  Node* curr = head_;
  Node* next = nullptr;
  while (curr != nullptr) {
    next = curr->next_node_;
    delete curr->next_bll_;
    delete curr;
    curr = next;
  }
  head_ = nullptr;
}
// -----------------Insert Node Func--------------------------
Node* BLL::InsertAtEmpty(char dat) {
  Node* new_node = new Node(dat);
  if (head_ == nullptr) {
    head_ = new_node;
    head_->next_node_ = nullptr;
  }
  return new_node;
}

Node* BLL::InsertNotEmpty(char dat) {
  Node* new_node = nullptr;
  Node* curr = head_;
  while (curr->next_node_ != nullptr) {
    curr = curr->next_node_;
  }
  new_node = curr->next_node_ = new Node(dat);
  return new_node;
}
Node* BLL::PushBack(char dat) {
  Node* new_node = nullptr;
  if (head_ == nullptr) {
    new_node = InsertAtEmpty(dat);
  } else {
    new_node = InsertNotEmpty(dat);
  }
  return new_node;
}
//---------------------Locate funcs-------------------------------
Node* BLL::FindIdx(size_t idx) const {
  Node* curr = head_;
  size_t count = -1;  // keep track of curr idx in list
  Node* look_for_node = nullptr;
  while (curr != nullptr) {
    count += 1;
    if (count == idx) {
      look_for_node = curr;
      break;
    }
    if (curr->next_bll_ != nullptr) {
      size_t next_bll_size = curr->next_bll_->Size();
      if (idx <= count + next_bll_size) {
        return curr->next_bll_->FindIdx(idx - (count + 1));
      }

      count = count + next_bll_size;
    }
    curr = curr->next_node_;
  }
  return look_for_node;
}
char BLL::GetAt(size_t idx) const {
  size_t size = Size();
  if (idx >= size || idx < 0) {
    throw std::invalid_argument("idx out of bound");
  }
  Node* look_for_node = FindIdx(idx);
  char char_at_idx = look_for_node->data_;

  return char_at_idx;
}

void BLL::SetAt(size_t idx, char dat) {
  size_t size = Size();
  if (idx >= size || idx < 0) {
    throw std::invalid_argument("idx out of bound");
  }
  FindIdx(idx)->data_ = dat;
}

void BLL::Join(size_t idx, BLL* list) {
  Node* locate_node = FindIdx(idx);
  locate_node->next_bll_ = list;
}

bool BLL::IsBLLAcyclic() const {
  bool is_cyclic = false;
  return is_cyclic;
}

std::string BLL::ToString() const {
  std::string printout;
  if (head_ == nullptr) {
    return printout;
  }
  Node* curr = head_;  // when do curr->next_bll_, curr = curr->next_bll_.head_
  while (curr != nullptr) {
    printout += curr->data_;
    if (curr->next_bll_ != nullptr) {
      printout += curr->next_bll_->ToString();
    }
    curr = curr->next_node_;
  }
  return printout;
}

size_t BLL::Size() const {
  size_t size = 0;
  size = CalculateSize(this);
  return size;
}

size_t BLL::CalculateSize(const BLL* bll) const {
  size_t size = 0;
  Node* curr = bll->head_;
  while (curr != nullptr) {
    if (curr->next_bll_ != nullptr) {
      size += CalculateSize(curr->next_bll_);
    }
    size++;
    curr = curr->next_node_;
  }
  return size;
}
