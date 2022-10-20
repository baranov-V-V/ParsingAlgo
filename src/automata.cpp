#include "automata.hpp"

#include <iterator>
#include <fstream>

Automata::Automata(basic_istream<char>& in) {
  read_alphabet(in);
  read_start_state(in);
  read_transitions(in);
  read_final_states(in);

  init_states();
  init_transitions_per_state();
}

Automata::Automata(const set<char>& alphabet,
                   const vector<Transition>& transitions, const int start,
                   const set<int>& final_states)
    : alphabet_(alphabet),
      transitions_(transitions),
      final_states_(final_states),
      start_(start) {
  init_states();
  init_transitions_per_state();
}

const set<char>& Automata::get_alphabet() const { return alphabet_; }

const vector<Transition>& Automata::get_all_vec_transitions() const {
  return transitions_;
}

const multiset<Transition>& Automata::get_transitions(const int state) const {
  return transitions_per_state_.at(state);
}

const unordered_map<int, multiset<Transition>>&
Automata::get_all_set_transitions() const {
  return transitions_per_state_;
}

const int Automata::get_start() const { return start_; }

const set<int>& Automata::get_final_states() const { return final_states_; }

const set<int>& Automata::get_states() const { return states_; }

void Automata::to_doa(const char* filename) {
  std::fstream stream(filename);
  
  stream << "DOA: v1\n";
  stream << "Start: q_" << start_ << "\n";

  stream << "Acceptance: ";
  auto it = final_states_.begin();
  stream << "q_" << *it;

  it = std::next(it);
  while (it != final_states_.end()) {
    stream << " & q_" << *it;
    it = std::next(it);
  }
  stream << "\n";

  stream << "--BEGIN--\n";

  for (int state : states_) {
    if (get_transitions(state).size() > 0) {
      stream << "State q_" << state << "\n";
      for (const Transition& trans : get_transitions(state)) {
        if (trans.from == state) {
          stream << "-> " << trans.letter << " q_" << trans.to << "\n";
        }
      }
    }
  }

  stream << "--END--\n";
}

void Automata::init_states() {
  states_.insert(start_);
  for (const Transition& trans : transitions_) {
    if (!alphabet_.contains(trans.letter)) {
      throw std::invalid_argument("No such letter in automata: [" +
                                  std::to_string(trans.letter) + "]");
    }
    states_.insert(trans.from);
    states_.insert(trans.to);
  }
}

void Automata::init_transitions_per_state() {
  for (int state : states_) {
    transitions_per_state_[state] = {};
  }

  for (const Transition& trans : transitions_) {
    if (!alphabet_.contains(trans.letter)) {
      throw std::invalid_argument("No such letter in automata: [" +
                                  std::to_string(trans.letter) + "]");
    }
    transitions_per_state_[trans.from].insert(trans);
  }
}

void Automata::read_alphabet(basic_istream<char>& in) {
  int alphabet_count = 0;
  char letter = 0;
  in >> alphabet_count;
  for (int i = 0; i < alphabet_count; ++i) {
    in >> letter;
    alphabet_.insert(letter);
  }
};

void Automata::read_start_state(basic_istream<char>& in) {
  in >> start_;
};

void Automata::read_transitions(basic_istream<char>& in) {
  int transtions_count = 0;
  int from = 0;
  char trans_letter = 0;
  int to = 0;
  in >> transtions_count;
  for (int i = 0; i < transtions_count; ++i) {
    in >> from >> trans_letter >> to;
    transitions_.push_back(Transition(from, trans_letter, to));
  }
};

void Automata::read_final_states(basic_istream<char>& in) {
  int final_state_count = 0;
  int final_state = 0;
  in >> final_state_count;
  for (int i = 0; i < final_state_count; ++i) {
    in >> final_state;
    final_states_.insert(final_state);
  }
};
