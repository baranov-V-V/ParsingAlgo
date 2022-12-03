#include "automata_utils.hpp"

Automata AutomataUtils::ToDfa(const Automata& nfa) {
  vector<Transition> dfa_transitions = {};
  MultiState dfa_final_states = {};
  set<MultiState> dfa_states = {{nfa.GetStart()}};
  map<MultiState, int> dfa_states_ids = {{set<int>({nfa.GetStart()}), 0}};

  queue<MultiState> queue = {};
  queue.push({nfa.GetStart()});

  while (!queue.empty()) {
    const MultiState curr_state = queue.front();
    queue.pop();

    int curr_state_id = dfa_states_ids.at(curr_state);

    for (char letter : nfa.GetAlphabet()) {
      MultiState new_state = GetToMultiState(curr_state, letter, nfa);

      if (!dfa_states.contains(new_state)) {
        dfa_states_ids.insert({new_state, dfa_states.size()});
        dfa_states.insert(new_state);
        queue.push(new_state);
      }

      dfa_transitions.push_back(
          Transition(curr_state_id, letter, dfa_states_ids.at(new_state)));
    }

    for (int state : curr_state) {
      if (nfa.GetFinalStates().contains(state)) {
        dfa_final_states.insert(curr_state_id);
        break;
      }
    }
  }

  return Automata(nfa.GetAlphabet(), dfa_transitions, 0, dfa_final_states);
};

Automata AutomataUtils::ToCDfa(const Automata& dfa) {
  vector<Transition> full_dfa_transitions = dfa.GetAllVecTransitions();

  const int new_state = dfa.GetStates().size();
  map<int, map<char, bool>> needed_transitions = {};

  // init map
  for (int state : dfa.GetStates()) {
    needed_transitions.insert({state, map<char, bool>()});
    for (char letter : dfa.GetAlphabet()) {
      needed_transitions.at(state).insert(std::make_pair(letter, true));
    }
  }

  // mark map
  for (const Transition& trans : dfa.GetAllVecTransitions()) {
    needed_transitions.at(trans.from).at(trans.letter) = false;
  }

  bool is_full = true;
  // process map
  for (const auto& state_entry : needed_transitions) {
    for (const auto& letter_entry : state_entry.second) {
      if (letter_entry.second == true) {
        is_full = false;
        full_dfa_transitions.push_back(
            Transition(state_entry.first, letter_entry.first, new_state));
      }
    }
  }

  if (!is_full) {
    for (char letter : dfa.GetAlphabet()) {
      full_dfa_transitions.push_back(Transition(new_state, letter, new_state));
    }
  }

  return Automata(dfa.GetAlphabet(), full_dfa_transitions, dfa.GetStart(),
                  dfa.GetFinalStates());
};

Automata AutomataUtils::ToMCDfa(const Automata& cdfa) {
  map<int, int> state_group_curr = {};

  for (int state : cdfa.GetStates()) {
    state_group_curr.insert({state, 0});
  }

  for (int state : cdfa.GetFinalStates()) {
    state_group_curr.at(state) = 1;
  }

  while (true) {
    map<vector<int>, int> eq_classes = {};
    map<int, int> state_group_next = {};

    for (int state : cdfa.GetStates()) {
      vector<int> new_class = {state_group_curr.at(state)};
      for (char letter : cdfa.GetAlphabet()) {
        new_class.push_back(
            state_group_curr.at(GetToByLetter(cdfa, state, letter)));
      }

      if (!eq_classes.contains(new_class)) {
        eq_classes.insert({new_class, eq_classes.size()});
      }

      state_group_next.insert({state, eq_classes.at(new_class)});
    }

    if (state_group_curr == state_group_next) {
      break;
    }

    state_group_curr = state_group_next;
  }

  vector<Transition> mfdfa_transitions = {};
  for (const Transition& trans : cdfa.GetAllVecTransitions()) {
    Transition new_trans(state_group_curr.at(trans.from), trans.letter,
                         state_group_curr.at(trans.to));

    if (std::find(mfdfa_transitions.begin(), mfdfa_transitions.end(),
                  new_trans) == mfdfa_transitions.end()) {
      mfdfa_transitions.push_back(new_trans);
    }
  }

  set<int> mfdfa_final_states = {};
  for (int state : cdfa.GetFinalStates()) {
    mfdfa_final_states.insert(state_group_curr.at(state));
  }

  return Automata(cdfa.GetAlphabet(), mfdfa_transitions, cdfa.GetStart(),
                  mfdfa_final_states);
};

AutomataUtils::MultiState AutomataUtils::GetToMultiState(const MultiState& from,
                                                const char letter,
                                                const Automata& automata) {
  MultiState to = {};

  for (const Transition& trans : automata.GetAllVecTransitions()) {
    if (trans.letter == letter && from.contains(trans.from)) {
      to.insert(trans.to);
    }
  }

  return to;
}

int AutomataUtils::GetToByLetter(Automata automata, int from, char letter) {
  for (const Transition& trans : automata.GetTransitions(from)) {
    if (trans.letter == letter) {
      return trans.to;
    }
  }
  return -1;
}