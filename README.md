# Automata and Parsing Algorithms

This is a library for storing and making operations with [automatas](https://en.wikipedia.org/wiki/Automata_theory) \
and formal [grammars](https://en.wikipedia.org/wiki/Formal_grammar)
You can add this library to your project via Cmake or write in ```src/main.cpp``` as a sandbox\
If you want to run test and code coverage before compilation run ```install.sh```\
To compile sandbox and tests use ```build.sh```\
To run test after compiling use ```run_tests.sh```\
All code coverage files are stored in ```build/ccov```

## Automata

Main class for storing any immutable Automata:

```C++
class Automata
```

Main class for operations with Automata is

```C++
class AutomataUtils;
```

### Creation of Automata

It can be constucted from an input stream like std::sin or std::istringstream

```C++
Automata(basic_istream<char>& in);
```

Automata should be discribed in following way:

`
(int) number of letters in alphabet
(char[]) alphabet
(int) start state
(int) number of transitions
({in, char, int}[]) transitions in form {"from" "letter" "to"}, brackets and quotes should be ommited
(int) number of final states
(int[]) final states
`

Examples:

`
3
a b c
0
5
0 a 2
0 a 3
0 b 2
2 b 4
0 a 2
2
2 4
`

Automata can be made from it's compontents:

```C++
Automata(const set<char>& alphabet, const vector<Transition>& transitions, const int start, const set<int>& final_states);
```

### Printing of Automata

Automata can be put into file with function

```C++
void to_doa(const char* filename);
```

which presents automata in DOA (Dolgoprudny HOA) format

`
automaton ::= header "--BEGIN--" body "--END--"

header ::= format-version header-start header-acceptance
format-version ::= "DOA:" STRING
header-start ::= "Start:" STRING
header-acceptance ::= "Acceptance:" STRING
body             ::= (state-name edge*)+
state-name       ::= "State:" identifier
edge             ::= "->" word identifier

word ::= STRING
identifier ::= STRING
state-conj: %empty | STRING "&" state-conj

STRING ::= `[a-zA-Z_0-9]*`

Examples:

`
DOA: v1
Start: 1
Acceptance: 2 & 3
--BEGIN--
State: 1
-> a 2
State: 2
-> ab 2
-> b 3
State: 3
--END--
`

## Working with Automata

Main class for operations with Automata is

```C++
class AutomataUtils;
```

It has 3 main static functions each returning a new Automata\
Functions will only work if you pass a correct needed automata to them\
For example, passing non-Complete Full Deterministic Automata to Minimalization function will lead to undifined behavoir

### Constucts Deterministic Finite Automata from Non-deterministic Finite Automata

```C++
static Automata to_dfa(const Automata& nfa);
```

### Constucts Complete Deterministic Finite Automata from Deterministic Finite Automata

```C++
static Automata to_fdfa(const Automata& nfa);
```

### Constucts Minimal Complete Deterministic Finite Automata from Complete Deterministic Finite Automata

```C++
static Automata to_mfdfa(const Automata& nfa);
```

## Parsing Algorithms

It is small library implementing [Cocke–Younger–Kasami](https://en.wikipedia.org/wiki/CYK_algorithm) and [Earley](https://en.wikipedia.org/wiki/Earley_parser) algorithms
They are used for parsing in computational linguistics. CYK works only with grammars given in [Chomsky normal form](https://en.wikipedia.org/wiki/Chomsky_normal_form).
CYK has complexity of O(n^3 * G), where is size of the CNF grammar.
Early endeed can work in O(n^3) time in worst case.

### Usage

Simply add this lib as a submodule to your program and include needed headers:

```cpp
#include <grammar.hpp>
#include <algorithms.hpp>
```

Create your first grammar and run one of the algorithms:

```cpp
std::string str_rules = "NP   :  Det Nom                                   ;"
                        "Nom  :  AP Nom                                    ;"
                        "AP   :  Adv A                                     ;"
                        "Det  :  'a' | 'an'                                ;"
                        "Adv  :  'very' | 'extremely'                      ;"
                        "AP   :  'heavy' | 'orange' | 'tall'               ;"
                        "A    :  'heavy' | 'orange' | 'tall' | 'muscular'  ;"
                        "Nom  :  'book' | 'orange' | 'man'                 ;";

  // create grammar from string and give 'NP' as a start symbol
  parsing::Grammar grammar("NP", str_rules);
  std::cout << std::boolalpha << std::parsing::CYK(grammar, vector<string>({"a", "very", "heavy", "orange", "book"})); //should see true
```

For more details see [API](#api) section

### API

#### Grammar Description

Main class representing context-free grammar

Grammar should be discribed in following way:
terminals should always be in 'single-quotes'

`
(string) start symbol of grammar
(Rule[]) rules of grammar in form:
  START ":" ('term' | NON_TERM) {"|" 'term' | NON_TERM} ";"
`

Examples:

`
NP   :  Det Nom;
Nom  :  AP Nom;
AP   :  Adv A;
Det  :  'a' | 'an';
Adv  :  'very' | 'extremely';
AP   :  'heavy' | 'orange' | 'tall';
A    :  'heavy' | 'orange' | 'tall' | 'muscular';
Nom  :  'book' | 'orange' | 'man';

S : 'x';
S : 'y';
S : 'z';
S : S '+' S;
S : S '-' S;
S : S '*' S;
S : S '/' S;
S : '(' S ')';
`

#### Main methods

Members                        | Descriptions
--------------------------------|---------------------------------------------
`Grammar::Grammar(basic_istream<char>& is)` | Constuctor from input stream, expecting in [following](#grammar description) form
`Grammar::Grammar(const string& start, const string& str_grammar)` | Constuctor start symbol and rules in string
`Grammar::Grammar(const string& start, const vector<Rule>& rules)` | Constuctor start symbol and vector of rules
`void Print(std::ostream& os)` | Prints grammar to output stream
`std::multimap<std::string, const TokenSeq&>& GetRulesMap()` | Obtains all rules from grammar
`vector<Rule>& GetRulesVec()` | Obtains all rules as a vector
`set<string>& GetTerminals()` | Obtains all terminal symbols
`set<string>& GetNonTerminals()` | Obtains all non terminal symbols
`set<string> GetLhsForWord(const string& word)` | Obtains right side of a rule
`string& GetStart()` | Obtains start symbol

#### Working with Grammar

Main functions for operations with Grammar are stored in

```C++
#include <algorithms.hpp>

// Checks if sentence belong to a given context-free
bool Earley(const Grammar& grammar, vector<string> sentence);
bool CYK(const Grammar& grammar, vector<string> sentence);

```
