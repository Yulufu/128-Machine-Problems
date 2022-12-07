// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Michael R. Nowak                Environment : ubuntu:latest               //
//  Date ......: 2022/02/07                      Compiler ...: clang-10                    //
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

#include "board.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////
constexpr int kBoardWidth = 7;
constexpr int kBoardHeight = 6;

bool AreEqual(DiskType solution[][kBoardWidth],
              DiskType student[][kBoardWidth]) {
  for (int i = 0; i < kBoardHeight; ++i) {
    for (int j = 0; j < kBoardWidth; ++j) {
      if (solution[i][j] != student[i][j]) return false;
    }
  }
  return true;
}
void CopyBoard(DiskType source[Board::kBoardHeight][Board::kBoardWidth],
               Board& b) {
  for (int i = 0; i < Board::kBoardHeight; ++i) {
    for (int j = 0; j < Board::kBoardWidth; ++j) {
      b.board[i][j] = source[i][j];
    }
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Board initialization", "[board_init]") {
  // SECTION("Can use sections") {}
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE(AreEqual(solution, student.board));
  // clang-format off
}
TEST_CASE("Board Check Full", "[board_init]") {
DiskType source[kBoardHeight][kBoardWidth] = { 
   // SECTION("Can use sections") {}
  // clang-format off
  {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
  {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
  {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
  {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
  {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
  {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
};
  // clang-format on
  Board student;  // NOLINT
  CopyBoard(source, student);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 0),
                    std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer2, 1),
                    std::runtime_error);
}
TEST_CASE("Board Invalid Number", "[board_init]") {
  DiskType source[kBoardHeight][kBoardWidth] = {
      // SECTION("Can use sections") {}
      // clang-format off
  {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
  {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
  {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
  {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
  {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
  {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
};
  // clang-format on
  Board student;  // NOLINT
  CopyBoard(source, student);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 100),
                    std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, -100),
                    std::runtime_error);
}
TEST_CASE("Board Horizontal Winner Play1", "[board_init]") {
  DiskType source[kBoardHeight][kBoardWidth] = {
      // SECTION("Can use sections") {}
      // clang-format off
  {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  Board student;  // NOLINT
  CopyBoard(source, student);
 REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kRightDiag));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kRightDiag));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kHorizontal));      
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kVertical));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kVertical));
REQUIRE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kHorizontal));
  // clang-format on
}
TEST_CASE("Board Horizontal Winner Play1 Comp", "[board_init]") {
  DiskType source[kBoardHeight][kBoardWidth] = {
      // SECTION("Can use sections") {}
      // clang-format off
  {DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1}, 
    {DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  Board student;  // NOLINT
  CopyBoard(source, student);
 REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kRightDiag));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kRightDiag));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kHorizontal));      
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kVertical));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kVertical));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kHorizontal));
  // clang-format on
}
TEST_CASE("Board Horizontal Winner Play1 Comp2", "[board_init]") {
  DiskType source[kBoardHeight][kBoardWidth] = {
      // SECTION("Can use sections") {}
      // clang-format off
  {DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer1}, 
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  Board student;  // NOLINT
  CopyBoard(source, student);
 REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kRightDiag));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kRightDiag));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kHorizontal));      
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kVertical));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kVertical));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kHorizontal));
  // clang-format on
}
TEST_CASE("Board Horizontal Winner Play1 Comp3", "[board_init]") {
  DiskType source[kBoardHeight][kBoardWidth] = {
      // SECTION("Can use sections") {}
      // clang-format off
  {DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1}, 
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  Board student;  // NOLINT
  CopyBoard(source, student);
 REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kRightDiag));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kRightDiag));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kHorizontal));      
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kVertical));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kVertical));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kHorizontal));
  // clang-format on
}
TEST_CASE("Board Horizontal Winner Play2", "[board_init]") {
  DiskType source[kBoardHeight][kBoardWidth] = {
      // SECTION("Can use sections") {}
      // clang-format off
  {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  Board student;  // NOLINT
  CopyBoard(source, student);
 REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kRightDiag));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kRightDiag));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kHorizontal));      
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kVertical));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kVertical));
REQUIRE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kHorizontal));
  // clang-format on
}
TEST_CASE("Board Vertical Winner Play1", "[board_init]") {
  DiskType source[kBoardHeight][kBoardWidth] = {
      // SECTION("Can use sections") {}
      // clang-format off
  {DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  Board student;  // NOLINT
  CopyBoard(source, student);
 REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kRightDiag));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kRightDiag));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kHorizontal));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kHorizontal));      
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kVertical));
REQUIRE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kVertical));
  // clang-format on
}
TEST_CASE("Board Vertical Winner Play2", "[board_init]") {
  DiskType source[kBoardHeight][kBoardWidth] = {
      // SECTION("Can use sections") {}
      // clang-format off
  {DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  Board student;  // NOLINT
  CopyBoard(source, student);
 REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kRightDiag));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kRightDiag));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kHorizontal));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kHorizontal));      
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kVertical));
REQUIRE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kVertical));
  // clang-format on
}
TEST_CASE("Board RightDiag Winner Play1", "[board_init]") {
  DiskType source[kBoardHeight][kBoardWidth] = {
      // SECTION("Can use sections") {}
      // clang-format off
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  }; //1st row is bottom row
  Board student;  // NOLINT
  CopyBoard(source, student);

REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kRightDiag));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kHorizontal));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kHorizontal));      
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kVertical));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kVertical));
REQUIRE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kRightDiag));
  // clang-format on
}
TEST_CASE("Board RightDiag Winner Play2", "[board_init]") {
  DiskType source[kBoardHeight][kBoardWidth] = {
      // SECTION("Can use sections") {}
      // clang-format off
     {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };//1st row is bottom row
  Board student;  // NOLINT
  CopyBoard(source, student);

REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kRightDiag));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kHorizontal));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kHorizontal));      
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kVertical));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kVertical));
REQUIRE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kRightDiag));
  // clang-format on
}
TEST_CASE("Board LeftDiag Winner Play1", "[board_init]") {
  DiskType source[kBoardHeight][kBoardWidth] = {
      // SECTION("Can use sections") {}
      // clang-format off
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  }; //1st row is bottom row
  Board student;  // NOLINT
  CopyBoard(source, student);
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kRightDiag));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kRightDiag));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kHorizontal));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kHorizontal));      
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kVertical));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kVertical));
REQUIRE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  // clang-format on
}
TEST_CASE("Board LeftDiag Winner Play2", "[board_init]") {
  DiskType source[kBoardHeight][kBoardWidth] = {
      // SECTION("Can use sections") {}
      // clang-format off
{DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  }; //1st row is bottom row
  Board student;  // NOLINT
  CopyBoard(source, student);
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kRightDiag));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kRightDiag));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kHorizontal));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kHorizontal));      
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kVertical));
REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kVertical));
REQUIRE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  // clang-format on
}
TEST_CASE("Board Location In Bound", "[board_init]") {
  DiskType source[kBoardHeight][kBoardWidth] = {
      // clang-format off
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer2}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  }; //1st row is bottom row
  Board student;  // NOLINT
  CopyBoard(source, student);
