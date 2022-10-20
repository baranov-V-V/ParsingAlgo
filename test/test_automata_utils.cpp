#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "automata.hpp"
#include "automata_utils.hpp"
#include "gtest/gtest.h"

using std::set;
using std::vector;

bool is_eq_transitions(
    const unordered_map<int, multiset<Transition>>& transitions_lhs,
    const unordered_map<int, multiset<Transition>>& transitions_rhs) {
  bool eq = true;
  for (const auto& state_entry : transitions_lhs) {
    if (!transitions_rhs.contains(state_entry.first) ||
        transitions_rhs.at(state_entry.first) != state_entry.second) {
      eq = false;
      break;
    }
  }

  return eq;
}

TEST(ConstructAutomata, IStream) {
  std::string input_automata = {};
  input_automata +=
      "3 a b c\n"
      "0\n"
      "5\n"
      "0 a 2\n"
      "0 a 3\n"
      "0 b 2\n"
      "2 b 4\n"
      "0 a 2\n"
      "2 2 4\n";

  std::istringstream ss(input_automata);

  Automata automata(ss);

  ASSERT_EQ(automata.get_alphabet(), std::set<char>({'a', 'b', 'c'}));
  ASSERT_EQ(automata.get_states(), std::set<int>({0, 2, 3, 4}));
  ASSERT_EQ(automata.get_start(), 0);
  ASSERT_EQ(automata.get_all_vec_transitions().size(), 5);
  ASSERT_EQ(
      automata.get_all_vec_transitions(),
      std::vector<Transition>(
          {{0, 'a', 2}, {0, 'a', 3}, {0, 'b', 2}, {2, 'b', 4}, {0, 'a', 2}}));
  ASSERT_EQ(automata.get_final_states(), std::set<int>({2, 4}));
}

TEST(AutomataUtil, ToDfa) {
  const set<char> alphabet = {'a', 'b'};
  const int start = 0;
  const set<int> final_states = {0, 1};
  const vector<Transition> transitions = {{0, 'a', 1}, {0, 'a', 2}, {0, 'b', 2},
                                          {1, 'a', 0}, {1, 'b', 2}, {1, 'b', 2},
                                          {1, 'b', 1}};

  Automata nfa(alphabet, transitions, start, final_states);
  Automata dfa = AutomataUtils::to_dfa(nfa);

  const unordered_map<int, multiset<Transition>> correct_transitions = {
      {0, {{0, 'a', 1}, {0, 'b', 2}}},
      {1, {{1, 'a', 0}, {1, 'b', 1}}},
      {2, {{2, 'a', 3}, {2, 'b', 3}}},
      {3, {{3, 'a', 3}, {3, 'b', 3}}},
  };

  ASSERT_TRUE(
      is_eq_transitions(correct_transitions, dfa.get_all_set_transitions()));
  ASSERT_EQ(nfa.get_alphabet(), dfa.get_alphabet());
  ASSERT_EQ(nfa.get_start(), 0);
  ASSERT_EQ(nfa.get_final_states(), std::set<int>({0, 1}));
}

TEST(AutomataUtil, ToFullDfa) {
  const set<char> alphabet = {'a', 'b'};
  const int start = 0;
  const set<int> final_states = {1, 2};
  const vector<Transition> transitions = {
      {0, 'a', 1}, {0, 'b', 2}, {2, 'b', 1}};

  Automata dfa(alphabet, transitions, start, final_states);
  Automata fdfa = AutomataUtils::to_cdfa(dfa);
  fdfa.to_doa("aaa.doa");

  const unordered_map<int, multiset<Transition>> correct_transitions = {
      {0, {{0, 'a', 1}, {0, 'b', 2}}},
      {1, {{1, 'a', 3}, {1, 'b', 3}}},
      {2, {{2, 'a', 3}, {2, 'b', 1}}},
      {3, {{3, 'a', 3}, {3, 'b', 3}}},
  };

  ASSERT_TRUE(
      is_eq_transitions(correct_transitions, fdfa.get_all_set_transitions()));
  ASSERT_EQ(fdfa.get_alphabet(), dfa.get_alphabet());
  ASSERT_EQ(fdfa.get_start(), 0);
  ASSERT_EQ(fdfa.get_final_states(), std::set<int>({1, 2}));
}

TEST(AutomataUtil, ToMinFullDfa) {
  const set<char> alphabet = {'a', 'b'};
  const int start = 0;
  const vector<Transition> transitions = {
      {0, 'a', 1}, {0, 'b', 2}, {1, 'a', 0}, {1, 'b', 4},
      {2, 'a', 4}, {2, 'b', 5}, {3, 'a', 4}, {3, 'b', 5},
      {4, 'a', 4}, {4, 'b', 5}, {5, 'a', 5}, {5, 'b', 5},
  };
  const set<int> final_states = {2, 3, 4};

  Automata fdfa(alphabet, transitions, start, final_states);
  Automata mfdfa = AutomataUtils::to_mcdfa(fdfa);

  const unordered_map<int, multiset<Transition>> correct_transitions = {
      {0, {{0, 'a', 0}, {0, 'b', 1}}},
      {1, {{1, 'a', 1}, {1, 'b', 2}}},
      {2, {{2, 'a', 2}, {2, 'b', 2}}}};

  ASSERT_TRUE(
      is_eq_transitions(correct_transitions, mfdfa.get_all_set_transitions()));
  ASSERT_EQ(mfdfa.get_alphabet(), alphabet);
  ASSERT_EQ(mfdfa.get_start(), 0);
  ASSERT_EQ(mfdfa.get_final_states(), std::set<int>({1}));
}