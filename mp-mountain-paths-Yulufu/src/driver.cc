#include <iostream>
#include <vector>

#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path.hpp"
#include "path_image.hpp"
int main() {
  ElevationDataset print = ElevationDataset(
      "/home/vagrant/src/MPs/mp-mountain-paths-Yulufu/example-data/"
      "ex_input_data/prompt_5w_2h.dat",
      5,
      2);
  std::vector<std::vector<int>> printout = print.GetData();
  for (size_t i = 0; i < printout.size(); ++i) {
    for (size_t j = 0; j < printout.at(0).size(); ++j) {
      std::cout << printout.at(i).at(j) << std::endl;
    }
  }
  GrayscaleImage printppm = GrayscaleImage(print);
  printppm.ToPpm(
      "/home/vagrant/src/MPs/mp-mountain-paths-Yulufu/example-data/"
      "ppm-testing.ppm");
  PathImage findpath = PathImage(printppm, print);
}