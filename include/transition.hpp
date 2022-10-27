#ifndef AUTOMATA_TRANSTION_H_
#define AUTOMATA_TRANSTION_H_

struct Transition {
  const int from;
  const int to;
  const char letter;

  Transition(int from, char letter, int to);
  Transition(const Transition& transition);

  bool operator==(const Transition& rhs) const;
  bool operator<(const Transition& rhs) const;
};

#endif  // AUTOMATA_TRANSTION_H_