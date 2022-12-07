#include "functions.hpp"

#include <iostream>
#include <map>
#include <string>
#include <vector>

std::vector<std::string> GetSTRNames(
    std::vector<std::vector<std::string>> database) {
  std::vector<std::string> strs;
  for (unsigned int i = 0; i < 1; ++i) {
    for (unsigned int j = 1; j < database.at(i).size(); ++j) {
      strs.push_back(database.at(0).at(j));
    }
  }
  return strs;
}

std::vector<int> CompareWithInputDNA(const std::string& input_dna,
                                     std::vector<std::string> strs) {
  std::string current_str;
  std::vector<int> input_dna_str_count;
  for (unsigned int k = 0; k < strs.size(); ++k) {  // get each STR
    current_str = strs.at(k);
    int max = 0;
    int count = 0;
    for (unsigned int i = 0; i < input_dna.size(); ++i) {
      count = 0;
      for (unsigned int j = i; j < input_dna.size(); ++j) {
        if (input_dna.substr(j, current_str.size()) == current_str) {
          ++count;
          j = j + current_str.size() - 1;
        } else {
          break;
        }
      }
      max = std::max(max, count);
    }
    input_dna_str_count.push_back(max);
  }
  return input_dna_str_count;
}

std::string CompareIndividualWithCSV(
    std::vector<std::vector<std::string>> database,
    std::vector<int>& individual_str_counts) {
  std::map<std::string, std::vector<int>> peopleinfo;
  std::vector<int> csv_num;
  std::string name;
  std::string output;
  for (unsigned int i = 1; i < database.size(); ++i) {
    int num_as_int = 0;
    name = database.at(i).at(0);
    for (unsigned int k = 1; k < database.at(i).size(); ++k) {
      std::string current_num = database.at(i).at(k);
      num_as_int = std::stoi(current_num);
      csv_num.push_back(num_as_int);
    }
    peopleinfo[name] = csv_num;
    csv_num.clear();
  }
  for (auto const& info : peopleinfo) {
    // std::cout << info.first << ':' << info.second.at(0) << std::endl;
    if (info.second == individual_str_counts) {
      output = info.first;
      break;
    }
    if (info.second != individual_str_counts) {
      output = "no match";
    }
  }
  return output;
}