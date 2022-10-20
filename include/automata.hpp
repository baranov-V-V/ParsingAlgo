#ifndef AUTOMATA_AUTOMATA_H_
#define AUTOMATA_AUTOMATA_H_

#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>

#include "transition.hpp"

using std::map;
using std::multiset;
using std::set;
using std::unordered_map;
using std::vector;
using std::basic_istream;

class Automata {
 public:
  /**
   * @brief Construct a new Automata object from input stream in following way:
   * (int) alphabet_count 
   * (int[]) alphabet
   * (int) start_state
   * (int) transitions_count
   * ({in, char, int}[]) transitions in form {"from" "letter" "to"}
   * (int) final_states_count
   * (int[]) final states
   *
   * @param in
   */
  Automata(basic_istream<char>& in);

  Automata(const set<char>& alphabet, const vector<Transition>& transitions,
           const int start, const set<int>& final_states);

  const set<char>& get_alphabet() const;

  const vector<Transition>& get_all_vec_transitions() const;

  const multiset<Transition>& get_transitions(const int state) const;

  const unordered_map<int, multiset<Transition>>& get_all_set_transitions()
      const;

  const int get_start() const;

  const set<int>& get_final_states() const;

  const set<int>& get_states() const;

  void to_doa(const char* filename);

 private:
  int start_ = 0;
  set<char> alphabet_;
  set<int> states_;

  vector<Transition> transitions_;
  set<int> final_states_;
  unordered_map<int, multiset<Transition>> transitions_per_state_;

  void read_alphabet(basic_istream<char>& in);
  void read_start_state(basic_istream<char>& in);
  void read_transitions(basic_istream<char>& in);
  void read_final_states(basic_istream<char>& in);

  void init_states();

  void init_transitions_per_state();
};

#endif  // AUTOMATA_AUTOMATA_H_