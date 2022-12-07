#include "elevation_dataset.hpp"

#include <cstdlib>  // for size_t
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

ElevationDataset::ElevationDataset(const std::string& filename,
                                   size_t width,
                                   size_t height):
    width_(width), height_(height) {
  std::ifstream ifs(filename);
  int value = 0;
  std::cout << "width:" << width_ << std::endl;
  std::cout << "height:" << height_ << std::endl;
  max_ele_ = INT32_MIN;
  min_ele_ = INT32_MAX;
  size_t read_correctly = 0;
  if (!ifs.is_open()) {
    throw std::runtime_error("file is not open");
  }
  for (size_t i = 0; i < height_; ++i) {
    std::vector<int> map_width(width_, 0);
    data_.push_back(map_width);
    for (size_t j = 0; j < width_; ++j) {
      if (ifs.good()) {
        ifs >> value;
        read_correctly += 1;
        if (ifs.fail()) {
          throw std::runtime_error("not right format");
        }
        if (value > max_ele_) {
          max_ele_ = value;
        }
        if (value < min_ele_) {
          min_ele_ = value;
        }
        data_.at(i).at(j) = value;  // high is row, width is colume
      }
    }
  }
  if (read_correctly < (width_ * height_)) {
    throw std::runtime_error("too little data");
  }
  ifs >> value;
  if (!ifs.fail()) {
    throw std::runtime_error("too much data");
  }
}

// instead of check height & width, check how many data
// is in the file
// or how many times can read correctly

/*read exactly width * height values
if this fails at any point, then too little
read one more time
if succeed: too much data
if fails: perfect amount of data
*/

// read_correctly = supposed_size;
// if ((bool)(read_correctly + 1)) {
//   throw std::runtime_error("too much data");
// } not working
size_t ElevationDataset::Width() const { return width_; }
size_t ElevationDataset::Height() const { return height_; }
int ElevationDataset::MaxEle() const { return max_ele_; }
int ElevationDataset::MinEle() const { return min_ele_; }
int ElevationDataset::DatumAt(size_t row, size_t col) const {
  return data_.at(row).at(col);
}
const std::vector<std::vector<int>>& ElevationDataset::GetData() const {
  return data_;
}