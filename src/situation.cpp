#include <situation.hpp>

namespace parsing {

Situation::Situation(const Rule& rule, int situation_pos,
                     int point_position)
    : rule_(rule),
      situation_pos_(situation_pos),
      point_pos_(point_position) {}

bool Situation::IsPointTokenTerm() const {
  if (IsCompleted()) {
    return false;
  }
  return rule_.GetRhs().at(point_pos_).is_term;
}

const Token& Situation::GetPointToken() const {
  return rule_.GetRhs().at(point_pos_);
}

const Token& Situation::GetLhs() const { return rule_.GetLhs(); }

const TokenSeq& Situation::GetRhs() const { return rule_.GetRhs(); }

bool Situation::IsCompleted() const {
  return point_pos_ == rule_.GetRhs().size();
}

int Situation::GetSituationPos() const { return situation_pos_; }
int Situation::GetPointPos() const { return point_pos_; }

Situation Situation::GetNextSituation(const Situation& situation) {
  return Situation(situation.rule_, situation.situation_pos_,
                   situation.point_pos_ + 1);
}

bool Situation::operator==(const Situation& other) const {
  return (rule_ == other.rule_ && situation_pos_ == other.situation_pos_ &&
          point_pos_ == other.point_pos_);
}

bool Situation::operator<(const Situation& other) const {
  if (rule_ != other.rule_) {
    return rule_ < other.rule_;
  } else if (point_pos_ != other.point_pos_) {
    return point_pos_ < other.point_pos_;
  }

  return situation_pos_ < other.situation_pos_;
}

}  // namespace parsing