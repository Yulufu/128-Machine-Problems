#include "path_image.hpp"

#include <cstdlib>  // for size_t
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "color.hpp"
#include "grayscale_image.hpp"
#include "path.hpp"

PathImage::PathImage(const GrayscaleImage& image,
                     const ElevationDataset& dataset):
    width_(image.Width()), height_(image.Height()) {
  paths_ = MovingNotAtEdge(dataset);
  paths_ = MovingAtRowZero(dataset);
  paths_ = MovingAtBottom(dataset);
  // need to interact with color to make ppm path_image
  path_image_ = image.GetImage();
  Path easiest_path = Path(dataset.Width(), 0);
  for (size_t k = 0; k < paths_.size(); ++k) {  // turn very path red
    easiest_path = paths_.at(0);
    if (easiest_path.EleChange() > paths_.at(k).EleChange()) {
      easiest_path = paths_.at(k);
    }  // not get in the loop
    Path red_path = paths_.at(k);
    for (size_t i = 0; i < red_path.Length(); ++i) {
      // path_image_.at(red_path.GetPath().at(i)).at(i) = kInRed;
      path_image_.at(red_path.GetPath().at(i)).at(i) = kInRed;
    }  // out of bound
  }
  for (size_t i = 0; i < easiest_path.GetPath().size(); ++i) {
    path_image_.at(easiest_path.GetPath().at(i)).at(i) = kInGreen;
  }
}

