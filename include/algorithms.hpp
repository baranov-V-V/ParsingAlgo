#ifndef PARSING_ALGORITHMS_H_
#define PARSING_ALGORITHMS_H_

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#include <rule.hpp>
#include <grammar.hpp>

using std::vector;
using std::string;
using std::unordered_map;

namespace parsing {
  
class CYKTable {
 public:
  CYKTable(const Grammar& grammar, int sentence_size);

  bool Get(const string& nonterm, int i, int j);

  void Set(const string& nonterm, int i, int j, bool val);
 private:
  unordered_map<string, vector<vector<bool>>> table_ = {};
};

bool CYK(const Grammar& grammar, vector<string> sentence);

} // namespace parsing 

#endif // PARSING_ALGORITHMS_H_