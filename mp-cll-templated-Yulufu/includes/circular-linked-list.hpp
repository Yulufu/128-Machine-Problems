#ifndef CIRCULAR_LINKED_LIST_HPP
#define CIRCULAR_LINKED_LIST_HPP

#include <iostream>

#include "node.hpp"

enum class Order { kASC, kDESC };

template <typename T>
class CircularLinkedList {
public:
  CircularLinkedList() = default;
  CircularLinkedList(const CircularLinkedList<T>& source);
  CircularLinkedList<T>& operator=(const CircularLinkedList<T>& source);
  ~CircularLinkedList();

  void InsertInOrder(const T& data);
  void Reverse();
  void InsertInEmpty(const T& data);
  void InsertAtFront(const T& data);
  void Pushback(const T& data);
  void InsertInMiddleASC(Node<T>* curr, const T& data);
  void InsertInMiddleDESC(Node<T>* curr, const T& data);

  void OverTwoEle(Node<T>* curr, const T& data);
  void Clear();

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os,
                                  const CircularLinkedList<U>& cll);

private:
  Node<T>* head_ = nullptr;
  Node<T>* tail_ = nullptr;
  Order node_order_ = Order::kASC;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const CircularLinkedList<T>& cll) {
  Node<T>* iter = cll.head_;
  // empty list condition
  if (iter == nullptr) {
    os << "Empty list";
    return os;
  }
  // non-empty list condition
  do {
    os << iter->data << '\t';
    iter = iter->next;
  } while (iter != cll.head_);

  return os;
}

// Implementation

// make a pushback func to create a new list,
template <typename T>
CircularLinkedList<T>::CircularLinkedList(const CircularLinkedList<T>& source) {
  node_order_ = source.node_order_;
  if (this == &source) {  // check if source is already been copied
    return;
  }
  if (source.head_ == nullptr) {
    head_ = tail_ = nullptr;
    return;
  }
  if (source.head_ == source.tail_) {  // source has only 1 element
    head_ = new Node(source.head_->data);
    tail_ = head_;
    tail_->next = head_;
  } else if (source.head_->next == source.tail_) {  // 2 elements
    head_ = new Node(source.head_->data);
    head_->next = new Node(source.head_->next->data);
    tail_ = head_->next;
    tail_->next = head_;
  } else {
    head_ = new Node(source.head_->data);
    Node<T>* curr = head_->next;
    Node<T>* prev = head_;
    Node<T>* source_curr = source.head_;
    while (source_curr != source.tail_) {
      curr = new Node(source_curr->next->data);
      prev->next = curr;
      source_curr = source_curr->next;
      tail_ = curr;
      prev = prev->next;
      curr = curr->next;
    }
    tail_->next = head_;
  }
}

template <typename T>
CircularLinkedList<T>& CircularLinkedList<T>::operator=(
    const CircularLinkedList<T>& source) {
  if (this == &source) {
    return *this;
  }
  Clear();
  node_order_ = source.node_order_;
  if (source.head_ == nullptr) {
    head_ = tail_ = nullptr;
    return *this;
  }
  if (source.head_ == source.tail_) {  // source has only 1 element
    head_ = new Node(source.head_->data);
    tail_ = head_;
    tail_->next = head_;
  } else if (source.head_->next == source.tail_) {  // 2 elements
    head_ = new Node(source.head_->data);
    head_->next = new Node(source.head_->next->data);
    tail_ = head_->next;
    tail_->next = head_;
  } else {
    head_ = new Node(source.head_->data);
    Node<T>* curr = head_->next;
    Node<T>* prev = head_;
    Node<T>* source_curr = source.head_;
    while (source_curr != source.tail_) {
      curr = new Node(source_curr->next->data);
      prev->next = curr;
      source_curr = source_curr->next;
      tail_ = curr;
      prev = prev->next;
      curr = curr->next;
    }
    tail_->next = head_;
  }
  return *this;
}

template <typename T>
CircularLinkedList<T>::~CircularLinkedList() {
  Clear();
}
template <typename T>
void CircularLinkedList<T>::Clear() {
  if (head_ != nullptr) {
    while (tail_ != head_) {
      tail_->next = head_->next;
      delete head_;
      head_ = tail_->next;
    }
    if (tail_ == head_) {
      delete head_;
    }
  }
  head_ = nullptr;
  tail_ = nullptr;
}

