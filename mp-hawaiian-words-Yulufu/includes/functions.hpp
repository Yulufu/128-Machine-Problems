#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <string>
#include <vector>

// Your function declarations should go in this header file.

std::string CheckIfValid(std::string sentence);
std::vector<std::string> SentenceToWords(std::string sentence);
// std::vector<std::string> TranslateToPhenetic(
//  std::vector<std::string> lowercasewords);
std::string TranslateToPhenetic(std::vector<std::string> lowercasewords);
bool CheckConstant(char current_letter);
std::string CheckA(unsigned int& j, unsigned int size, char next_letter);
std::string CheckE(unsigned int& j, unsigned int size, char next_letter);
std::string CheckI(unsigned int& j, unsigned int size, char next_letter);
std::string CheckO(unsigned int& j, unsigned int size, char next_letter);
std::string CheckU(unsigned int& j, unsigned int size, char next_letter);
std::string CheckW(unsigned int j, char previous_letter);
std::string CheckVowel(unsigned int& j,
                       unsigned int size,
                       char next_letter,
                       std::string letter,
                       char current_letter);
unsigned int PlusJ(const std::string& letter, unsigned int j);
#endif