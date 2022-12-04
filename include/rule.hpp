#ifndef PARSING_RULE_H_
#define PARSING_RULE_H_

#include <algorithm>
#include <fstream>
#include <memory>
#include <iterator>
#include <list>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using std::string;
using std::vector;

namespace parsing {

typedef std::shared_ptr<std::string> StrPtr;

struct Token {
 public:
  Token(string data, bool is_term);
  Token() = default;

 public:
  bool is_filled();

  bool operator<(const Token& other) const;

  bool operator==(const Token& other) const;

  bool operator>(const Token& other) const;
  bool operator<=(const Token& other) const;
  bool operator>=(const Token& other) const;
  bool operator!=(const Token& other) const;

  StrPtr data;
  bool is_term;
};

typedef std::vector<Token> TokenSeq;

class FailedParsingExeption : public std::logic_error {
 public:
  FailedParsingExeption();
  virtual ~FailedParsingExeption() = default;

  const char* what() const noexcept override;
};

struct ParseRulesHelper {
 public:
  ParseRulesHelper(const string& parse);

  void SkipSpaces();

  const size_t Size();

  bool HasNext();

  char NextSymbol();

  void Next(int count);

  char CurrSymbol();

  bool HasCurr();

  const string& rules_string;
  int pos;
};

class Rule {
 public:
  Rule(Token lhs, TokenSeq rhs);

  Rule(const Rule&) = default;
  Rule& operator=(const Rule&) = default;

  bool operator<(const Rule& other) const;
  bool operator==(const Rule& other) const;
  bool operator!=(const Rule& other) const;

  const Token& GetLhs() const;
  const TokenSeq& GetRhs() const;
  const Token& GetRhs(int token_pos) const;

  static void CheckDelimeter(ParseRulesHelper& parse_string);
  static void CheckEnding(ParseRulesHelper& parse_string);

  static vector<Rule> ReadRuleLine(ParseRulesHelper& parse_string);

 private:
  Token lhs_;
  TokenSeq rhs_;

  static Token GetNonTerm(ParseRulesHelper& parse_string);

  static Token GetTerm(ParseRulesHelper& parse_string);

  static Token GetStr(ParseRulesHelper& parse_string, bool is_term);

  static Token GetWord(ParseRulesHelper& parse_string);

  static TokenSeq GetTokenSeq(ParseRulesHelper& parse_string);

  static Token GetLhs(ParseRulesHelper& parse_string);

  static vector<TokenSeq> GetRhs(ParseRulesHelper& parse_string);
};

}  // namespace parsing

#endif  // PARSING_RULE_H_