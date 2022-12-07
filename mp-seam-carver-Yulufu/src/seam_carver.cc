#include "seam_carver.hpp"

#include "image_ppm.hpp"

// implement the rest of SeamCarver's functions here

// delete[] not right
const ImagePPM& SeamCarver::GetImage() const { return image_; }
int SeamCarver::GetHeight() const { return height_; }
int SeamCarver::GetWidth() const { return width_; }

int SeamCarver::GetEnergy(int row, int col) const {
  Pixel up_pix = {0, 0, 0};
  Pixel down_pix = {0, 0, 0};
  Pixel left_pix = {0, 0, 0};
  Pixel right_pix = {0, 0, 0};
  if (row != 0 && row != image_.GetHeight() - 1) {  // not 0th/last row
    up_pix = image_.GetPixel(row - 1, col);
    down_pix = image_.GetPixel(row + 1, col);
  } else if (row == 0) {
    up_pix = image_.GetPixel(image_.GetHeight() - 1, col);
    down_pix = image_.GetPixel(row + 1, col);
  } else if (row == image_.GetHeight() - 1) {
    up_pix = image_.GetPixel(row - 1, col);
    down_pix = image_.GetPixel(0, col);
  }
  if (col != 0 && col != image_.GetWidth() - 1) {  // not oth/last col
    left_pix = image_.GetPixel(row, col - 1);
    right_pix = image_.GetPixel(row, col + 1);
  } else if (col == 0) {
    left_pix = image_.GetPixel(row, image_.GetWidth() - 1);
    right_pix = image_.GetPixel(row, col + 1);
  } else if (col == image_.GetWidth() - 1) {
    left_pix = image_.GetPixel(row, col - 1);
    right_pix = image_.GetPixel(row, 0);
  }
  int red_row_diff_in_sq = (left_pix.GetRed() - right_pix.GetRed()) *
                           (left_pix.GetRed() - right_pix.GetRed());
  int green_row_diff_in_sq = (left_pix.GetGreen() - right_pix.GetGreen()) *
                             (left_pix.GetGreen() - right_pix.GetGreen());
  int blue_row_diff_in_sq = (left_pix.GetBlue() - right_pix.GetBlue()) *
                            (left_pix.GetBlue() - right_pix.GetBlue());
  int red_col_diff_in_sq = (up_pix.GetRed() - down_pix.GetRed()) *
                           (up_pix.GetRed() - down_pix.GetRed());
  int green_col_diff_in_sq = (up_pix.GetGreen() - down_pix.GetGreen()) *
                             (up_pix.GetGreen() - down_pix.GetGreen());
  int blue_col_diff_in_sq = (up_pix.GetBlue() - down_pix.GetBlue()) *
                            (up_pix.GetBlue() - down_pix.GetBlue());
  int energy = red_row_diff_in_sq + green_row_diff_in_sq + blue_row_diff_in_sq +
               red_col_diff_in_sq + green_col_diff_in_sq + blue_col_diff_in_sq;
  return energy;
}

