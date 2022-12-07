#include <initializer_list>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "db.hpp"
#include "db_table.hpp"
int main() {
  // write informal tests here
  DbTable db;
  db.AddColumn({"name", DataType::kString});
  db.AddColumn({"UIN", DataType::kInt});
  db.AddRow({"Yulu", "123"});
  db.AddRow({"Sora", "23"});
  db.AddRow({"Tim", "33"});
  db.AddRow({"Fan", "26"});

  db.AddColumn({"email", DataType::kInt});
  db.AddColumn({"address", DataType::kInt});
  db.AddColumn({"parent", DataType::kDouble});

  db.AddRow({"a", "1", "2", "3", "4.4 "});

  DbTable db2(db);

  // db.DeleteColumnByIdx(0);

  std::cout << db2 << std::endl;

  return 0;
}

// Asan -g -fsanitize=address,null -fno-omit-frame-pointer
// Valgrind valgrind ./bin/exec