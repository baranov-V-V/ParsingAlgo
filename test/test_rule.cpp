#include "gtest/gtest.h"
#include <rule.hpp>
#include <string>
#include <vector>

using std::vector;
using std::string;
using parsing::Rule;
using parsing::ParseString;

TEST(Construction, simple_terminals) {
  string str_rule = "A : B C;";

  ParseString parse_string(str_rule);
  vector<Rule> rules = Rule::ReadRuleLine(parse_string);
  ASSERT_EQ(rules.size(), 1);
  
  ASSERT_EQ(*rules.at(0).GetLhs().data, string("A"));
  
  ASSERT_EQ(*rules.at(0).GetRhs(0).data, string("B"));
  ASSERT_EQ(rules.at(0).GetRhs(0).is_term, false);
  
  ASSERT_EQ(*rules.at(0).GetRhs(1).data, string("C"));
  ASSERT_EQ(rules.at(0).GetRhs(1).is_term, false);
}

TEST(Construction, simple_non_terminals) {
  string str_rule = "A : 'b' 'c';";

  ParseString parse_string(str_rule);
  vector<Rule> rules = Rule::ReadRuleLine(parse_string);
  ASSERT_EQ(rules.size(), 1);
  
  ASSERT_EQ(*rules.at(0).GetLhs().data, string("A"));
  
  ASSERT_EQ(*rules.at(0).GetRhs(0).data, string("b"));
  ASSERT_EQ(rules.at(0).GetRhs(0).is_term, true);
  
  ASSERT_EQ(*rules.at(0).GetRhs(1).data, string("c"));
  ASSERT_EQ(rules.at(0).GetRhs(1).is_term, true);
}


TEST(Construction, simple_mixed) {
  string str_rule = "A : B 'c';";

  ParseString parse_string(str_rule);
  vector<Rule> rules = Rule::ReadRuleLine(parse_string);
  ASSERT_EQ(rules.size(), 1);
  
  ASSERT_EQ(*rules.at(0).GetLhs().data, string("A"));
  
  ASSERT_EQ(*rules.at(0).GetRhs(0).data, string("B"));
  ASSERT_EQ(rules.at(0).GetRhs(0).is_term, false);
  
  ASSERT_EQ(*rules.at(0).GetRhs(1).data, string("c"));
  ASSERT_EQ(rules.at(0).GetRhs(1).is_term, true);
}

TEST(Construction, advanced_oneline) {
  string str_rule = "A : B 'c' | Lol 'kek' | testtt ;";

  ParseString parse_string(str_rule);
  vector<Rule> rules = Rule::ReadRuleLine(parse_string);
  ASSERT_EQ(rules.size(), 3);
  
  ASSERT_EQ(*rules.at(0).GetLhs().data, string("A"));
  
  ASSERT_EQ(*rules.at(0).GetRhs(0).data, string("B"));
  ASSERT_EQ(rules.at(0).GetRhs(0).is_term, false);
  
  ASSERT_EQ(*rules.at(0).GetRhs(1).data, string("c"));
  ASSERT_EQ(rules.at(0).GetRhs(1).is_term, true);

  ASSERT_EQ(*rules.at(1).GetRhs(0).data, string("Lol"));
  ASSERT_EQ(rules.at(1).GetRhs(0).is_term, false);

  ASSERT_EQ(*rules.at(1).GetRhs(1).data, string("kek"));
  ASSERT_EQ(rules.at(1).GetRhs(1).is_term, true);

  ASSERT_EQ(*rules.at(2).GetRhs(0).data, string("testtt"));
  ASSERT_EQ(rules.at(2).GetRhs(0).is_term, false);
}

TEST(Construction, advanced_multiline) {
  string str_rule = "A : B 'c'       \n"
                        "| Lol 'kek' \n"
                        "|testtt ;";

  ParseString parse_string(str_rule);
  vector<Rule> rules = Rule::ReadRuleLine(parse_string);
  ASSERT_EQ(rules.size(), 3);
  
  ASSERT_EQ(*rules.at(0).GetLhs().data, string("A"));
  
  ASSERT_EQ(*rules.at(0).GetRhs(0).data, string("B"));
  ASSERT_EQ(rules.at(0).GetRhs(0).is_term, false);
  
  ASSERT_EQ(*rules.at(0).GetRhs(1).data, string("c"));
  ASSERT_EQ(rules.at(0).GetRhs(1).is_term, true);

  ASSERT_EQ(*rules.at(1).GetRhs(0).data, string("Lol"));
  ASSERT_EQ(rules.at(1).GetRhs(0).is_term, false);

  ASSERT_EQ(*rules.at(1).GetRhs(1).data, string("kek"));
  ASSERT_EQ(rules.at(1).GetRhs(1).is_term, true);

  ASSERT_EQ(*rules.at(2).GetRhs(0).data, string("testtt"));
  ASSERT_EQ(rules.at(2).GetRhs(0).is_term, false);
}
