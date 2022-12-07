#include "db.hpp"

#include <iostream>
#include <map>
#include <string>

#include "db_table.hpp"
// do-nothing func
void Database::CreateTable(const std::string& table_name) {
  if (tables_.contains(table_name)) {
    throw std::invalid_argument("table name already exist");
  }
  tables_[table_name] = new DbTable();
}
void Database::DropTable(const std::string& table_name) {
  if (!tables_.contains(table_name)) {
    throw std::invalid_argument("table name not exist");
  }
  delete tables_[table_name];
  tables_.erase(table_name);
}
DbTable& Database::GetTable(const std::string& table_name) {
  if (!tables_.contains(table_name)) {
    throw std::invalid_argument("table name not exist");
  }
  return *tables_[table_name];
}

Database::Database(const Database& rhs) {
  if (tables_.empty()) {
    return;
  }
  for (const auto& table_pair : rhs.tables_) {
    tables_[table_pair.first] = new DbTable(*table_pair.second);
  }
  tables_ = rhs.tables_;
}
Database& Database::operator=(const Database& rhs) {
  if (this == &rhs) {
    return *this;
  }
  Clear();
  std::map<std::string, DbTable*> temp;
  try {
    for (const auto& table_pair : rhs.tables_) {
      temp[table_pair.first] = new DbTable(*table_pair.second);
    }
  } catch (const std::bad_alloc&) {
    throw;
  }
  for (const auto& table_pair : rhs.tables_) {
    delete tables_[table_pair.first];
  }
  tables_ = temp;  // will work after db_assignment work
  return *this;
}
Database::~Database() { Clear(); }

void Database::Clear() {  // use the same logic in ~DbTable() too;
  for (auto& table_pair : tables_) {
    delete table_pair.second;
  }
  tables_.clear();
}
std::ostream& operator<<(std::ostream& os, const Database& db) {
  for (const auto& table_pair : db.tables_) {
    os << table_pair.first << "\n";
    os << table_pair.second << "\n";
  }
  return os;
}

// Pointer is an address of an object/variable
// Reference is a nickname of a variable
// if change reference, change the variable too