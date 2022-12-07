#ifndef DNA_STRAND_HPP
#define DNA_STRAND_HPP

#include "node.hpp"

class DNAstrand {
public:
  DNAstrand() = default;
  DNAstrand(const DNAstrand& rhs) = delete;
  DNAstrand& operator=(const DNAstrand& rhs) = delete;
  ~DNAstrand();
  void SpliceIn(const char* pattern, DNAstrand& to_splice_in);
  void CreateDNASequence(const char* enzymes);
  void CheckContainPattern(const char* pattern, DNAstrand& to_splice_in);
  void InsertSpliceIn(DNAstrand& to_splice_in,
                      Node* prev_node,
                      Node* after_pattern);
  void DeleteNodesinPattern(Node* prev_node, Node* after_pattern);
  void DeleteNodesinPatternAtStart(Node* head_, Node* after_pattern);
  void CallDeletePattern(Node* head_, Node* prev_node, Node* after_pattern);
  // friend std::ostream& operator<<(std::ostream& os, const DNAstrand&
  // sequence);

private:
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
};

// have access to head_, tail_ of DNA sequence (which I will modify), but no
// need to make a new one
#endif