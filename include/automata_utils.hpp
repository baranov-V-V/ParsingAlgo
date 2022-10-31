#include <algorithm>
#include <map>
#include <queue>
#include <set>
#include <vector>

#include "automata.hpp"
#include "transition.hpp"

using std::map;
using std::queue;
using std::set;
using std::vector;

class AutomataUtils {
 private:
  using MultiState = set<int>;

 public:
  /**
   * @brief Constructs new DFA Automata from NFA
   *
   * @param nfa
   * @return Automata
   */
  static Automata ToDfa(const Automata& nfa);

  /**
   * @brief Constructs new full DFA from DFA
   *
   * @param dfa
   * @return Automata
   */
  static Automata ToCDfa(const Automata& dfa);

  /**
   * @brief Constructs new minimal full DFA from full DFA
   *
   * @param fullDfa
   * @return Automata
   */
  static Automata ToMCDfa(const Automata& cdfa);

 private:
  static MultiState GetToMultiState(const MultiState& from, const char letter,
                           const Automata& automata);

  static bool IsFull(map<int, set<char>>& letters_to_full_states);

  static int GetToByLetter(Automata automata, int from, char letter);
};