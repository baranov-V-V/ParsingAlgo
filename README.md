# Parsing Algorithms

This is a library for storing and making operations with formal grammars (https://en.wikipedia.org/wiki/Formal_grammar)\
You can add this library to your project via Cmake or write in ```src/main.cpp``` as a sandbox\
If you want to run test and code coverage before compilation run ```install.sh```\
To compile sandbox and tests use ```build.sh```\
To run test after compiling use ```run_tests.sh```\
All code coverage files are stored in ```build/ccov```

## Main classes

Main class for storing any immutable Grammar:
```C++
class Grammar
```

## Creation of Grammar
It can be constucted from an input stream like std::sin or std::istringstream and from std::string
```C++
Grammar(basic_istream<char>& in);
Grammar(const string& start, const string& str_grammar);
```

Grammar should be discribed in following way:
terminals should always be in 'single-quotes'

```
(string) start symbol of grammar
(Rule[]) rules of grammar in form:
  START ":" ('term' | NON_TERM) {"|" 'term' | NON_TERM} ";"
```
Examples:

```
NP   :  Det Nom                                   ;
Nom  :  AP Nom                                    ;
AP   :  Adv A                                     ;
Det  :  'a' | 'an'                                ;
Adv  :  'very' | 'extremely'                      ;
AP   :  'heavy' | 'orange' | 'tall'               ;
A    :  'heavy' | 'orange' | 'tall' | 'muscular'  ;
Nom  :  'book' | 'orange' | 'man'                 ;
```

Grammar can be made from it's compontents:

```C++
Grammar(const string& start, const vector<Rule>& rules);
```

## Printing of Grammar
Automata can be put into ostream
```C++
void Print(std::ostream& os);
```

## Working with Grammar

Main functions for operations with Grammar are is
```C++
#include <algorithms.hpp>
```

### Checks if sentence belongs to grammar
```C++
bool CYK(const Grammar& grammar, vector<string> sentence);
```