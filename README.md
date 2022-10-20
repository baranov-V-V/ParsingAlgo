# Automata

This is a library for storing and making operations with automatas (https://en.wikipedia.org/wiki/Automata_theory)\
You can add this library to your project via Cmake

## Main classes

Main class for storing any immutable Automata:
```C++
class Automata
```

Main class for operations with Automata is
```C++
class AutomataUtils;
```

## Creation of Automata
It can be constucted from and input stream like std::sin or std::istringstream
```C++
Automata(basic_istream<char>& in);
```

Automata should be discribed in following way:

```
(int) number of letters in alphabet
(char[]) alphabet
(int) start state
(int) number of transitions
({in, char, int}[]) transitions in form {"from" "letter" "to"}, brackets and quotes should be ommited
(int) number of final states
(int[]) final states
```
Examples:

```
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
```

Automata can be made from it's compontents:

```C++
Automata(const set<char>& alphabet, const vector<Transition>& transitions, const int start, const set<int>& final_states);
```

## Printing of Automata
Automata can be put into file with function
```C++
void to_doa(const char* filename);
```

which presents automata in DOA (Dolgoprudny HOA) format

```
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

STRING ::= [a-zA-Z_0-9]*
```

Examples:

```
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
```

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