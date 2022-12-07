#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "functions.hpp"
#include "utilities.hpp"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " [input_file] [dna_sequence]"
              << std::endl;
    return 1;
  }
  std::ifstream ifs{argv[1]};
  std::vector<std::vector<std::string>> database;
  for (std::string line; std::getline(ifs, line); line = "") {
    // std::cout << "line = \"" << line << '\"' << std::endl;
    std::vector<std::string> csvvect = utilities::GetSubstrs(line, ',');
    database.push_back(csvvect);
  }
  const std::string& input_dna = argv[2];
  std::vector<std::string> strs = GetSTRNames(database);
  std::vector<int> individual_str_counts = CompareWithInputDNA(input_dna, strs);
  std::string output =
      CompareIndividualWithCSV(database, individual_str_counts);
  std::cout << output << std::endl;
  return 0;
}
