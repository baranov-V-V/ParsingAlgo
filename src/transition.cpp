#include "transition.hpp"

Transition::Transition(int from, char letter, int to)
    : from(from), to(to), letter(letter) {}

bool Transition::operator==(const Transition& rhs) const {
  return (from == rhs.from) && (to == rhs.to) && (letter == rhs.letter);
}

bool Transition::operator<(const Transition& rhs) const {
  if (from != rhs.from) {
    return from < rhs.from;
  } else if (from == rhs.from && to != rhs.to) {
    return to < rhs.to;
  } else if (from == rhs.from && to == rhs.to) {
    return letter < rhs.letter;
  }
  return false;
}
