#include <algorithms.hpp>

namespace parsing {

SituationLists::SituationLists(size_t size) : situation_lists_(size) {}

const SituationList& SituationLists::GetList(int index) const {
  return situation_lists_.at(index);
}

void SituationLists::Insert(int index, const Situation& situation) {
  situation_lists_.at(index).insert(situation);
}

bool SituationLists::Contains(int index, const Situation& situation) {
  return situation_lists_.at(index).contains(situation);
}

void EarleyScan(SituationLists& situation_lists, const vector<string>& sentence,
                int situation_idx) {
  if (situation_idx == 0) {
    return;
  }
  for (const Situation& situation : situation_lists.GetList(situation_idx - 1)) {
    if (situation.IsPointTokenTerm() &&
        *situation.GetPointToken().data == sentence.at(situation_idx - 1)) {
      situation_lists.Insert(situation_idx, Situation::GetNextSituation(situation));
    }
  }
}

void EarleyComplete(const Grammar& grammar, SituationLists& situation_lists,
                    const vector<string>& sentence, int situation_idx) {
  for (const Situation& situation_i : situation_lists.GetList(situation_idx)) {
    if (situation_i.IsCompleted()) {
      for (const Situation& situation_j :
           situation_lists.GetList(situation_i.GetSituationPos())) {
        if (!situation_j.IsCompleted() &&
            situation_j.GetPointToken() == situation_i.GetLhs()) {
          situation_lists.Insert(situation_idx, Situation::GetNextSituation(situation_j));
        }
      }
    }
  }
};

void EarleyPredict(const Grammar& grammar, SituationLists& situation_lists,
                   const vector<string>& sentence, int situation_idx) {
  for (const Situation& situation : situation_lists.GetList(situation_idx)) {
    if (!situation.IsCompleted() && !situation.IsPointTokenTerm()) {
      for (const Rule& rule : grammar.GetRulesVec()) {
        if (situation.GetPointToken() == rule.GetLhs()) {
          situation_lists.Insert(situation_idx, Situation(rule, situation_idx, 0));
        }
      }
    }
  }
};

bool Earley(const Grammar& grammar, vector<string> sentence) {
  const string fake_start_token = "$";
  
  vector<Rule> earlry_grammar_rules = grammar.GetRulesVec();
  Rule fake_start_rule(Token(fake_start_token, false), vector<Token>({Token(grammar.GetStart(), false)}));
  earlry_grammar_rules.push_back(fake_start_rule);
  Grammar earley_grammar(fake_start_token, earlry_grammar_rules);

  SituationLists situation_lists(sentence.size() + 1);
  Situation fake_start_situation = Situation(fake_start_rule, 0, 0);
  situation_lists.Insert(0, fake_start_situation);

  for (int situation_idx = 0; situation_idx <= sentence.size(); ++situation_idx) {
    EarleyScan(situation_lists, sentence, situation_idx);
    int situation_list_size = 0;
    bool is_changed = true;
    while (is_changed) {
      situation_list_size = situation_lists.GetList(situation_idx).size();
      EarleyComplete(earley_grammar, situation_lists, sentence, situation_idx);
      EarleyPredict(earley_grammar, situation_lists, sentence, situation_idx);
      if (situation_lists.GetList(situation_idx).size() == situation_list_size) {
        is_changed = false;
      }
    }
  }

  Situation target_situation = Situation::GetNextSituation(fake_start_situation);
  return situation_lists.Contains(sentence.size(), target_situation);
}

}  // namespace parsing
