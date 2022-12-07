#include "db_table.hpp"

#include <iostream>
#include <map>
#include <string>
// const unsigned int kRowGrowthRate = 2;

void DbTable::ResizeColInRows() {
  if (col_descs_.size() == row_col_capacity_) {
    unsigned int update_row_col_capacity = row_col_capacity_ * 2;
    for (auto& [id, row] : rows_) {
      void** new_row = new void*[update_row_col_capacity];
      for (size_t i = 0; i < col_descs_.size(); ++i) {
        new_row[i] = row[i];
      }
      delete[] row;
      row = new_row;
    }
    row_col_capacity_ = update_row_col_capacity;
  }
}

void DbTable::CastinAddCol(const std::pair<std::string, DataType>& col_desc) {
  for (auto& row_pair : rows_) {
    if (col_desc.second == DataType::kString) {
      row_pair.second[col_descs_.size() - 1] =
          static_cast<void*>(new std::string(""));
    } else if (col_desc.second == DataType::kDouble) {
      row_pair.second[col_descs_.size() - 1] =
          static_cast<void*>(new double(0.0));
    } else if (col_desc.second == DataType::kInt) {
      row_pair.second[col_descs_.size() - 1] = static_cast<void*>(new int(0));
    }
  }
}
void DbTable::AddColumn(const std::pair<std::string, DataType>& col_desc) {
  if (row_col_capacity_ < 0) {
    throw std::runtime_error("invalid capacity");
  }
  ResizeColInRows();
  col_descs_.push_back(col_desc);
  CastinAddCol(col_desc);
}

void DbTable::CastinDeleteCol(unsigned int col_idx) {
  for (auto& row_pair : rows_) {
    if (col_descs_.at(col_idx).second == DataType::kString) {
      delete static_cast<std::string*>(row_pair.second[col_idx]);
    } else if (col_descs_.at(col_idx).second == DataType::kInt) {
      delete static_cast<int*>(row_pair.second[col_idx]);
    } else if (col_descs_.at(col_idx).second == DataType::kDouble) {
      delete static_cast<double*>(row_pair.second[col_idx]);
    }
    for (size_t i = col_idx; i < col_descs_.size(); ++i) {  // check this again
      row_pair.second[col_idx] = row_pair.second[col_idx + 1];
    }
  }
}
void DbTable::DeleteColumnByIdx(unsigned int col_idx) {
  if (col_idx < 0 || col_idx >= col_descs_.size()) {
    throw std::out_of_range("index too small or too large");
  }
  if (col_descs_.size() == 1 && (!rows_.empty())) {
    throw std::runtime_error(
        "any table with at least one row must have at least one column");
  }
  CastinDeleteCol(col_idx);
  col_descs_.erase(col_descs_.begin() + col_idx);
}

void DbTable::CastinAddRow(const std::initializer_list<std::string>& col_data,
                           int& row_num) {
  for (const std::string& str : col_data) {
    if (col_descs_.at(row_num).second == DataType::kString) {
      rows_[next_unique_id_][row_num] =
          static_cast<void*>(new std::string(str));
    } else if (col_descs_.at(row_num).second == DataType::kDouble) {
      rows_[next_unique_id_][row_num] =
          static_cast<void*>(new double(std::stod(str)));
    } else if (col_descs_.at(row_num).second == DataType::kInt) {
      rows_[next_unique_id_][row_num] =
          static_cast<void*>(new int{std::stoi(str)});
    }
    ++row_num;
  }
}
void DbTable::AddRow(const std::initializer_list<std::string>& col_data) {
  if (!(col_data.size() == col_descs_.size())) {
    throw std::invalid_argument(
        "number of items in col_data not equal to the number of columns in the "
        "table's rows");
  }
  rows_[next_unique_id_] = new void*[row_col_capacity_];
  int row_num = 0;
  CastinAddRow(col_data, row_num);
  ++next_unique_id_;
}

void DbTable::DeleteRowById(unsigned int id) {
  if (id < 0 || id >= rows_.size()) {
    throw std::invalid_argument("out of range");
  }
  if (!rows_.contains(id)) {
    throw std::invalid_argument("not exist");
  }
  CastinDeleteRow(id);
  delete[] rows_[id];
  rows_.erase(id);
}

