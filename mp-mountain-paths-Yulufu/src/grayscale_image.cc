#include "grayscale_image.hpp"

#include <cmath>
#include <cstdlib>  // for size_t
#include <fstream>
#include <iostream>
#include <vector>

#include "color.hpp"
#include "elevation_dataset.hpp"
GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset):
    width_(dataset.Width()), height_(dataset.Height()) {
  for (size_t i = 0; i < dataset.Height(); ++i) {
    std::vector<Color> row_of_color;
    for (size_t j = 0; j < dataset.Width(); ++j) {
      int shade_of_gray = 0;
      int elevation_point = dataset.DatumAt(i, j);
      if (dataset.MaxEle() - dataset.MinEle() != 0) {
        double denominator = dataset.MaxEle() - dataset.MinEle();
        double numerator = elevation_point - dataset.MinEle();
        double calculation_result = (numerator / denominator) * MaxColorValue();
        // std::cout << "calculation_result" << calculation_result << std::endl;
        shade_of_gray = (int)std::round(calculation_result);
      } else {
        shade_of_gray = 0;
      }
      // std::cout << shade_of_gray << std::endl;
      Color color_combination{shade_of_gray, shade_of_gray, shade_of_gray};
      row_of_color.push_back(color_combination);
    }
    image_.push_back(row_of_color);
  }
}  // use debugger or print statement to see what shade_of_gray is and if it's
   // calculated correctly

// also check if min/max are 0
// Color shade_of_gray =
// std::round((elevation_point - min_ele) / (max_ele - min_ele) * 255);
GrayscaleImage::GrayscaleImage(const std::string& filename,
                               size_t width,
                               size_t height):
    width_(width), height_(height) {
  ElevationDataset dataset(filename, width, height);
  for (size_t i = 0; i < dataset.Height(); ++i) {
    std::vector<Color> row_of_color;
    for (size_t j = 0; j < dataset.Width(); ++j) {
      int shade_of_gray = 0;
      int elevation_point = dataset.DatumAt(i, j);
      if (dataset.MaxEle() - dataset.MinEle() != 0) {
        double denominator = dataset.MaxEle() - dataset.MinEle();
        double numerator = elevation_point - dataset.MinEle();
        double calculation_result = numerator / denominator;
        shade_of_gray = (int)std::round(calculation_result);
      } else {
        shade_of_gray = 0;
      }
      Color color_combination{shade_of_gray, shade_of_gray, shade_of_gray};
      row_of_color.push_back(color_combination);
    }
    image_.push_back(row_of_color);
  }
}
size_t GrayscaleImage::Width() const { return width_; }
size_t GrayscaleImage::Height() const { return height_; }
unsigned int GrayscaleImage::MaxColorValue() const { return kMaxColorValue; }
const Color& GrayscaleImage::ColorAt(int row, int col) const {
  return image_.at(row).at(col);
}
const std::vector<std::vector<Color>>& GrayscaleImage::GetImage() const {
  return image_;
}
void GrayscaleImage::ToPpm(const std::string& name) const {
  std::string p_three = "P3";
  std::ofstream ofs{name};
  if (!ofs.is_open()) {
    throw std::runtime_error("file is not open");
  }
  ofs << p_three << '\n'
      << Width() << " " << Height() << " " << '\n'
      << MaxColorValue() << '\n';
  for (size_t i = 0; i < image_.size(); ++i) {
    for (size_t j = 0; j < image_.at(i).size(); ++j) {
      Color ppm = image_.at(i).at(j);
      int red = ppm.Red();
      int green = ppm.Green();
      int blue = ppm.Blue();
      ofs << red << " " << green << " " << blue << " ";
    }
    ofs << '\n';
  }
  ofs << '\n';
}
