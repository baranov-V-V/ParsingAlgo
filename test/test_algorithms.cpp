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


TEST(CYK, simple) {
  string str_rules = "NP   :  Det Nom                                   ;"
                     "Nom  :  AP Nom                                    ;"
                     "AP   :  Adv A                                     ;"
                     "Det  :  'a' | 'an'                                ;"
                     "Adv  :  'very' | 'extremely'                      ;"
                     "AP   :  'heavy' | 'orange' | 'tall'               ;"
                     "A    :  'heavy' | 'orange' | 'tall' | 'muscular'  ;"
                     "Nom  :  'book' | 'orange' | 'man'                 ;";

  Grammar grammar("NP", str_rules);

  ASSERT_EQ(parsing::CYK(grammar, vector<string>({"a", "very", "heavy", "orange", "book"})), true);
}
