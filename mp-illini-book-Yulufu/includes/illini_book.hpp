#ifndef ILLINI_BOOK_HPP
#define ILLINI_BOOK_HPP

#include <map>
#include <set>
#include <string>
#include <vector>

class IlliniBook {
public:
  IlliniBook(const std::string& people_fpath,
             const std::string& relations_fpath);
  IlliniBook(const IlliniBook& rhs) = delete;
  IlliniBook& operator=(const IlliniBook& rhs) = delete;
  ~IlliniBook();
  bool AreRelated(int uin_1, int uin_2) const;
  bool AreRelated(int uin_1, int uin_2, const std::string& relationship) const;
  int GetRelated(int uin_1, int uin_2) const;
  int GetRelated(int uin_1, int uin_2, const std::string& relationship) const;
  std::vector<int> GetSteps(int uin, int n) const;
  size_t CountGroups() const;
  size_t CountGroups(const std::string& relationship) const;
  size_t CountGroups(const std::vector<std::string>& relationships) const;
  // helper
  void BSF(std::set<int>& visited, int cur_uin) const;
  void BSFRelated(std::set<int>& visited,
                  int cur_uin,
                  const std::string& relationship) const;
  void BSFRelatedVect(std::set<int>& visited,
                      int cur_uin,
                      const std::vector<std::string>& relationships) const;

private:
  std::map<int, std::vector<std::pair<int, std::string>>>
      organized_relationship_map_;
};

#endif
