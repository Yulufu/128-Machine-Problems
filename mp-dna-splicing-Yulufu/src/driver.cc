#include <iostream>

#include "dna_strand.hpp"

int main() {
  DNAstrand sequence;
  // sequence.CreateDNASequence("tacba");
  // sequence.CreateDNASequence("ctata");
  sequence.CreateDNASequence("abdbc");
  // sequence.CreateDNASequence("ctgaattcg");
  std::cout << "Original sequence" << std::endl;
  // std::cout << sequence << std::endl;
  //  const char* pattern = "ta";
  //   const char* pattern = "taaa";
  //   const char* pattern = "ab";
  const char* pattern = "abd";
  DNAstrand to_splice_in;
  to_splice_in.CreateDNASequence("z");
  // std::cout << to_splice_in << std::endl;
  sequence.SpliceIn(pattern, to_splice_in);

  std::cout << "After splice sequence" << std::endl;
  // std::cout << sequence << std::endl;
}

/*
1. create a  DNAstrand sequence;
2. Compared with pattern
    a. if there isn't a match, throw an exception
    b. if pattern and or to_splice_in is empty, return directly
    c. if to_splice_in is invoking SpliceIn (&to_splice_in == this), return
directly
    d. if match:
      1) find the pattern that's closer to the tail
        a) start checking when find the first same char
        b) if find the pattern, continue to check
      2) replace the pattern with to_splice_in
      3) delete the pattern that was in sequence

*/

//-g -fsanitize=address,null -fno-omit-frame-pointer