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

  const set<char>& GetAlphabet() const;

  const vector<Transition>& GetAllVecTransitions() const;

  const multiset<Transition>& GetTransitions(const int state) const;

  const unordered_map<int, multiset<Transition>>& GetAllSetTransitions()
      const;

  const int GetStart() const;

  const set<int>& GetFinalStates() const;

  const set<int>& GetStates() const;

  void ToDoa(const char* filename);

 private:
  int start_ = 0;
  set<char> alphabet_;
  set<int> states_;

  vector<Transition> transitions_;
  set<int> final_states_;
  unordered_map<int, multiset<Transition>> transitions_per_state_;

  void ReadAlphabet(basic_istream<char>& in);
  void ReadStartState(basic_istream<char>& in);
  void ReadTransitions(basic_istream<char>& in);
  void ReadFinalStates(basic_istream<char>& in);

  void InitStates();

  void InitTransitionsPerState();
};

#endif  // AUTOMATA_AUTOMATA_H_