#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <string>
#include <vector>

#include "utilities.hpp"

std::vector<std::string> GetSTRNames(
    std::vector<std::vector<std::string>> database);
std::vector<int> CompareWithInputDNA(const std::string& input_dna,
                                     std::vector<std::string> strs);
std::string CompareIndividualWithCSV(
    std::vector<std::vector<std::string>> database,
    std::vector<int>& individual_str_counts);

#endif