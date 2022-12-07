#include "WordSearchSolver.hpp"

#include <cstddef>
#include <iostream>
#include <limits>
#include <vector>

bool WordSearchSolver::LocationInBounds(size_t row, size_t col) const {
  return ((row < puzzle_height_) && (col < puzzle_width_));
}
// initialize the puzzle
WordSearchSolver::WordSearchSolver(
    const std::vector<std::vector<char>>& puzzle):
    puzzle_(puzzle),
    puzzle_height_(puzzle.size()),
    puzzle_width_(puzzle.at(0).size()) {
  if (puzzle_height_ < 0 || puzzle_width_ < 0) {
    throw std::invalid_argument("Invalid puzzle");
  }
}

WordLocation WordSearchSolver::FindWord(const std::string& word) {
  WordLocation founded_word =
      WordSearchSolver::FindWord(word, CheckDirection::kHorizontal);
  if (founded_word.word == word) {
    return founded_word;
  }
  founded_word = WordSearchSolver::FindWord(word, CheckDirection::kVertical);
  if (founded_word.word == word) {
    return founded_word;
  }
  founded_word = WordSearchSolver::FindWord(word, CheckDirection::kLeftDiag);
  if (founded_word.word == word) {
    return founded_word;
  }
  founded_word = WordSearchSolver::FindWord(word, CheckDirection::kRightDiag);
  if (founded_word.word == word) {
    return founded_word;
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::FindWord(const std::string& word,
                                        CheckDirection direction) {
  WordLocation founded_word;
  if (CheckDirection::kHorizontal == direction) {
    founded_word = CheckHorizontal(word);
    return founded_word;
  }
  if (CheckDirection::kVertical == direction) {
    founded_word = CheckVertical(word);
    return founded_word;
  }
  if (CheckDirection::kLeftDiag == direction) {
    founded_word = CheckLeftDiag(word);
    return founded_word;
  }
  if (CheckDirection::kRightDiag == direction) {
    founded_word = CheckRightDiag(word);
    return founded_word;
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::CheckHorizontal(const std::string& word) {
  WordLocation founded_word;
  std::string store;
  std::vector<CharPositions> coordinate;
  // if (word.size() > puzzle_width_) {
  //   throw std::invalid_argument("word too long");
  // }
  for (size_t i = 0; i < puzzle_height_; ++i) {
    for (size_t j = 0; j < puzzle_width_; ++j) {
      if (puzzle_.at(i).at(j) == word.at(0)) {
        store = "";
        coordinate.clear();
        if (word.size() == 1) {
          coordinate.push_back({puzzle_.at(i).at(j), i, j});
          founded_word = {word, coordinate};
        }
        for (size_t k = 0; k < word.size(); ++k) {
          if ((j + k) < puzzle_width_) {
            if (puzzle_.at(i).at(j + k) == word.at(k)) {
              store += puzzle_.at(i).at(j + k);
              coordinate.push_back({puzzle_.at(i).at(j + k), i, j + k});
            }
            if (store == word) {
              founded_word = {store, coordinate};
            }
          }
        }
      }
    }
  }
  return founded_word;
}
WordLocation WordSearchSolver::CheckVertical(const std::string& word) {
  WordLocation founded_word;
  std::string store;
  std::vector<CharPositions> coordinate;
  // if (word.size() > puzzle_height_) {
  //   throw std::invalid_argument("word too long");
  // }
  for (size_t i = 0; i < puzzle_height_; ++i) {
    for (size_t j = 0; j < puzzle_width_; ++j) {
      if (puzzle_.at(i).at(j) == word.at(0)) {
        store = "";
        coordinate.clear();
        if (word.size() == 1) {
          coordinate.push_back({puzzle_.at(i).at(j), i, j});
          founded_word = {word, coordinate};
        }
        for (size_t k = 0; k < word.size(); ++k) {
          if ((i + k) < puzzle_height_) {
            if (puzzle_.at(i + k).at(j) == word.at(k)) {
              store += puzzle_.at(i + k).at(j);
              coordinate.push_back({puzzle_.at(i + k).at(j), i + k, j});
            }
            if (store == word) {
              founded_word = {store, coordinate};
            }
          }
        }
      }
    }
  }
  return founded_word;
}
WordLocation WordSearchSolver::CheckLeftDiag(const std::string& word) {
  WordLocation founded_word;
  std::string store;
  std::vector<CharPositions> coordinate;
  // if (word.size() > puzzle_height_) {
  //   throw std::invalid_argument("word too long");
  // }
  for (size_t i = 0; i < puzzle_height_; ++i) {
    for (size_t j = 0; j < puzzle_width_; ++j) {
      if (puzzle_.at(i).at(j) == word.at(0)) {
        store = "";
        coordinate.clear();
        if (word.size() == 1) {
          coordinate.push_back({puzzle_.at(i).at(j), i, j});
          founded_word = {word, coordinate};
        }
        for (size_t k = 0; k < word.size(); ++k) {
          if ((i + k) < puzzle_height_ && j >= k) {
            // out of bound issue
            if (puzzle_.at(i + k).at(j - k) == word.at(k)) {
              store += puzzle_.at(i + k).at(j - k);
              coordinate.push_back({puzzle_.at(i + k).at(j - k), i + k, j - k});
            }
            if (store == word) {
              founded_word = {store, coordinate};
            }
          }
        }
      }
    }
  }
  return founded_word;
}
WordLocation WordSearchSolver::CheckRightDiag(const std::string& word) {
  WordLocation founded_word;
  std::string store;
  std::vector<CharPositions> coordinate;
  // if (word.size() > puzzle_height_) {
  //   throw std::invalid_argument("word too long");
  // }

  // https://discuss.cs128.org/d/3976-auto-grader-feedback
  //  A vector threw an exception due to an index being out of range
  for (size_t i = 0; i < puzzle_height_; ++i) {
    for (size_t j = 0; j < puzzle_width_; ++j) {
      if (puzzle_.at(i).at(j) == word.at(0)) {
        store = "";
        coordinate.clear();
        if (word.size() == 1) {
          coordinate.push_back({puzzle_.at(i).at(j), i, j});
          founded_word = {word, coordinate};
        }
        for (size_t k = 0; k < word.size(); ++k) {
          if ((i + k) < puzzle_height_ && (j + k) < puzzle_width_) {
            if (puzzle_.at(i + k).at(j + k) == word.at(k)) {
              store += puzzle_.at(i + k).at(j + k);
              coordinate.push_back({puzzle_.at(i + k).at(j + k), i + k, j + k});
            }
            if (store == word) {
              founded_word = {store, coordinate};
            }
          }
        }
      }
    }
  }
  return founded_word;
}