void DbTable::CastinDeleteRow(unsigned int id) {
  for (unsigned int i = 0; i < col_descs_.size(); ++i) {
    if (col_descs_.at(i).second == DataType::kString) {
      delete static_cast<std::string*>(rows_[id][i]);
    } else if (col_descs_.at(i).second == DataType::kDouble) {
      delete static_cast<double*>(rows_[id][i]);
    } else if (col_descs_.at(i).second == DataType::kInt) {
      delete static_cast<int*>(rows_[id][i]);
    }
  }
}

DbTable::DbTable(const DbTable& rhs):
    next_unique_id_(rhs.next_unique_id_),
    row_col_capacity_(rhs.row_col_capacity_),
    col_descs_(rhs.col_descs_) {
  for (const auto& row_pair : rhs.rows_) {
    rows_[row_pair.first] = new void*[row_col_capacity_];
    for (unsigned int i = 0; i < col_descs_.size(); ++i) {
      if (rhs.col_descs_.at(i).second == DataType::kString) {
        rows_[row_pair.first][i] = static_cast<void*>(
            new std::string{*static_cast<std::string*>(row_pair.second[i])});
      } else if (rhs.col_descs_.at(i).second == DataType::kDouble) {
        rows_[row_pair.first][i] = static_cast<void*>(
            new double{*static_cast<double*>(row_pair.second[i])});
      } else if (rhs.col_descs_.at(i).second == DataType::kInt) {
        rows_[row_pair.first][i] =
            static_cast<void*>(new int{*static_cast<int*>(row_pair.second[i])});
      }
    }
  }
}

DbTable& DbTable::operator=(const DbTable& rhs) {
  if (this == &rhs) return *this;
  Clear();
  next_unique_id_ = rhs.next_unique_id_;
  row_col_capacity_ = rhs.row_col_capacity_;
  col_descs_ = rhs.col_descs_;
  for (const auto& row_pair : rhs.rows_) {
    rows_[row_pair.first] = new void*[row_col_capacity_];
    for (unsigned int i = 0; i < col_descs_.size(); ++i) {
      if (rhs.col_descs_.at(i).second == DataType::kString) {
        rows_[row_pair.first][i] = static_cast<void*>(
            new std::string{*static_cast<std::string*>(row_pair.second[i])});
      } else if (rhs.col_descs_.at(i).second == DataType::kDouble) {
        rows_[row_pair.first][i] = static_cast<void*>(
            new double{*static_cast<double*>(row_pair.second[i])});
      } else if (rhs.col_descs_.at(i).second == DataType::kInt) {
        rows_[row_pair.first][i] =
            static_cast<void*>(new int{*static_cast<int*>(row_pair.second[i])});
      }
    }
  }
  return *this;
}
void DbTable::Clear() {
  for (auto& row_pair : rows_) {
    delete row_pair.second;
  }
  rows_.clear();
}
DbTable::~DbTable() { Clear(); }

std::ostream& operator<<(std::ostream& os, const DbTable& table) {
  for (unsigned int i = 0; i < table.col_descs_.size(); ++i) {
    os << table.col_descs_.at(i).first;
    if (table.col_descs_.at(i).second == DataType::kString) {
      os << " (std::string)";
    }
    if (table.col_descs_.at(i).second == DataType::kInt) {
      os << " (int)";
    }
    if (table.col_descs_.at(i).second == DataType::kDouble) {
      os << " (double)";
    }
    if (i != table.col_descs_.size() - 1) {
      os << ", ";
    }
  }
  os << "\n";
  for (const auto& row_pair : table.rows_) {
    for (unsigned int i = 0; i < table.col_descs_.size(); ++i) {
      if (table.col_descs_.at(i).second == DataType::kString) {
        os << *static_cast<std::string*>(row_pair.second[i]);
      } else if (table.col_descs_.at(i).second == DataType::kInt) {
        os << *static_cast<int*>(row_pair.second[i]);
      } else if (table.col_descs_.at(i).second == DataType::kDouble) {
        os << *static_cast<double*>(row_pair.second[i]);
      }
      if (i != table.col_descs_.size() - 1) {
        os << ", ";
      }
    }
    os << "\n";
  }
  return os;
}