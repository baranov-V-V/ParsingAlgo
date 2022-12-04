#ifndef PARSING_GRAMMAR_H_
#define PARSING_GRAMMAR_H_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <set>
#include <sstream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>
#include <map>

#include <rule.hpp>

using std::basic_istream;
using std::set;
using std::string;
using std::unordered_set;
using std::vector;

namespace parsing {

class Grammar {
 public:
  typedef std::multimap<std::string, const TokenSeq&> RulesMap;
  
  Grammar(basic_istream<char>& is);

  Grammar(const string& start, const string& str_grammar);

  Grammar(const string& start, const vector<Rule>& rules);

  const RulesMap& GetRulesMap() const;
  const vector<Rule>& GetRulesVec() const;
  const set<string>& GetTerminals() const;
  const set<string>& GetNonTerminals() const;
  const set<string> GetLhsForWord(const string& word) const;
  const string& GetStart() const;
  
  void Print(std::ostream& os) const;

  friend std::ostream& operator<<(std::ostream& os, const Grammar& grammar) {
    grammar.Print(os);
    return os;
  }

 private:
  RulesMap rules_map_;

  vector<Rule> rules_;

  set<string> terminals_;
  set<string> non_terminals_;

  string start_;

  void ConstructVecRules(const string& str_grammar);
  void AddToMap(const vector<Rule>& rules);
  void InitHelperSets(); 
};

}  // namespace parsing

#endif  // PARSING_GRAMMAR_H_H
