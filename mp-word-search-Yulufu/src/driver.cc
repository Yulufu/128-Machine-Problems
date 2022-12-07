#include <iostream>
#include <string>
#include <vector>

#include "WordSearchSolver.hpp"

int main() {
  std::vector<std::vector<char>> puzzle{{'d', 'h', 'b', 'b', 'n'},
                                        {'i', 'e', 'a', 'e', 'h'},
                                        {'d', 'b', 'l', 'o', 'm'},
                                        {'a', 'l', 't', 'a', 'a'},
                                        {'j', 'e', 't', 'o', 'b'}};
  // WordSearchSolver wss(puzzle);
  WordSearchSolver my_puzzle = WordSearchSolver(puzzle);
  std::cout << "Check Left Diag"
            << my_puzzle.FindWord("d", CheckDirection::kLeftDiag) << std::endl;
  std::cout << "Check Left Diag"
            << my_puzzle.FindWord("hi", CheckDirection::kLeftDiag)
            << std::endl;  // no output
  std::cout << "Check Left Diag"
            << my_puzzle.FindWord("bed", CheckDirection::kLeftDiag)
            << std::endl;
  std::cout << "Check Left Diag"
            << my_puzzle.FindWord("baba", CheckDirection::kLeftDiag)
            << std::endl;  // reached out of rage
  std::cout << "Check Left Diag"
            << my_puzzle.FindWord("hello", CheckDirection::kLeftDiag)
            << std::endl;
  std::cout << "Check Left Diag"
            << my_puzzle.FindWord("hote", CheckDirection::kLeftDiag)
            << std::endl;
  std::cout << "Check Left Diag"
            << my_puzzle.FindWord("mat", CheckDirection::kLeftDiag)
            << std::endl;
  std::cout << "Check Left Diag"
            << my_puzzle.FindWord("oa", CheckDirection::kLeftDiag) << std::endl;
  std::cout << "Check Left Diag"
            << my_puzzle.FindWord("b", CheckDirection::kLeftDiag) << std::endl;
  // -----------------------------------------------------------------------------
  // std::cout << my_puzzle.FindWord("hi");
  // std::cout << my_puzzle.FindWord("h", CheckDirection::kHorizontal);

  // std::cout << "Check Right Diag"
  //           << my_puzzle.FindWord("n", CheckDirection::kRightDiag) <<
  //           std::endl;
  // std::cout << "Check Right Diag"
  //           << my_puzzle.FindWord("bh", CheckDirection::kRightDiag)
  //           << std::endl;
  // std::cout << "Check Right Diag"
  //           << my_puzzle.FindWord("bem", CheckDirection::kRightDiag)
  //           << std::endl;
  // std::cout << "Check Right Diag"
  //           << my_puzzle.FindWord("haoa", CheckDirection::kRightDiag)
  //           << std::endl;
  // std::cout << "Check Right Diag"
  //           << my_puzzle.FindWord("delab", CheckDirection::kRightDiag)
  //           << std::endl;
  // std::cout << "Check Right Diag"
  //           << my_puzzle.FindWord("ibto", CheckDirection::kRightDiag)
  //           << std::endl;
  // std::cout << "Check Right Diag"
  //           << my_puzzle.FindWord("dlt", CheckDirection::kRightDiag)
  //           << std::endl;
  // std::cout << "Check Right Diag"
  //           << my_puzzle.FindWord("ae", CheckDirection::kRightDiag)
  //           << std::endl;
  // std::cout << "Check Right Diag"
  //           << my_puzzle.FindWord("j", CheckDirection::kRightDiag) <<
  //           std::endl;
}

// check for single char