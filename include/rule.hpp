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

struct ParseString {
 public:
  ParseString(const string& parse);

  void SkipSpaces();

  const size_t Size();

  bool HasNext();

  char Next();

  void Next(int count);

  char Curr();

  bool HasCurr();

  const string& parse;
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

  static void CheckDelimeter(ParseString& parse_string);
  static void CheckEnding(ParseString& parse_string);

  static vector<Rule> ReadRuleLine(ParseString& parse_string);

 private:
  Token lhs_;
  TokenSeq rhs_;

  static Token GetNonTerm(ParseString& parse_string);

  static Token GetTerm(ParseString& parse_string);

  static Token GetStr(ParseString& parse_string, bool is_term);
  static Token GetQuotedStr(ParseString& parse_string, bool is_term);

  static Token GetWord(ParseString& parse_string);

  static TokenSeq GetTokenSeq(ParseString& parse_string);

  static Token GetLhs(ParseString& parse_string);

  static vector<TokenSeq> GetRhs(ParseString& parse_string);
};

}  // namespace parsing

#endif  // PARSING_RULE_H_