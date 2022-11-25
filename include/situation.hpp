#ifndef PARSING_SITUATION_H_
#define PARSING_SITUATION_H_

#include <rule.hpp>

namespace parsing {
  
class Situation {
 public:
  Situation(const Rule& rule, int previous_level_position, int point_position);
  Situation(const Situation& other) = default;
  
  static Situation GetNextSituation(const Situation& situation);

  const Token& GetLhs() const;
  const TokenSeq& GetRhs() const;
  const Token& GetPointToken() const;

  bool IsPointTokenTerm() const;
  bool IsCompleted() const;

  int GetSituationPos() const;
  int GetPointPos() const;

  bool operator==(const Situation& other) const;
  bool operator<(const Situation& other) const;

 private:
  const Rule& rule_;
  int situation_pos_;
  int point_pos_;
};

} // namespace parsing

#endif