REQUIRE_FALSE(BoardLocationInBounds(-100, -100));
REQUIRE_FALSE(BoardLocationInBounds(-100, 100));
REQUIRE_FALSE(BoardLocationInBounds(100, 100));
REQUIRE_FALSE(BoardLocationInBounds(100, -100));
REQUIRE_FALSE(BoardLocationInBounds(kBoardHeight - 10, kBoardWidth - 10));
REQUIRE_FALSE(BoardLocationInBounds(kBoardHeight + 10, kBoardWidth + 10));
//check require in bound 
REQUIRE(BoardLocationInBounds(kBoardHeight - 1, kBoardWidth - 1));
  //  clang-format on
}
TEST_CASE("Board No Winner", "[board_init]") {
  DiskType source[kBoardHeight][kBoardWidth] = {
      // SECTION("Can use sections") {}
      // clang-format off
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2}, 
    {DiskType::kPlayer2, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  }; //1st row is bottom row
  Board student;  // NOLINT
  CopyBoard(source, student);
REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  // clang-format on
}
TEST_CASE("Board Floating disk", "[board_init]") {
  DiskType source[kBoardHeight][kBoardWidth] = {
      // SECTION("Can use sections") {}
      // clang-format off
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  }; //1st row is bottom row
  Board student;  // NOLINT
  CopyBoard(source, student);
REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  // clang-format on
}
TEST_CASE("Board Useless threat", "[board_init]") {
  DiskType source[kBoardHeight][kBoardWidth] = {
      // SECTION("Can use sections") {}
      // clang-format off
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  }; //1st row is bottom row
  Board student;  // NOLINT
  CopyBoard(source, student);
REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  // clang-format on
}
TEST_CASE("Board Empty disk out of bound", "[board_init]") {
  DiskType source[kBoardHeight][kBoardWidth] = {
      // SECTION("Can use sections") {}
      // clang-format off
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  }; //1st row is bottom row
  Board student;  // NOLINT
  CopyBoard(source, student);
REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer2, 10), std::runtime_error);
  // clang-format on
}
/////////////////////////////////////////////////////////////////////////////////////////////