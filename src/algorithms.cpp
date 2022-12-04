#include <algorithms.hpp>

namespace parsing {

CYKTable::CYKTable(const Grammar& grammar, int sentence_size) {
  for (const string& non_term : grammar.GetNonTerminals()) {
    table_.insert(
        {non_term, vector<vector<bool>>(sentence_size,
                                        vector<bool>(sentence_size, false))});
  }
}

bool CYKTable::Get(const string& nonterm, int i, int j) {
  return table_.at(nonterm).at(i).at(j);
}

void CYKTable::Set(const string& nonterm, int i, int j, bool val) {
  table_.at(nonterm).at(i).at(j) = val;
}

bool CYK(const Grammar& grammar, vector<string> sentence) {
  CYKTable table(grammar, sentence.size());

  for (int i = 0; i < sentence.size(); ++i) {
    set<string> lhs_set = grammar.GetLhsForWord(sentence.at(i));
    for (const string& lhs : lhs_set) {
      table.Set(lhs, i, i, true);
    }
  }

  for (int i = 1; i < sentence.size(); ++i) {
    for (int j = i; j < sentence.size(); ++j) {
      for (int k = j - i; k < j; ++k) {
        for (const Rule& rule : grammar.GetRulesVec()) {
          if (!rule.GetRhs(0).is_term) {
            if (table.Get(*rule.GetRhs(0).data, j - i, k) &&
                table.Get(*rule.GetRhs(1).data, k + 1, j)) {
              table.Set(*rule.GetLhs().data, j - i, j, true);
            }
          }
        }
      }
    }
  }

  return table.Get(grammar.GetStart(), 0, sentence.size() - 1);
}

}  // namespace parsing
