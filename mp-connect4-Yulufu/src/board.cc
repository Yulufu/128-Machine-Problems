#include "board.hpp"

// you might need additional includes
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

/**************************************************************************/
/* your function definitions                                              */
/**************************************************************************/

void InitBoard(Board& b) {
  // below was minimal to get tests to actually compile and given test case to
  // fail
  // b.board[0][0] = DiskType::kEmpty;
  // this only said the first cell is empty need to make all the cells empty
  for (int i = 0; i < Board::kBoardHeight; ++i) {
    for (int j = 0; j < Board::kBoardWidth; ++j) {
      b.board[i][j] = DiskType::kEmpty;
    }
  }
}

/**************************************************************************/
/* provided to you                                                        */
/**************************************************************************/
std::string BoardToStr(const Board& b) {
  constexpr int kTotalWidth = Board::kBoardWidth * 11 - Board::kBoardHeight - 1;
  std::stringstream ss;
  ss << std::endl;
  for (int row = Board::kBoardHeight; row > 0; --row) {
    ss << " |";
    for (int col = 0; col < Board::kBoardWidth; ++col) {
      std::string value_here;
      value_here.push_back(static_cast<char>(b.board[row - 1][col]));
      ss << ' ' << CenterStr(value_here, Board::kBoardWidth + 1) << '|';
    }
    ss << std::endl;
    ss << " |" << std::setw(kTotalWidth) << std::setfill('-') << '|'
       << std::endl;
  }
  ss << " |";
  for (int col = 0; col < Board::kBoardWidth; ++col) {
    ss << ' ' << CenterStr(std::to_string(col), Board::kBoardWidth + 1) << '|';
  }
  return ss.str();
}

std::string CenterStr(const std::string& str, int col_width) {
  // quick and easy (but error-prone) implementation
  auto padl = (col_width - str.length()) / 2;
  auto padr = (col_width - str.length()) - padl;
  std::string strf = std::string(padl, ' ') + str + std::string(padr, ' ');
  return strf;
}

void DropDiskToBoard(Board& b, DiskType disk, int col) {
  if (col < 0 || col >= Board::kBoardWidth) {
    throw std::runtime_error("Invalid col number");
  }
  for (int i = 0; i < Board::kBoardHeight; ++i) {
    if (b.board[i][col] == DiskType::kEmpty) {
      b.board[i][col] = disk;
      break;
    }
    if (b.board[i][col] == b.board[Board::kBoardHeight - 1][col]) {
      throw std::runtime_error("column is full");
    }
  }
}
bool CheckForWinner(Board& b, DiskType disk) {
  if (SearchForWinner(b, disk, WinningDirection::kHorizontal)) {
    return true;
  }
  if (SearchForWinner(b, disk, WinningDirection::kVertical)) {
    return true;
  }
  if (SearchForWinner(b, disk, WinningDirection::kRightDiag)) {
    return true;
  }
  if (SearchForWinner(b, disk, WinningDirection::kLeftDiag)) {
    return true;
  }
  return false;
}
bool SearchForWinner(Board& b, DiskType disk, WinningDirection to_check) {
  for (int i = Board::kBoardHeight - 1; i >= 0; --i) {
    for (int j = Board::kBoardWidth - 1; j >= 0; --j) {
      if (WinningDirection::kHorizontal == to_check && (j - 3) >= 0) {
        if (b.board[i][j] == disk && b.board[i][j - 1] == disk &&
            b.board[i][j - 2] == disk && b.board[i][j - 3] == disk) {
          return true;
        }
      }
      if (WinningDirection::kVertical == to_check && (i - 3) >= 0) {
        if (b.board[i][j] == disk && b.board[i - 1][j] == disk &&
            b.board[i - 2][j] == disk && b.board[i - 3][j] == disk) {
          return true;
        }
      }
      if (WinningDirection::kRightDiag == to_check && (i - 3) >= 0 &&
          (j - 3) >= 0) {
        if (b.board[i][j] == disk && b.board[i - 1][j - 1] == disk &&
            b.board[i - 2][j - 2] == disk && b.board[i - 3][j - 3] == disk) {
          return true;
        }
      }
      if (WinningDirection::kLeftDiag == to_check && (i - 3) >= 0 &&
          (j - 3) >= 0) {
        if (b.board[i][j - 3] == disk && b.board[i - 1][j - 2] == disk &&
            b.board[i - 2][j - 1] == disk && b.board[i - 3][j] == disk) {
          return true;
        }
      }
    }
  }
  return false;
}

bool BoardLocationInBounds(int row, int col) {
  return row >= 0 && row < Board::kBoardHeight && col >= 0 &&
         col < Board::kBoardWidth;
}


void resizeRows(int num_rows) {
        // if the new row count is smaller 
        // remove the previous elements
        // if the new row count is larger
        // fill them with 0s
        // if new row count < 1
        // output error message
        if (num_rows < 1) {
            std::cout << "Error: new row count must be greater than 0" << std::endl;
            return;
        }
        if (num_rows < rows) {
            for (int i = num_rows; i < rows; i++) {
                delete[] matrix[i];
            }
        } else if (num_rows > rows) {
            int **new_matrix = new int*[num_rows];
            for (int i = 0; i < num_rows; i++) {
                new_matrix[i] = new int[cols];
            }
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    new_matrix[i][j] = matrix[i][j];
                }
            }
            for (int i = rows; i < num_rows; i++) {
                for (int j = 0; j < cols; j++) {
                    new_matrix[i][j] = 0;
                }
            }
            for (int i = 0; i < rows; i++) {
                delete[] matrix[i];
            }
            delete[] matrix;
            matrix = new_matrix;

            // update the row count
            this->rows = num_rows;
        }
    }