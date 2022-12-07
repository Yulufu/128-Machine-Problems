#include "illini_book.hpp"

#include <fstream>
#include <map>
#include <queue>
#include <set>
#include <vector>

#include "utilities.hpp"

// Your code here!
// check MP7 output operator to print out IlliBook
/*when checking relationship of one type, you want to ignore those with
 * incorrect relationship. See the GetRelatted for reference*/
IlliniBook::IlliniBook(const std::string& people_fpath,
                       const std::string& relations_fpath) {
  std::ifstream ifs(people_fpath);
  if (!ifs.is_open()) throw std::runtime_error("file is not open");
  int uin = 0;
  while (ifs.good()) {
    ifs >> uin;
    if (ifs.fail()) {
      ifs.clear();
    }
    // std::cout << uin << std::endl;
    organized_relationship_map_[uin] =
        std::vector<std::pair<int, std::string>>();
  }
  std::ifstream ifsp(relations_fpath);
  if (!ifsp.is_open())
    throw std::runtime_error("relationsihp file is not open");
  for (std::string line; std::getline(ifsp, line); line = "") {
    std::vector<std::string> csv_vect = utilities::Split(line, ',');
    // {"1", "3", "128"}
    // convert csv_vector.at(1) and csv_vector.at(0) to int
    // pair for 1
    int pair_key = std::stoi(csv_vect.at(1));
    int map_key = std::stoi(csv_vect.at(0));
    std::pair<int, std::string> p(pair_key, csv_vect.at(2));
    organized_relationship_map_[map_key].push_back(p);
    // pair for 3
    int pair_key2 = std::stoi(csv_vect.at(0));
    int map_key2 = std::stoi(csv_vect.at(1));
    std::pair<int, std::string> p2(pair_key2, csv_vect.at(2));
    organized_relationship_map_[map_key2].push_back(p2);
  }
  // for (auto const& x : organized_relationship_map_) {
  //   std::cout << x.first << ":";
  //   for (size_t i = 0; i < x.second.size(); i++) {
  //     std::cout << x.second[i].first << ", " << x.second[i].second << "\t";
  //   }
  // }
}

IlliniBook::~IlliniBook() = default;

bool IlliniBook::AreRelated(int uin_1, int uin_2) const {
  std::queue<int> q;
  std::set<int> visited;
  q.push(uin_1);
  visited.insert(uin_1);
  while (!q.empty()) {  // need to edit from here
    int cur_uin = q.front();
    q.pop();  // remove the frontest int in the queue
    if (cur_uin == uin_2) return true;
    // gives the vector
    // neighbor of 1 is 3,2,6
    for (const auto& [first, sec] : organized_relationship_map_.at(cur_uin)) {
      if (!visited.contains(first)) {
        q.push(first);
        visited.insert(first);
      }
    }
  }
  return false;
}
bool IlliniBook::AreRelated(int uin_1,
                            int uin_2,
                            const std::string& relationship) const {
  if (!AreRelated(uin_1, uin_2)) {
    return false;
  }
  std::queue<int> q;
  std::set<int> visited;
  q.push(uin_1);
  visited.insert(uin_1);
  while (!q.empty()) {
    int cur_uin = q.front();
    q.pop();
    for (const auto& [first, sec] : organized_relationship_map_.at(cur_uin)) {
      if (first == uin_2 && sec == relationship) {
        return true;
      }
      if (!visited.contains(first) &&
          sec == relationship) {  // part to add neighbor
        q.push(first);
        visited.insert(first);
      }
    }
  }
  return false;
}

