#include "gtest/gtest.h"

#include <rule.hpp>
#include <grammar.hpp>
#include <algorithms.hpp>
#include <string>
#include <vector>

using parsing::Grammar;
using parsing::Rule;
using std::string;
using std::vector;

TEST(Earley, simple1) {
  string str_rules = "NP   :  Det Nom                                   ;"
                     "Nom  :  AP Nom                                    ;"
                     "AP   :  Adv A                                     ;"
                     "Det  :  'a' | 'an'                                ;"
                     "Adv  :  'very' | 'extremely'                      ;"
                     "AP   :  'heavy' | 'orange' | 'tall'               ;"
                     "A    :  'heavy' | 'orange' | 'tall' | 'muscular'  ;"
                     "Nom  :  'book' | 'orange' | 'man'                 ;";

  Grammar grammar("NP", str_rules);

  grammar.Print(std::cout);

  //parsing::CYK(grammar, vector<string>({"a", "very", "heavy", "orange", "book"}));

  ASSERT_EQ(parsing::Earley(grammar, vector<string>({"a", "very", "heavy", "orange", "book"})), true);
}