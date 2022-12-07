#include "image_ppm.hpp"

#include <fstream>
#include <iostream>
#include <string>

#include "pixel.hpp"
// implement the rest of ImagePPM's functions here

Pixel ImagePPM::GetPixel(int row, int col) const {
  Pixel pix_loc = pixels_[row][col];
  return pix_loc;
}
int ImagePPM::GetMaxColorValue() const {
  return max_color_value_;
}  // not always 255

void ImagePPM::RemoveVerticalSeamInPPM(const int* col_index) {
  // height is same if shrink vertically
  auto** resized_image_vertical = new Pixel*[height_];
  for (int row = 0; row < height_; ++row) {
    resized_image_vertical[row] = new Pixel[width_ - 1];
  }
  for (int row = 0; row < height_; ++row) {
    for (int col = 0; col < width_; ++col) {
      if (col_index[row] < col) {
        resized_image_vertical[row][col - 1] = pixels_[row][col];
      } else if (col_index[row] != col) {
        resized_image_vertical[row][col] = pixels_[row][col];
      }
    }
  }
  for (int row = 0; row < height_; ++row) {
    delete[] pixels_[row];
  }
  delete[] pixels_;
  pixels_ = resized_image_vertical;
  width_ = width_ - 1;
}
void ImagePPM::RemoveHorizontalSeamInPPM(const int* row_index) {
  // width_ is same if shrink horizontally
  auto** resized_image_horizontal = new Pixel*[height_ - 1];
  for (int row = 0; row < height_ - 1; ++row) {
    resized_image_horizontal[row] = new Pixel[width_];
  }
  for (int col = 0; col < width_; ++col) {
    for (int row = 0; row < height_; ++row) {
      if (row_index[col] < row) {
        resized_image_horizontal[row - 1][col] = pixels_[row][col];
      } else if (row_index[col] != row) {
        resized_image_horizontal[row][col] = pixels_[row][col];
      }
    }
  }
  for (int row = 0; row < height_; ++row) {
    delete[] pixels_[row];
  }
  delete[] pixels_;
  pixels_ = resized_image_horizontal;
  height_ = height_ - 1;
}
//  given functions below, DO NOT MODIFY

ImagePPM::ImagePPM(const std::string& path) {
  std::ifstream input_file(path);
  input_file >> *this;
  input_file.close();
}

ImagePPM::ImagePPM(const ImagePPM& source) { *this = source; }

ImagePPM& ImagePPM::operator=(const ImagePPM& source) {
  if (this == &source) {
    return *this;
  }

  Clear();

  height_ = source.height_;
  width_ = source.width_;
  max_color_value_ = source.max_color_value_;

  pixels_ = new Pixel*[height_];
  for (int row = 0; row < height_; row++) {
    pixels_[row] = new Pixel[width_];

    for (int col = 0; col < width_; col++) {
      pixels_[row][col] = source.pixels_[row][col];
    }
  }

  return *this;
}

ImagePPM::~ImagePPM() { Clear(); }

void ImagePPM::Clear() {
  for (int i = 0; i < height_; i++) {
    delete[] pixels_[i];
  }

  delete[] pixels_;

  height_ = 0;
  width_ = 0;
  pixels_ = nullptr;
}

std::istream& operator>>(std::istream& is, ImagePPM& image) {
  image.Clear();
  std::string line;
  // ignore magic number line
  getline(is, line);
  // check to see if there's a comment line
  getline(is, line);
  if (line[0] == '#') {
    getline(is, line);
  }
  // parse width and height
  int space = line.find_first_of(' ');
  image.width_ = std::stoi(line.substr(0, space));
  image.height_ = std::stoi(line.substr(space + 1));
  // get max color value
  getline(is, line);
  image.max_color_value_ = std::stoi(line);
  // init and fill in Pixels array
  image.pixels_ = new Pixel*[image.height_];
  for (int i = 0; i < image.height_; i++) {
    image.pixels_[i] = new Pixel[image.width_];
  }
  for (int row = 0; row < image.height_; row++) {
    for (int col = 0; col < image.width_; col++) {
      getline(is, line);
      int red = std::stoi(line);
      getline(is, line);
      int green = std::stoi(line);
      getline(is, line);
      int blue = std::stoi(line);

      Pixel p(red, green, blue);
      image.pixels_[row][col] = p;
    }
  }
  return is;
}