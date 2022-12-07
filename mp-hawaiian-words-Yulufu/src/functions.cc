#include "functions.hpp"

#include <cctype>
#include <iostream>
#include <string>
#include <vector>
// Your function definitions should go in this source file.

std::string CheckIfValid(std::string sentence) {
  for (unsigned int i = 0; i < sentence.size(); ++i) {
    char character = sentence.at(i);
    sentence[i] = (char)tolower(character);  // turn to lower case
    character = sentence.at(i);  // now char should all be in lowercase
    if (character != 'a' && character != 'e' && character != 'i' &&
        character != 'o' && character != 'u' && character != 'p' &&
        character != 'k' && character != 'h' && character != 'l' &&
        character != 'm' && character != 'n' && character != 'w' &&
        character != '\'' && character != ' ') {
      std::cout << sentence
                << " contains a character not a part of the Hawaiian language."
                << std::endl;
    }
  }
  // std::cout << sentence << std::endl;
  return sentence;
}

std::vector<std::string> SentenceToWords(std::string sentence) {
  std::string temp;
  std::vector<std::string> lowercasewords;
  for (unsigned int i = 0; i < sentence.size(); ++i) {
    if (sentence.at(i) != ' ') {
      temp += sentence.at(i);
    }
    if (sentence.at(i) == ' ') {
      lowercasewords.push_back(temp);
      // std::cout << temp << std::endl;
      temp = "";
    }
  }
  if (!temp.empty()) {  // maybe use .empty method to check if size != 0
    lowercasewords.push_back(temp);
    // std::cout << temp << std::endl;
  }
  return lowercasewords;
}
// constant helper
bool CheckConstant(char current_letter) {
  bool constant = false;
  if (current_letter == '\'' || current_letter == 'p' ||
      current_letter == 'k' || current_letter == 'h' || current_letter == 'l' ||
      current_letter == 'm' || current_letter == 'n') {
    constant = true;
  }
  return constant;
}
// CheckA helper
std::string CheckA(unsigned int& j, unsigned int size, char next_letter) {
  if (j != size - 1 && next_letter != 'i' && next_letter != 'e' &&
      next_letter != 'o' && next_letter != 'u' &&
      next_letter != '\'') {  // a is not the last char, a is not in combination
    return "ah-";
  }
  if (j == size - 1 ||
      next_letter == '\'') {  // a is the last char, not in combination
    return "ah";
  }
  if ((j + 1) != size - 1 &&
      (next_letter == 'i' ||
       next_letter == 'e')) {  // a in combination, not last char
    return "eye-";
  }
  if ((j + 1) == size - 1 &&
      (next_letter == 'i' ||
       next_letter == 'e')) {  // a in combination,  last char
    return "eye";
  }
  if ((j + 1) != size - 1 &&
      (next_letter == 'o' ||
       next_letter == 'u')) {  // a in combination, not last char
    return "ow-";
  }
  if ((j + 1) == size - 1 &&
      (next_letter == 'o' ||
       next_letter == 'u')) {  // a in combination,  last char
    return "ow";
  }
  return "";
}
// CheckE helper
std::string CheckE(unsigned int& j, unsigned int size, char next_letter) {
  if (j != size - 1 && next_letter != 'i' &&
      next_letter !=
          'u') {  // a is not the last char, a is not in, vowel combination
    return "eh-";
  }
  if (j == size - 1) {  // e is the last char, not in combination
    return "eh";
  }
  if ((j + 1) != size - 1 && next_letter == 'i') {
    return "ay-";
  }
  if ((j + 1) == size - 1 && next_letter == 'i') {
    return "ay";
  }
  if ((j + 1) != size - 1 && next_letter == 'u') {
    return "eh-oo-";
  }
  if ((j + 1) == size - 1 && next_letter == 'u') {
    return "eh-oo";
  }
  return "";
}
std::string CheckI(unsigned int& j, unsigned int size, char next_letter) {
  if (j != size - 1 && next_letter != 'u') {
    return "ee-";
  }
  if (j == size - 1) {  // e is the last char, not in combination
    return "ee";
  }
  if ((j + 1) != size - 1 && next_letter == 'u') {
    return "ew-";
  }
  if ((j + 1) == size - 1 && next_letter == 'u') {
    return "ew";
  }
  return "";
}
std::string CheckO(unsigned int& j, unsigned int size, char next_letter) {
  if (j != size - 1 && next_letter != 'i' && next_letter != 'u') {
    return "oh-";
  }
  if (j == size - 1) {
    return "oh";
  }
  if ((j + 1) != size - 1 && next_letter == 'i') {
    return "oy-";
  }
  if ((j + 1) == size - 1 && next_letter == 'i') {
    return "oy";
  }
  if ((j + 1) != size - 1 && next_letter == 'u') {
    return "ow-";
  }
  if ((j + 1) == size - 1 && next_letter == 'u') {
    return "ow";
  }
  return "";
}
std::string CheckU(unsigned int& j, unsigned int size, char next_letter) {
  if (j != size - 1 && next_letter != 'i') {
    return "oo-";
  }
  if (j == size - 1) {  // e is the last char, not in combination
    return "oo";
  }
  if ((j + 1) != size - 1 && next_letter == 'i') {
    return "ooey-";
  }
  if ((j + 1) == size - 1 && next_letter == 'i') {
    return "ooey";
  }
  return "";
}
std::string CheckW(unsigned int j, char previous_letter) {
  if (j == 0 || previous_letter == 'a' || previous_letter == 'o' ||
      previous_letter == 'u') {
    return "w";
  }
  return "v";
}