int SeamCarver::FindMinInFirstRow() const {
  int** values = FindVertialcalSeamHelper();
  int col_index_1st_row = 0;
  for (int col = 0; col < width_; ++col) {
    int min_val = values[0][0];
    if (min_val > values[0][col]) {
      min_val = values[0][col];
      col_index_1st_row = col;
    }
  }
  for (int row = 0; row < height_; ++row) {
    delete[] values[row];
  }
  delete[] values;
  return col_index_1st_row;
}
int SeamCarver::FindMinInFirstCol() const {
  int** values = FindHorizontalSeamHelper();
  int row_index_1st_col = 0;
  for (int row = 0; row < height_; ++row) {
    int min_val = values[0][0];
    if (min_val > values[row][0]) {
      min_val = values[row][0];
      row_index_1st_col = row;
    }
  }
  for (int row = 0; row < height_; ++row) {
    delete[] values[row];
  }
  delete[] values;
  return row_index_1st_col;
}
int* SeamCarver::GetVerticalSeam() const {
  int** values = FindVertialcalSeamHelper();
  int* col_index = new int[height_];
  col_index[0] = FindMinInFirstRow();
  for (int row = 1; row < height_; ++row) {
    for (int col = 0; col < width_; ++col) {
      int current_min_index = col_index[0];
      int left_down_val = INT32_MAX;
      int right_down_val = INT32_MAX;
      int direct_down_val = values[row][current_min_index];
      if (current_min_index == 0) {
        right_down_val = values[row][current_min_index + 1];
      } else if (col_index[0] == width_ - 1) {
        left_down_val = values[row][current_min_index - 1];
      } else {
        left_down_val = values[row][current_min_index - 1];
        right_down_val = values[row][current_min_index + 1];
      }
      if ((right_down_val < left_down_val) &&
          (right_down_val < direct_down_val)) {
        current_min_index = current_min_index + 1;
        col_index[row] = current_min_index;
      } else if ((left_down_val == right_down_val) &&
                 (left_down_val < direct_down_val)) {
        current_min_index = current_min_index - 1;
        col_index[row] = current_min_index;
      } else if ((left_down_val < right_down_val) &&
                 (left_down_val < direct_down_val)) {
        current_min_index = current_min_index - 1;
        col_index[row] = current_min_index;
      } else {
        col_index[row] = current_min_index;
      }
    }
  }
  for (int row = 0; row < height_; ++row) delete[] values[row];
  delete[] values;
  // delete[] col_index; //not working after I after add these
  return col_index;
}
int* SeamCarver::GetHorizontalSeam() const {
  int** values = FindHorizontalSeamHelper();
  int* row_index = new int[width_];
  row_index[0] = FindMinInFirstCol();
  for (int col = 1; col < width_; ++col) {
    for (int row = 0; row < height_; ++row) {
      int current_min_index = row_index[0];
      int up_val = INT32_MAX;
      int down_val = INT32_MAX;
      int direct_val = values[current_min_index][col];
      if (current_min_index == 0) {  // at top row
        down_val = values[current_min_index + 1][col];
      } else if (row_index[0] == height_ - 1) {
        up_val = values[current_min_index - 1][col];
      } else {
        up_val = values[current_min_index - 1][col];
        down_val = values[current_min_index + 1][col];
      }
      if ((down_val < up_val) && (down_val < direct_val)) {
        current_min_index = current_min_index + 1;
        row_index[col] = current_min_index;
      } else if ((up_val == down_val) && (up_val < direct_val)) {
        current_min_index = current_min_index - 1;
        row_index[col] = current_min_index;
      } else if ((up_val < down_val) && (up_val < direct_val)) {
        current_min_index = current_min_index - 1;
        row_index[col] = current_min_index;
      } else {
        row_index[col] = current_min_index;
      }
    }
  }
  for (int row = 0; row < height_; ++row) delete[] values[row];
  delete[] values;
  // delete[] row_index;
  return row_index;
}
int** SeamCarver::FindVertialcalSeamHelper() const {
  int** values = new int*[height_];
  for (int row = 0; row < height_; ++row) {
    values[row] = new int[width_];
  }
  for (int col = 0; col < width_; ++col) {  // last row
    values[height_ - 1][col] = GetEnergy(height_ - 1, col);
  }
  for (int row = height_ - 2; row >= 0; --row) {  // not last row
    for (int col = 0; col < width_; ++col) {
      if (col == 0) {
        int min = GetEnergy(row + 1, col);
        if (min > GetEnergy(row + 1, col + 1)) {
          min = GetEnergy(row + 1, col + 1);
        }
        values[row][col] = GetEnergy(row, col) + min;
      } else if (col == width_ - 1) {
        int min = GetEnergy(row + 1, col);
        if (min > GetEnergy(row + 1, col - 1)) {
          min = GetEnergy(row + 1, col - 1);
        }
        values[row][col] = GetEnergy(row, col) + min;
      } else {
        int left_energy = GetEnergy(row + 1, col - 1);
        int right_energy = GetEnergy(row + 1, col + 1);
        int down_energy = GetEnergy(row + 1, col);
        int min = down_energy;
        if (min > left_energy && left_energy <= right_energy) {
          min = left_energy;
        } else if (min > right_energy && right_energy < left_energy) {
          min = right_energy;
        }
        values[row][col] = GetEnergy(row, col) + min;
      }
    }
  }
  return values;
}
int** SeamCarver::FindHorizontalSeamHelper() const {
  int** values = new int*[height_];
  for (int row = 0; row < height_; ++row) {
    values[row] = new int[width_];
  }
  for (int row = 0; row < height_; ++row) {  // last col
    values[row][width_ - 1] = GetEnergy(row, width_ - 1);
  }
  for (int col = width_ - 2; col >= 0; --col) {  // not last col
    for (int row = 0; row < height_; ++row) {
      if (row == 0) {
        int min = GetEnergy(row, col + 1);
        if (min > GetEnergy(row + 1, col + 1)) {
          min = GetEnergy(row + 1, col + 1);
        }
        values[row][col] = GetEnergy(row, col) + min;
      } else if (row == height_ - 1) {
        int min = GetEnergy(row, col + 1);
        if (min > GetEnergy(row - 1, col + 1)) {
          min = GetEnergy(row - 1, col + 1);
        }
        values[row][col] = GetEnergy(row, col) + min;
      } else {
        int up_energy = GetEnergy(row - 1, col + 1);
        int dir_energy = GetEnergy(row, col + 1);
        int down_energy = GetEnergy(row + 1, col + 1);
        int min = dir_energy;
        if (min > up_energy && up_energy <= down_energy) {
          min = up_energy;
        } else if (min > down_energy && down_energy < up_energy) {
          min = down_energy;
        }
        values[row][col] = GetEnergy(row, col) + min;
      }
    }
  }
  return values;
}

void SeamCarver::RemoveVerticalSeam() {
  if (width_ > 0) {
    int* col_index = GetVerticalSeam();
    image_.RemoveVerticalSeamInPPM(col_index);
    delete[] col_index;
    width_ = width_ - 1;
  }
}
void SeamCarver::RemoveHorizontalSeam() {
  if (height_ > 0) {
    int* row_index = GetHorizontalSeam();
    image_.RemoveHorizontalSeamInPPM(row_index);
    delete[] row_index;
    height_ = height_ - 1;
  }
}
std::ostream& operator<<(std::ostream& os, const ImagePPM& image) {
  std::string p_three = "P3";
  os << p_three << '\n'
     << image.GetWidth() << " " << image.GetHeight() << " " << '\n'
     << image.GetMaxColorValue() << '\n';
  for (int row = 0; row < image.GetHeight(); ++row) {
    for (int col = 0; col < image.GetWidth(); ++col) {
      Pixel pix_comb = image.GetPixel(row, col);
      os << pix_comb.GetRed() << '\n'
         << pix_comb.GetGreen() << '\n'
         << pix_comb.GetBlue() << '\n';
    }
  }
  return os;
}
// given functions below, DO NOT MODIFY

SeamCarver::SeamCarver(const ImagePPM& image): image_(image) {
  height_ = image.GetHeight();
  width_ = image.GetWidth();
}

void SeamCarver::SetImage(const ImagePPM& image) {
  image_ = image;
  width_ = image.GetWidth();
  height_ = image.GetHeight();
}