template <typename T>
void CircularLinkedList<T>::InsertInEmpty(const T& data) {
  Node<T>* new_node = new Node(data);
  if (head_ == nullptr) {
    head_ = new_node;
    tail_ = new_node;
    tail_->next = new_node;
  }
}
template <typename T>
void CircularLinkedList<T>::InsertAtFront(const T& data) {
  // head probably not updating properly
  Node<T>* new_node = new Node(data);
  new_node->next = head_;
  head_ = new_node;
  tail_->next = new_node;
}
template <typename T>
void CircularLinkedList<T>::Pushback(const T& data) {
  Node<T>* new_node = new Node(data);
  tail_->next = new_node;
  tail_ = new_node;
  tail_->next = head_;
}
template <typename T>
void CircularLinkedList<T>::InsertInMiddleASC(Node<T>* curr, const T& data) {
  Node<T>* new_node = new Node(data);
  Node<T>* prev = nullptr;
  curr = head_;
  while (curr != tail_) {
    if (curr->data > data) {
      break;
    }
    prev = curr;
    curr = curr->next;
  }
  new_node->next = prev->next;
  prev->next = new_node;
  if (prev == tail_) {
    tail_ = new_node;
  }
}
template <typename T>
void CircularLinkedList<T>::InsertInMiddleDESC(Node<T>* curr, const T& data) {
  Node<T>* new_node = new Node(data);
  Node<T>* prev = nullptr;
  curr = head_;
  while (curr != tail_) {
    if (curr->data < data) {
      break;
    }
    prev = curr;
    curr = curr->next;
  }
  new_node->next = prev->next;
  prev->next = new_node;
  if (prev == tail_) {
    tail_ = new_node;
  }
}

template <typename T>
void CircularLinkedList<T>::InsertInOrder(const T& data) {
  // everytime call insert, curr reset to head_;
  Node<T>* curr = tail_;
  if (head_ == nullptr) {
    CircularLinkedList<T>::InsertInEmpty(data);
  } else if (head_ != nullptr) {
    if (head_ == tail_) {  // one element in list
      if (node_order_ == Order::kASC) {
        if (data < curr->data || data == curr->data) {
          CircularLinkedList<T>::InsertAtFront(data);
        }
        if (data > curr->data) {
          CircularLinkedList<T>::Pushback(data);
        }
      } else if (node_order_ == Order::kDESC) {
        if (data < curr->data || data == curr->data) {
          CircularLinkedList<T>::Pushback(data);
        }
        if (data > curr->data) {
          CircularLinkedList<T>::InsertAtFront(data);
        }
      }
    } else if (head_ != tail_) {  // >= 2 elements
      CircularLinkedList<T>::OverTwoEle(curr, data);
    }
  }
}
template <typename T>
void CircularLinkedList<T>::OverTwoEle(Node<T>* curr, const T& data) {
  if (node_order_ == Order::kASC) {
    if (data < head_->data) {
      CircularLinkedList<T>::InsertAtFront(data);
    } else if (data < tail_->data || data == curr->data) {
      CircularLinkedList<T>::InsertInMiddleASC(curr, data);
    }
    if (data > curr->data) {
      CircularLinkedList<T>::Pushback(data);
    }
  } else if (node_order_ == Order::kDESC) {
    if (data > head_->data) {
      CircularLinkedList<T>::InsertAtFront(data);
    } else if (data > tail_->data || data == curr->data) {
      CircularLinkedList<T>::InsertInMiddleDESC(curr, data);
    }
    if (data < curr->data) {
      CircularLinkedList<T>::Pushback(data);
    }
  }
}
template <typename T>
void CircularLinkedList<T>::Reverse() {
  if (head_ == nullptr) {
    if (node_order_ == Order::kASC) {
      node_order_ = Order::kDESC;
    } else if (node_order_ == Order::kDESC) {
      node_order_ = Order::kASC;
    }
    return;
  }
  Node<T>* prev = nullptr;
  Node<T>* curr = head_;
  Node<T>* next = nullptr;
  do {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  } while (curr != head_);
  head_->next = prev;
  head_ = prev;
  tail_ = curr;
  // both head & tail are same, tail not correct
  if (node_order_ == Order::kASC) {
    node_order_ = Order::kDESC;
  } else if (node_order_ == Order::kDESC) {
    node_order_ = Order::kASC;
  }
}

#endif