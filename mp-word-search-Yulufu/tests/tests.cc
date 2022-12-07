// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Student Name                    Environment : ubuntu:bionic               //
//  Date ......: 2021/02/10                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>
#include <vector>

#include "CharPositions.hpp"
#include "WordLocation.hpp"
#include "WordSearchSolver.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

bool IsRectangel(std::vector<std::vector<char>> puzzle) {
  for (size_t height = 0; height < puzzle.size(); ++height) {
    for (size_t width = 0; width < puzzle.at(height).size(); ++width) {
      if (height == width) {
        return true;
      }
    }
  }
  return false;
}
// void ValidHightWidth(std::vector<std::vector<char>> puzzle) {
//   for (size_t height = 0; height < puzzle.size(); ++height) {
//     for (size_t width = 0; width < puzzle.at(height).size(); ++width) {
//     }
//   }
// }
/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("True == True", "") { REQUIRE(true == true); }
TEST_CASE("Puzzle Initialization is a Rectangle", "[puzzle_init]") {
  std::vector<std::vector<char>> puzzle = {{'d', 'e', 'a', 'l', 'l'},
                                           {'h', 'l', 'l', 'l', 'o'},
                                           {'c', 'a', 'l', 'o', 'm'},
                                           {'a', 'e', 't', 'a', 'u'},
                                           {'a', 'e', 't', 'o', 'u'}};
  REQUIRE(IsRectangel(puzzle));
  REQUIRE(puzzle.size() >= 0);
  // work on have test case to initialze the puzzle
  // check if it's rectangle
  // check if hight, width >= 0
}

TEST_CASE("Puzzle Find Horizontal word", "[puzzle_init]") {
  std::vector<std::vector<char>> puzzle = {{'d', 'e', 'a', 'l', 'l'},
                                           {'h', 'l', 'l', 'l', 'o'},
                                           {'c', 'a', 'b', 'o', 'm'},
                                           {'a', 'e', 't', 'a', 'u'},
                                           {'a', 'e', 't', 'o', 'u'}};
  WordSearchSolver horizontal_puzzle = WordSearchSolver(puzzle);
  WordLocation myword =
      horizontal_puzzle.FindWord("all", CheckDirection::kHorizontal);
  WordLocation myword1 =
      horizontal_puzzle.FindWord("all", CheckDirection::kVertical);
  REQUIRE(myword.word == "all");
  WordLocation myword2 =
      horizontal_puzzle.FindWord("all", CheckDirection::kLeftDiag);
  WordLocation myword3 =
      horizontal_puzzle.FindWord("all", CheckDirection::kRightDiag);
  REQUIRE(myword.word == "all");
  REQUIRE_FALSE(myword.word != "all");
  REQUIRE_FALSE(myword1.word == "all");
  REQUIRE_FALSE(myword2.word == "all");
  REQUIRE_FALSE(myword3.word == "all");
}
TEST_CASE("Puzzle Find Horizontal word at different line", "[puzzle_init]") {
  std::vector<std::vector<char>> puzzle = {{'d', 'e', 'a', 'l', 'l'},
                                           {'h', 'l', 'l', 'l', 'o'},
                                           {'c', 'a', 'l', 'o', 'm'},
                                           {'a', 'e', 't', 'c', 'a'},
                                           {'t', 'e', 't', 'o', 'u'}};
  WordSearchSolver horizontal_puzzle = WordSearchSolver(puzzle);
  WordLocation myword =
      horizontal_puzzle.FindWord("cat", CheckDirection::kHorizontal);
  REQUIRE_FALSE(myword.word == "cat");
}
TEST_CASE("Puzzle Find Horizontal word reverse", "[puzzle_init]") {
  std::vector<std::vector<char>> puzzle = {{'d', 'e', 'a', 'l', 'l'},
                                           {'h', 'l', 'l', 'l', 'o'},
                                           {'c', 'a', 'l', 'o', 'm'},
                                           {'a', 'e', 't', 'a', 'c'},
                                           {'t', 'e', 't', 'o', 'u'}};
  WordSearchSolver horizontal_puzzle = WordSearchSolver(puzzle);
  WordLocation myword =
      horizontal_puzzle.FindWord("cat", CheckDirection::kHorizontal);
  REQUIRE_FALSE(myword.word == "cat");
}
TEST_CASE("Puzzle Find Vertical word", "[puzzle_init]") {
  std::vector<std::vector<char>> puzzle = {{'d', 'e', 'a', 'b', 'e'},
                                           {'h', 'l', 'l', 'l', 'o'},
                                           {'c', 'a', 'l', 'o', 'm'},
                                           {'a', 'e', 't', 'a', 'u'},
                                           {'a', 'e', 't', 'o', 'u'}};
  WordSearchSolver my_puzzle = WordSearchSolver(puzzle);
  WordLocation myword = my_puzzle.FindWord("all", CheckDirection::kHorizontal);
  WordLocation myword1 = my_puzzle.FindWord("all", CheckDirection::kVertical);
  WordLocation myword2 = my_puzzle.FindWord("all", CheckDirection::kLeftDiag);
  WordLocation myword3 = my_puzzle.FindWord("all", CheckDirection::kRightDiag);
  REQUIRE_FALSE(myword.word == "all");
  REQUIRE_FALSE(myword1.word != "all");
  REQUIRE(myword1.word == "all");
  REQUIRE_FALSE(myword2.word == "all");
  REQUIRE_FALSE(myword3.word == "all");
}
TEST_CASE("Puzzle Find Vertical word not at same line", "[puzzle_init]") {
  std::vector<std::vector<char>> puzzle = {{'d', 'e', 'a', 'l', 'e'},
                                           {'h', 'l', 'e', 'l', 'o'},
                                           {'c', 'a', 'e', 'o', 'm'},
                                           {'a', 'e', 'a', 'a', 'u'},
                                           {'a', 'e', 'l', 'o', 'u'}};
  WordSearchSolver vertical_puzzle = WordSearchSolver(puzzle);
  WordLocation myword =
      vertical_puzzle.FindWord("all", CheckDirection::kVertical);
  REQUIRE_FALSE(myword.word == "all");
}
TEST_CASE("Puzzle Find Vertical word reverse", "[puzzle_init]") {
  std::vector<std::vector<char>> puzzle = {{'d', 'e', 'l', 'b', 'l'},
                                           {'h', 'l', 'l', 'b', 'o'},
                                           {'c', 'b', 'a', 'o', 'm'},
                                           {'a', 'e', 't', 'a', 'c'},
                                           {'t', 'e', 't', 'o', 'u'}};
  WordSearchSolver vertical_puzzle = WordSearchSolver(puzzle);
  WordLocation myword =
      vertical_puzzle.FindWord("all", CheckDirection::kVertical);
  REQUIRE_FALSE(myword.word == "all");
}
TEST_CASE("Puzzle Find LefDiag word", "[puzzle_init]") {
  std::vector<std::vector<char>> puzzle = {{'d', 'e', 'b', 'b', 'a'},
                                           {'h', 'l', 'l', 'l', 'o'},
                                           {'l', 'a', 'l', 'o', 'a'},
                                           {'a', 'e', 't', 'l', 'u'},
                                           {'a', 'e', 'l', 'o', 'u'}};
  WordSearchSolver my_puzzle = WordSearchSolver(puzzle);
  WordLocation myword = my_puzzle.FindWord("all", CheckDirection::kHorizontal);
  WordLocation myword1 = my_puzzle.FindWord("all", CheckDirection::kVertical);
  WordLocation myword2 = my_puzzle.FindWord("all", CheckDirection::kLeftDiag);
  WordLocation myword3 = my_puzzle.FindWord("all", CheckDirection::kRightDiag);
  REQUIRE_FALSE(myword.word == "all");
  REQUIRE_FALSE(myword2.word != "all");
  REQUIRE_FALSE(myword1.word == "all");
  REQUIRE(myword2.word == "all");
  REQUIRE_FALSE(myword3.word == "all");
}
TEST_CASE("Puzzle Find LefDiag word not on same line", "[puzzle_init]") {
  std::vector<std::vector<char>> puzzle = {{'d', 'a', 'b', 'b', 'b'},
                                           {'l', 'b', 'b', 'b', 'o'},
                                           {'e', 'a', 'l', 'o', 'l'},
                                           {'a', 'e', 't', 'a', 'u'},
                                           {'a', 'e', 't', 'o', 'u'}};
  WordSearchSolver leftdiag_puzzle = WordSearchSolver(puzzle);
  WordLocation myword =
      leftdiag_puzzle.FindWord("all", CheckDirection::kLeftDiag);
  REQUIRE_FALSE(myword.word == "all");
}

