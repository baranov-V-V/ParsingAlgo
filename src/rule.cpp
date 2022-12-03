#include <rule.hpp>

namespace parsing {

Token::Token(string data, bool is_term) : data(std::make_shared<string>(data)), is_term(is_term) {}

bool Token::is_filled() {
  return data->size() != 0;
}

bool Token::operator<(const Token& other) const {
  return *data < *other.data;
};

bool Token::operator==(const Token& other) const {
  return *data == *other.data;
};

bool Token::operator>(const Token& other) const {
  return other < *this;
};
bool Token::operator<=(const Token& other) const {
  return !(*this > other);
};
bool Token::operator>=(const Token& other) const {
  return !(*this < other);
};
bool Token::operator!=(const Token& other) const {
  return !(*this == other);
};


FailedParsingExeption::FailedParsingExeption() : std::logic_error("failed parse") {}

const char* FailedParsingExeption::what() const noexcept {
  return "failed parse";
}


ParseRulesHelper::ParseRulesHelper(const string& parse) : rules_string(parse), pos(0) {}

void ParseRulesHelper::SkipSpaces() {
  while (pos < Size() && std::isspace(CurrSymbol())) {
    NextSymbol();
  }
}

const size_t ParseRulesHelper::Size() {
  return rules_string.size();
}

bool ParseRulesHelper::HasNext() {
  return (pos + 1) < Size();
}

bool ParseRulesHelper::HasCurr() {
  return pos < Size();
}

char ParseRulesHelper::NextSymbol() {
  if ((pos + 1) >= Size()) {
    throw std::out_of_range("got to end of rules");
  }
  return rules_string[pos++];
}

void ParseRulesHelper::Next(int count) {
  if ((pos + count) >= Size()) {
    throw std::out_of_range("got to end of rules");
  }
  pos += count;
}

char ParseRulesHelper::CurrSymbol() {
  if (pos >= Size()) {
    throw std::out_of_range("got to end of rules");
  }
  return rules_string[pos];
}

Rule::Rule(Token lhs, TokenSeq rhs) : lhs_(lhs), rhs_(rhs) {}

Token Rule::GetStr(ParseRulesHelper& rules, bool is_term) {
  int start_pos = rules.pos;
  rules.SkipSpaces();
  
  Token token("", is_term);
  
  while (rules.pos < rules.Size() && std::isalpha(rules.CurrSymbol())) {
    token.data->push_back(rules.CurrSymbol());
    rules.NextSymbol();
  }

  rules.SkipSpaces();
  
  if (!token.is_filled()) {
    rules.pos = start_pos;
    throw FailedParsingExeption();
  }

  return token;
}

Token Rule::GetQuotedStr(ParseRulesHelper& rules, bool is_term) {
  int start_pos = rules.pos;
  rules.SkipSpaces();
  
  Token token("", is_term);
  
  while (rules.HasCurr() && rules.CurrSymbol() != '\'') {
    token.data->push_back(rules.CurrSymbol());
    rules.NextSymbol();
  }
  
  if (!token.is_filled()) {
    rules.pos = start_pos;
    throw FailedParsingExeption();
  }

  return token;
}

Token Rule::GetNonTerm(ParseRulesHelper& rules) {
  return GetStr(rules, false);
}

Token Rule::GetTerm(ParseRulesHelper& rules) {
  Token token("", true);

  rules.SkipSpaces();
  
  int start_pos = rules.pos;

  if (rules.HasCurr() && rules.CurrSymbol() == '\'') {
    rules.NextSymbol();
    token = GetQuotedStr(rules, true);

    if (rules.HasCurr() && rules.CurrSymbol() != '\'') {
      rules.pos = start_pos;
      throw FailedParsingExeption();
    }
    rules.NextSymbol();
  } else {
    rules.pos = start_pos;
    throw FailedParsingExeption();
  }

  return token;
}

Token Rule::GetWord(ParseRulesHelper& rules) {
  int start_pos = rules.pos;
  
  try {
    return GetNonTerm(rules);
  } catch(const FailedParsingExeption& e) {
    //could not get non-term then try Term
  }
  
  rules.pos = start_pos;
  return GetTerm(rules);
}

vector<Token> Rule::GetTokenSeq(ParseRulesHelper& rules) {
  vector<Token> seq = {};

  seq.push_back(GetWord(rules));

  try{
    while (true) {
      seq.push_back(GetWord(rules));
    }
  }
  catch(const FailedParsingExeption& e) {
    //could not read more words;
  }
  
  return seq;
}

Token Rule::GetLhs(ParseRulesHelper& rules) {
  return GetNonTerm(rules);
}

vector<TokenSeq> Rule::GetRhs(ParseRulesHelper& rules) {
  vector<TokenSeq> rhs = {};

  rhs.push_back(GetTokenSeq(rules));
  rules.SkipSpaces();

  while (rules.HasCurr() && rules.CurrSymbol() == '|') {
    rules.NextSymbol();
    rhs.push_back(GetTokenSeq(rules));
    rules.SkipSpaces();
  }

  return rhs;
}

void Rule::CheckDelimeter(ParseRulesHelper& rules) {
  rules.SkipSpaces();
  if (!rules.HasCurr() || rules.CurrSymbol() != ':') {
    throw FailedParsingExeption();
  }
  rules.NextSymbol();
}

void Rule::CheckEnding(ParseRulesHelper& rules) {
  rules.SkipSpaces();
  if (!rules.HasCurr() || rules.CurrSymbol() != ';') {
    throw FailedParsingExeption();
  }
  if (rules.HasNext()) {
    rules.NextSymbol();
  }
}

vector<Rule> Rule::ReadRuleLine(ParseRulesHelper& rules) {
  vector<Rule> rules_vec = {};

  Token lhs = GetLhs(rules);
  
  CheckDelimeter(rules);

  for (const TokenSeq& rhs: GetRhs(rules)) {
    rules_vec.push_back({lhs, rhs});
  }
  
  CheckEnding(rules);

  return rules_vec;
}

const Token& Rule::GetLhs() const {
  return lhs_;
}
const TokenSeq& Rule::GetRhs() const {
  return rhs_;
}
const Token& Rule::GetRhs(int token_pos) const {
  return rhs_.at(token_pos);
};

bool Rule::operator<(const Rule& other) const {
  if (lhs_ != other.lhs_) {
    return lhs_ < other.lhs_;
  } else {
    int pos = 0;
    while (pos < rhs_.size() && pos < other.rhs_.size()) {
      if (rhs_.at(pos) != other.rhs_.at(pos)) {
        return rhs_.at(pos) < other.rhs_.at(pos);
      }
      ++pos;
    }
  }
  return rhs_.size() < other.rhs_.size();
};

bool Rule::operator==(const Rule& other) const {
  if (rhs_.size() != other.rhs_.size()) {
    return false;
  }

  if (lhs_ != other.lhs_) {
    return false;
  }

  int pos = 0;
  while (pos < rhs_.size() && pos < other.rhs_.size()) {
    if (rhs_.at(pos) != other.rhs_.at(pos)) {
      return false;
    }
    ++pos;
  }

  return true;
};

bool Rule::operator!=(const Rule& other) const {
  return !(*this == other);
};

} // namespace parsing