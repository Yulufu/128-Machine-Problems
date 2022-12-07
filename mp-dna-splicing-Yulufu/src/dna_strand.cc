#include "dna_strand.hpp"

#include <stdexcept>

#include "node.hpp"

void DNAstrand::CreateDNASequence(const char* enzymes) {
  size_t idx = 0;
  Node* prev = nullptr;
  Node* new_node = nullptr;
  while (enzymes[idx] != '\0') {
    new_node = new Node(enzymes[idx]);
    if (head_ == nullptr) {
      head_ = new_node;
    }
    if (prev != nullptr) {
      prev->next = new_node;
    }
    prev = new_node;
    idx++;
  }
  tail_ = new_node;
}

void DNAstrand::CheckContainPattern(const char* pattern,
                                    DNAstrand& to_splice_in) {
  Node* previous = nullptr;
  Node* current = head_;
  unsigned int pattern_size = 0;
  unsigned int count = 0;
  int lastest_match = -1;  // where the pattern begin
  int idx = 0;             // idx is the position of current
  Node* prev_node = nullptr;
  Node* after_pattern = nullptr;
  for (unsigned int i = 0; pattern[i] != '\0'; ++i) pattern_size += 1;
  while (current != nullptr) {
    if (current->data == pattern[0]) {
      count = 1;
      Node* runner = current->next;
      for (unsigned int i = 1; i < pattern_size; ++i) {
        if (runner == nullptr) {
          break;
        }
        if (pattern[i] == runner->data) {
          count += 1;
          runner = runner->next;
        } else if (pattern[i] != runner->data) {
          count = 0;
          break;
        }
      }
      if (count == pattern_size) {
        lastest_match = idx;
        prev_node = previous;    // previous is a nullptr
        after_pattern = runner;  // maybe runner
        count = 0;
      }
    }
    previous = current;
    current = current->next;
    idx++;
  }
  if (lastest_match == -1) throw std::runtime_error("no match");
  CallDeletePattern(head_, prev_node, after_pattern);
  InsertSpliceIn(to_splice_in, prev_node, after_pattern);
}
/*when call the DeleteNodesinPattern in CheckContainPattern, pass most memory
check except 1 & 2. However, all the single occurrence at the start stop
working*/
void DNAstrand::CallDeletePattern(Node* head_,
                                  Node* prev_node,
                                  Node* after_pattern) {
  if (prev_node == nullptr) {
    DeleteNodesinPatternAtStart(head_, after_pattern);
  } else {
    DeleteNodesinPattern(prev_node, after_pattern);
  }
}
void DNAstrand::DeleteNodesinPatternAtStart(Node* head_, Node* after_pattern) {
  Node* pattern_first_char = head_;
  while (pattern_first_char != after_pattern) {
    Node* node_temp = pattern_first_char->next;
    delete pattern_first_char;
    pattern_first_char = node_temp;
  }
}
void DNAstrand::DeleteNodesinPattern(Node* prev_node, Node* after_pattern) {
  Node* pattern_first_char = prev_node->next;
  while (pattern_first_char != after_pattern) {
    Node* node_temp = pattern_first_char->next;
    delete pattern_first_char;
    pattern_first_char = node_temp;
  }
}
void DNAstrand::InsertSpliceIn(DNAstrand& to_splice_in,
                               Node* prev_node,
                               Node* after_pattern) {
  Node* insert_head = to_splice_in.head_;
  Node* insert_tail = to_splice_in.tail_;
  // check at the start again
  if (prev_node == nullptr) {
    insert_tail->next = after_pattern;
    head_ = insert_head;
    if (tail_ == nullptr) {  // if insert is same size as original sequence
      tail_ = insert_tail;
    }
  } else {
    prev_node->next = insert_head;
    insert_tail->next = after_pattern;
    if (prev_node == tail_) {
      // case when this is the last node.
      tail_ = insert_tail;
    }
  }
}

void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
  for (unsigned int i = 0; pattern[i] != '\0'; ++i) {
    if (pattern[0] == '\0' || to_splice_in.head_ == nullptr) return;
  }
  // "this" is the original sequence
  if (&to_splice_in == this) return;
  CheckContainPattern(pattern, to_splice_in);
  to_splice_in.head_ = nullptr;
  to_splice_in.tail_ = nullptr;
}

DNAstrand::~DNAstrand() {
  while (head_ != nullptr) {
    Node* next = head_->next;
    delete head_;
    head_ = next;
  }
  head_ = nullptr;
  tail_ = nullptr;
}

// std::ostream& operator<<(std::ostream& os, const DNAstrand& sequence) {
//   Node* curr = sequence.head_;
//   while (curr != nullptr) {
//     os << curr->data << "->" << curr << std::endl;
//     curr = curr->next;
//   }
//   return os;
// }