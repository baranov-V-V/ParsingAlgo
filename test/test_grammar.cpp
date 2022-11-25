#include "gtest/gtest.h"
#include <rule.hpp>
#include <grammar.hpp>
#include <string>

using parsing::Grammar;
using parsing::Rule;
using std::string;

TEST(Construction, simple) {
  string str_rules = "A : B 'c';\n"
                     "S : A;\n"
                     "A : B  C ;\n";

  Grammar grammar("S", str_rules);

  //grammar.Print(std::cout);

  ASSERT_EQ(grammar.GetStart(), "S");

  ASSERT_EQ(3, grammar.GetRulesVec().size());
  ASSERT_EQ(3, grammar.GetRulesMap().size());

  const Rule& rule1 = grammar.GetRulesVec().at(0);
  const Rule& rule2 = grammar.GetRulesVec().at(1);
  const Rule& rule3 = grammar.GetRulesVec().at(2);

  ASSERT_EQ(*rule1.GetLhs().data, string("A"));
  ASSERT_EQ(*rule1.GetRhs(0).data, string("B"));
  ASSERT_EQ(rule1.GetRhs(0).is_term, false);
  ASSERT_EQ(*rule1.GetRhs(1).data, string("c"));
  ASSERT_EQ(rule1.GetRhs(1).is_term, true);

  ASSERT_EQ(*rule2.GetLhs().data, string("S"));
  ASSERT_EQ(*rule2.GetRhs(0).data, string("A"));
  ASSERT_EQ(rule2.GetRhs(0).is_term, false);

  ASSERT_EQ(*rule3.GetLhs().data, string("A"));
  ASSERT_EQ(*rule3.GetRhs(0).data, string("B"));
  ASSERT_EQ(rule3.GetRhs(0).is_term, false);
  ASSERT_EQ(*rule3.GetRhs(1).data, string("C"));
  ASSERT_EQ(rule3.GetRhs(1).is_term, false);
}

TEST(Construction, from_stream) {
  string str_rules = "S         \n"
                     "A : B 'c';\n"
                     "S : A;    \n"
                     "A : B  C ;\n";

  std::istringstream in(str_rules);

  Grammar grammar(in);

  ASSERT_EQ(3, grammar.GetRulesVec().size());
  ASSERT_EQ(3, grammar.GetRulesMap().size());

  const Rule& rule1 = grammar.GetRulesVec().at(0);
  const Rule& rule2 = grammar.GetRulesVec().at(1);
  const Rule& rule3 = grammar.GetRulesVec().at(2);

  ASSERT_EQ(grammar.GetStart(), "S");

  ASSERT_EQ(*rule1.GetLhs().data, string("A"));
  ASSERT_EQ(*rule1.GetRhs(0).data, string("B"));
  ASSERT_EQ(rule1.GetRhs(0).is_term, false);
  ASSERT_EQ(*rule1.GetRhs(1).data, string("c"));
  ASSERT_EQ(rule1.GetRhs(1).is_term, true);

  ASSERT_EQ(*rule2.GetLhs().data, string("S"));
  ASSERT_EQ(*rule2.GetRhs(0).data, string("A"));
  ASSERT_EQ(rule2.GetRhs(0).is_term, false);

  ASSERT_EQ(*rule3.GetLhs().data, string("A"));
  ASSERT_EQ(*rule3.GetRhs(0).data, string("B"));
  ASSERT_EQ(rule3.GetRhs(0).is_term, false);
  ASSERT_EQ(*rule3.GetRhs(1).data, string("C"));
  ASSERT_EQ(rule3.GetRhs(1).is_term, false);
}