TEST_CASE("Puzzle Find RightDiag word", "[puzzle_init]") {
  std::vector<std::vector<char>> puzzle = {{'d', 'e', 'a', 'o', 'u'},
                                           {'a', 'e', 'l', 'l', 'o'},
                                           {'c', 'l', 'b', 'o', 'm'},
                                           {'a', 'e', 'l', 'a', 'u'},
                                           {'t', 'e', 't', 'o', 'u'}};
  WordSearchSolver my_puzzle = WordSearchSolver(puzzle);
  WordLocation myword = my_puzzle.FindWord("all", CheckDirection::kHorizontal);
  WordLocation myword1 = my_puzzle.FindWord("all", CheckDirection::kVertical);
  WordLocation myword2 = my_puzzle.FindWord("all", CheckDirection::kLeftDiag);
  WordLocation myword3 = my_puzzle.FindWord("all", CheckDirection::kRightDiag);
  REQUIRE_FALSE(myword.word == "all");
  REQUIRE_FALSE(myword3.word != "all");
  REQUIRE_FALSE(myword1.word == "all");
  REQUIRE_FALSE(myword2.word == "all");
  REQUIRE(myword3.word == "all");
}
TEST_CASE("Puzzle Find RightDiag word not on the same line", "[puzzle_init]") {
  std::vector<std::vector<char>> puzzle = {{'d', 'e', 'a', 'o', 'u'},
                                           {'b', 'e', 'l', 'l', 'o'},
                                           {'c', 'c', 'l', 'h', 'm'},
                                           {'a', 'e', 't', 'a', 'a'},
                                           {'t', 'e', 't', 'o', 'u'}};
  WordSearchSolver rightdiag_puzzle = WordSearchSolver(puzzle);
  WordLocation myword =
      rightdiag_puzzle.FindWord("hat", CheckDirection::kRightDiag);
  REQUIRE_FALSE(myword.word == "hat");
}

// testcase for only one character
/////////////////////////////////////////////////////////////////////////////////////////////