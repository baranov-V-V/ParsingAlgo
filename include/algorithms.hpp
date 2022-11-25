#ifndef PARSING_ALGORITHMS_H_
#define PARSING_ALGORITHMS_H_

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#include <rule.hpp>
#include <grammar.hpp>
#include <situation.hpp>

using std::vector;
using std::string;
using std::unordered_map;

namespace parsing {

typedef set<Situation> SituationList;

class SituationLists {
 public:
  SituationLists(size_t size);

  const SituationList& GetList(int index) const;

  void Insert(int index, const Situation& situation);

  bool Contains(int index, const Situation& situation);

 private:
  vector<SituationList> situation_lists_;
};

void EarleyScan(SituationLists& situation_lists, const vector<string>& sentence,
                int situation_idx);
void EarleyComplete(const Grammar& grammar, SituationLists& situation_lists,
                    const vector<string>& sentence, int situation_idx);
void EarleyPredict(const Grammar& grammar, SituationLists& situation_lists,
                   const vector<string>& sentence, int situation_idx);

bool Earley(const Grammar& grammar, vector<string> sentence);

} // namespace parsing 

#endif // PARSING_ALGORITHMS_H_