unsigned int PlusJ(const std::string& letter, unsigned int j) {
  if (letter == "eye-" || letter == "eye" || letter == "ow-" ||
      letter == "ow" || letter == "ay-" || letter == "ay" ||
      letter == "eh-oo-" || letter == "eh-oo" || letter == "ew-" ||
      letter == "ew" || letter == "oy-" || letter == "oy" ||
      letter == "ooey-" || letter == "ooey") {
    return j + 1;
  }
  return j;
}
std::string CheckVowel(unsigned int& j,
                       unsigned int size,
                       char next_letter,
                       std::string letter,
                       char current_letter) {
  std::string phenetic_words;
  if (current_letter == 'a') {  // check if it has a
    letter = CheckA(j, size, next_letter);
    j = PlusJ(letter, j);
    phenetic_words += letter;
  }
  if (current_letter == 'e') {  // check e
    letter = CheckE(j, size, next_letter);
    j = PlusJ(letter, j);
    phenetic_words += letter;

  } else if (current_letter == 'i') {  // check i
    letter = CheckI(j, size, next_letter);
    j = PlusJ(letter, j);
    phenetic_words += letter;

  } else if (current_letter == 'o') {  // check o
    letter = CheckO(j, size, next_letter);
    j = PlusJ(letter, j);
    phenetic_words += letter;

  } else if (current_letter == 'u') {  // check u
    letter = CheckU(j, size, next_letter);
    j = PlusJ(letter, j);
    phenetic_words += letter;
  }
  return phenetic_words;
}
std::string TranslateToPhenetic(std::vector<std::string> lowercasewords) {
  std::string letter = " ";
  std::string phenetic_words;
  for (unsigned int i = 0; i < lowercasewords.size(); ++i) {
    std::string current = lowercasewords.at(i);
    for (unsigned int j = 0; j < current.size(); ++j) {
      char current_letter = current.at(j);
      char next_letter = ' ';
      char previous_letter = ' ';
      if (j < current.size() - 1) {
        next_letter = current.at(j + 1);
      }
      if (j > 0) {
        previous_letter = current.at(j - 1);
      }
      if (CheckConstant(current_letter)) {  // check constant
        phenetic_words += current.at(j);
        continue;
      }
      phenetic_words +=
          CheckVowel(j, current.size(), next_letter, letter, current_letter);
      if (current_letter == 'w') {  // check w
        letter = CheckW(j, previous_letter);
        j = PlusJ(letter, j);
        phenetic_words += letter;
        continue;
      }
    }
    letter = " ";
    phenetic_words.append(letter);
  }
  return phenetic_words;
}