int IlliniBook::GetRelated(int uin_1, int uin_2) const {
  if (!AreRelated(uin_1, uin_2)) {
    return -1;
  }
  int length = 0;
  std::queue<int> q;
  std::queue<int> length_of_cur;
  std::set<int> visited;
  q.push(uin_1);
  length_of_cur.push(length);
  visited.insert(uin_1);
  while (!q.empty()) {
    int cur_uin = q.front();
    int cur_length = length_of_cur.front();
    q.pop();  // remove the frontest int in the queue
    length_of_cur.pop();
    if (cur_uin == uin_2) {
      return cur_length;
    }
    for (const auto& [first, sec] : organized_relationship_map_.at(cur_uin)) {
      if (!visited.contains(first)) {
        q.push(first);
        length = cur_length + 1;
        length_of_cur.push(length);
        visited.insert(first);
      }
    }
  }
  return -1;
}
int IlliniBook::GetRelated(int uin_1,
                           int uin_2,
                           const std::string& relationship) const {
  if (!AreRelated(uin_1, uin_2)) {
    return -1;
  }
  int length = 0;
  std::queue<int> q;
  std::queue<int> length_of_cur;
  std::set<int> visited;
  q.push(uin_1);
  length_of_cur.push(length);
  visited.insert(uin_1);
  while (!q.empty()) {
    int cur_uin = q.front();
    int cur_length = length_of_cur.front();
    q.pop();  // remove the frontest int in the queue
    length_of_cur.pop();
    if (cur_uin == uin_2) {
      return cur_length;
    }
    for (const auto& [first, sec] : organized_relationship_map_.at(cur_uin)) {
      if (!visited.contains(first) && sec == relationship) {
        q.push(first);
        length = cur_length + 1;
        length_of_cur.push(length);
        visited.insert(first);
      }
    }
  }
  return -1;
}
std::vector<int> IlliniBook::GetSteps(int uin, int n) const {
  std::vector<int> n_steps_away;
  int length = 0;
  std::queue<int> q;
  std::queue<int> length_of_cur;
  std::set<int> visited;
  q.push(uin);
  length_of_cur.push(length);
  visited.insert(uin);
  while (!q.empty()) {
    int cur_uin = q.front();
    int cur_length = length_of_cur.front();
    if (cur_length == n) {
      while (!q.empty()) {
        int cur_node = q.front();
        n_steps_away.push_back(cur_node);
        q.pop();
      }
      return n_steps_away;
    }
    q.pop();
    length_of_cur.pop();
    for (const auto& [first, sec] : organized_relationship_map_.at(cur_uin)) {
      if (!visited.contains(first)) {
        q.push(first);
        length = cur_length + 1;
        length_of_cur.push(length);
        visited.insert(first);
      }
    }
  }
  return n_steps_away;
} /*n is how many steps away*/

void IlliniBook::BSF(std::set<int>& visited, int cur_uin) const {
  std::queue<int> q;
  q.push(cur_uin);
  visited.insert(cur_uin);
  while (!q.empty()) {
    int cur_uin = q.front();
    q.pop();  // remove the frontest int in the queue
    // if (cur_uin == uin_2) return true;
    for (const auto& [first, sec] : organized_relationship_map_.at(cur_uin)) {
      if (!visited.contains(first)) {
        q.push(first);
        visited.insert(first);
      }
    }
  }
}
size_t IlliniBook::CountGroups() const {  // counting connected component
  size_t num_of_groups = 0;
  std::set<int> visited;
  int cur_uin = 0;
  for (const auto& [first, sec] : organized_relationship_map_) {
    cur_uin = first;
    if (!visited.contains(first)) {
      BSF(visited, cur_uin);  // count how many times call this func
      num_of_groups += 1;
    }
  }
  return num_of_groups;
}
void IlliniBook::BSFRelated(std::set<int>& visited,
                            int cur_uin,
                            const std::string& relationship) const {
  std::queue<int> q;
  q.push(cur_uin);
  visited.insert(cur_uin);
  while (!q.empty()) {
    int cur_uin = q.front();
    q.pop();  // remove the frontest int in the queue
    // if (cur_uin == uin_2) return true;
    for (const auto& [first, sec] : organized_relationship_map_.at(cur_uin)) {
      if (!visited.contains(first) && sec == relationship) {
        q.push(first);
        visited.insert(first);
      }
    }
  }
}
size_t IlliniBook::CountGroups(const std::string& relationship) const {
  size_t num_of_groups = 0;
  std::set<int> visited;
  int cur_uin = 0;
  for (const auto& [first, sec] : organized_relationship_map_) {
    cur_uin = first;
    if (!visited.contains(first)) {
      BSFRelated(visited, cur_uin, relationship);
      // BFS  need to handle the relationship
      num_of_groups += 1;
    }
  }
  return num_of_groups;
}

void IlliniBook::BSFRelatedVect(
    std::set<int>& visited,
    int cur_uin,
    const std::vector<std::string>& relationships) const {
  std::queue<int> q;
  q.push(cur_uin);
  visited.insert(cur_uin);
  while (!q.empty()) {
    int cur_uin = q.front();
    q.pop();  // remove the frontest int in the queue
    // if (cur_uin == uin_2) return true;
    for (const auto& [first, sec] : organized_relationship_map_.at(cur_uin)) {
      for (size_t i = 0; i < relationships.size(); ++i) {
        if (!visited.contains(first) && sec == relationships.at(i)) {
          q.push(first);
          visited.insert(first);
        }
      }
    }
  }
}
size_t IlliniBook::CountGroups(
    const std::vector<std::string>& relationships) const {
  size_t num_of_groups = 0;
  std::set<int> visited;
  int cur_uin = 0;
  for (const auto& [first, sec] : organized_relationship_map_) {
    cur_uin = first;
    if (!visited.contains(first)) {
      BSFRelatedVect(visited, cur_uin, relationships);
      // BFS  need to handle the relationship
      num_of_groups += 1;
    }
  }
  return num_of_groups;
}