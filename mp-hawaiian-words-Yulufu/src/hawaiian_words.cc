#include <iostream>
#include <string>

#include "functions.hpp"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: ./bin/exec word" << std::endl;
    return 1;
  }

  std::string word = argv[1];
  std::cerr << word << std::endl;

  std::string valid_lowercase = CheckIfValid(
      word);  // after calling the function, need to store the value
  std::vector<std::string> vect = SentenceToWords(valid_lowercase);

  std::string phonetics = TranslateToPhenetic(vect);
  std::cout << phonetics << std::endl;
}