////////////////////////Helper
/// Functions////////////////////////////////////////
std::vector<Path> PathImage::MovingNotAtEdge(const ElevationDataset& dataset) {
  std::vector<std::vector<int>> path_ele = dataset.GetData();
  int forward_dir = 0;
  int up_dir = 0;
  int down_dir = 0;
  int row_loc = 0;
  for (size_t i = 0; i < dataset.Height(); ++i) {
    Path each_pathifo = Path(dataset.Width(), i);
    row_loc = (int)i;  // the starting_row
    std::cout << "row" << row_loc << std::endl;
    for (size_t j = 0; j < dataset.Width() - 1; ++j) {
      each_pathifo.SetLoc(j, row_loc);
      if ((row_loc + 1 < (int)dataset.Height() && row_loc - 1 >= 0) &&
          j + 1 < dataset.Width()) {
        forward_dir =
            abs(path_ele.at(row_loc).at(j + 1) - path_ele.at(row_loc).at(j));
        up_dir = abs(path_ele.at(row_loc + 1).at(j + 1) -
                     path_ele.at(row_loc).at(j));
        down_dir = abs(path_ele.at(row_loc - 1).at(j + 1) -
                       path_ele.at(row_loc).at(j));
      }
      if (up_dir < forward_dir && up_dir < down_dir) {
        each_pathifo.IncEleChange(up_dir);
        row_loc = row_loc + 1;  // show be starting_row_ + 1
      } else if (down_dir < forward_dir && down_dir < up_dir) {
        each_pathifo.IncEleChange(down_dir);
        row_loc = row_loc - 1;
      } else if (up_dir == down_dir && down_dir < forward_dir) {
        each_pathifo.IncEleChange(down_dir);
        row_loc = row_loc - 1;
      } else {
        each_pathifo.IncEleChange(forward_dir);  // row_loc = row_loc;
      }
    }
    each_pathifo.SetLoc(dataset.Width() - 1, row_loc);
    paths_.push_back(each_pathifo);
    std::cout << "ele chaneg totoal" << each_pathifo.EleChange() << std::endl;
    // why is it 0;
  }
  return paths_;
}
std::vector<Path> PathImage::MovingAtRowZero(const ElevationDataset& dataset) {
  std::vector<std::vector<int>> path_ele = dataset.GetData();
  int forward_dir = 0;
  int up_dir = 0;
  int down_dir = 0;
  int row_loc = 0;
  for (size_t i = 0; i < dataset.Height(); ++i) {
    Path each_pathifo = Path(dataset.Width(), i);
    row_loc = (int)i;  // the starting_row
    // std::cout << "row" << row_loc << std::endl;
    for (size_t j = 0; j < dataset.Width() - 1; ++j) {
      each_pathifo.SetLoc(j, row_loc);
      if (row_loc == 0 && j + 1 < dataset.Width()) {
        forward_dir =
            abs(path_ele.at(row_loc).at(j + 1) - path_ele.at(row_loc).at(j));
        up_dir = abs(path_ele.at(row_loc + 1).at(j + 1) -
                     path_ele.at(row_loc).at(j));
        down_dir = INT32_MAX;
      }
      if (up_dir < forward_dir && up_dir < down_dir) {
        each_pathifo.IncEleChange(up_dir);
        row_loc = row_loc + 1;  // show be starting_row_ + 1
      } else if (down_dir < forward_dir && down_dir < up_dir) {
        each_pathifo.IncEleChange(down_dir);
        row_loc = row_loc - 1;
      } else if (up_dir == down_dir && down_dir < forward_dir) {
        each_pathifo.IncEleChange(down_dir);
        row_loc = row_loc - 1;
      } else {
        each_pathifo.IncEleChange(forward_dir);  // row_loc = row_loc;
      }
    }
    each_pathifo.SetLoc(dataset.Width() - 1, row_loc);
    paths_.push_back(each_pathifo);
  }
  return paths_;
}
std::vector<Path> PathImage::MovingAtBottom(const ElevationDataset& dataset) {
  std::vector<std::vector<int>> path_ele = dataset.GetData();
  int forward_dir = 0;
  int up_dir = 0;
  int down_dir = 0;
  int row_loc = 0;
  for (size_t i = 0; i < dataset.Height(); ++i) {
    Path each_pathifo = Path(dataset.Width(), i);
    row_loc = (int)i;  // the starting_row
    for (size_t j = 0; j < dataset.Width() - 1; ++j) {
      each_pathifo.SetLoc(j, row_loc);
      if (row_loc == (int)dataset.Height() - 1) {
        forward_dir =
            abs(path_ele.at(row_loc).at(j + 1) - path_ele.at(row_loc).at(j));
        down_dir = abs(path_ele.at(row_loc - 1).at(j + 1) -
                       path_ele.at(row_loc).at(j));
        up_dir = INT32_MAX;
      }
      if (up_dir < forward_dir && up_dir < down_dir) {
        each_pathifo.IncEleChange(up_dir);
        row_loc = row_loc + 1;  // show be starting_row_ + 1
      } else if (down_dir < forward_dir && down_dir < up_dir) {
        each_pathifo.IncEleChange(down_dir);
        row_loc = row_loc - 1;
      } else if (up_dir == down_dir && down_dir < forward_dir) {
        each_pathifo.IncEleChange(down_dir);
        row_loc = row_loc - 1;
      } else {
        each_pathifo.IncEleChange(forward_dir);  // row_loc = row_loc;
      }
    }
    each_pathifo.SetLoc(dataset.Width() - 1, row_loc);
    paths_.push_back(each_pathifo);
  }
  return paths_;
}
/////////////////////////////End Helper///////////////////////////////////////
size_t PathImage::Width() const { return width_; }
size_t PathImage::Height() const { return height_; }
unsigned int PathImage::MaxColorValue() const { return kMaxColorValue; }
const std::vector<Path>& PathImage::Paths() const { return paths_; }
const std::vector<std::vector<Color>>& PathImage::GetPathImage() const {
  return path_image_;
}
void PathImage::ToPpm(const std::string& name) const {
  std::string p_three = "P3";
  std::ofstream ofs{name};
  if (!ofs.is_open()) {
    throw std::runtime_error("file is not open");
  }
  ofs << p_three << '\n'
      << Width() << " " << Height() << " " << '\n'
      << MaxColorValue() << '\n';
  for (size_t i = 0; i < path_image_.size(); ++i) {
    for (size_t j = 0; j < path_image_.at(i).size(); ++j) {
      Color ppm = path_image_.at(i).at(j);
      int red = ppm.Red();
      int green = ppm.Green();
      int blue = ppm.Blue();
      ofs << red << " " << green << " " << blue << " ";
    }
    ofs << '\n';
  }
  ofs << '\n';
}
