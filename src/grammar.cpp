#include <grammar.hpp>

namespace parsing {

Grammar::Grammar(basic_istream<char>& is) {
  is >> start_;

  is >> std::noskipws;

  std::istream_iterator<char> it(is);
  std::istream_iterator<char> end;
  std::string str_grammar(it, end);

  ConstructVecRules(str_grammar);
}

Grammar::Grammar(const string& start, const string& str_grammar) : start_(start) {
  ConstructVecRules(str_grammar); 
  AddToMap(rules_);
  InitHelperSets();
}

Grammar::Grammar(const string& start, const vector<Rule>& rules) : start_(start), rules_(rules)  {
  AddToMap(rules_);
  InitHelperSets();
}

void Grammar::ConstructVecRules(const string& str_grammar) {
  ParseRulesHelper parse_string(str_grammar);

  while (parse_string.HasNext()) {
    parse_string.SkipSpaces();
    
    vector<Rule> rules = Rule::ReadRuleLine(parse_string);
    rules_.insert(rules_.cend(), rules.begin(), rules.end());
  }
}

void Grammar::AddToMap(const vector<Rule>& rules) {
  for (const Rule& rule: rules) {
    rules_map_.insert({*rule.GetLhs().data, rule.GetRhs()});
  }
}

void Grammar::InitHelperSets() {
  for (const auto& rule : rules_map_) {
    non_terminals_.insert(rule.first);

    for (const Token& token : rule.second) {
      if (token.is_term) {
        terminals_.insert(*token.data);
      } else {
        non_terminals_.insert(*token.data);
      }
    }
  }
}
const Grammar::RulesMap& Grammar::GetRulesMap() const {
  return rules_map_;
}
const vector<Rule>& Grammar::GetRulesVec() const {
  return rules_;
};
const set<string>& Grammar::GetTerminals() const {
  return terminals_;
}
const set<string>& Grammar::GetNonTerminals() const {
  return non_terminals_;
}
const string& Grammar::GetStart() const {
  return start_;
};

void Grammar::Print(std::ostream& os) const {
  for (const Rule& rule : GetRulesVec()) {
    std::cout << *rule.GetLhs().data << " : ";
    for (int i = 0; i < rule.GetRhs().size(); ++i) {
      const Token& token = rule.GetRhs(i);
      if (token.is_term) {
        std::cout << "'" << *token.data << "'";
      } else {
        std::cout << *token.data;
      }
      if (i != rule.GetRhs().size() - 1) {
        std::cout << " | ";
      }
    }
    std::cout << ";\n";
  }
}

const set<string> Grammar::GetLhsForWord(const string& word) const {
  set<string> nonterms;
  
  for (const Rule& rule: GetRulesVec()) {
    if (rule.GetRhs(0).is_term && *rule.GetRhs(0).data == word) {
      nonterms.insert(*rule.GetLhs().data);
    }
  }

  return nonterms;
}

} // namespace parsing
