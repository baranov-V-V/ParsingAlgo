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


ParseString::ParseString(const string& parse) : parse(parse), pos(0) {}

void ParseString::SkipSpaces() {
  while (pos < Size() && std::isspace(Curr())) {
    Next();
  }
}

const size_t ParseString::Size() {
  return parse.size();
}

bool ParseString::HasNext() {
  return (pos + 1) < Size();
}

bool ParseString::HasCurr() {
  return pos < Size();
}

char ParseString::Next() {
  if ((pos + 1) >= Size()) {
    throw std::out_of_range("got to end of parse_string");
  }
  return parse[pos++];
}

void ParseString::Next(int count) {
  if ((pos + count) >= Size()) {
    throw std::out_of_range("got to end of parse_string");
  }
  pos += count;
}

char ParseString::Curr() {
  if (pos >= Size()) {
    throw std::out_of_range("got to end of parse_string");
  }
  return parse[pos];
}

Rule::Rule(Token lhs, TokenSeq rhs) : lhs_(lhs), rhs_(rhs) {}

Token Rule::GetStr(ParseString& parse_string, bool is_term) {
  int start_pos = parse_string.pos;
  parse_string.SkipSpaces();
  
  Token token("", is_term);
  
  while (parse_string.pos < parse_string.Size() && std::isalpha(parse_string.Curr())) {
    token.data->push_back(parse_string.Curr());
    parse_string.Next();
  }

  parse_string.SkipSpaces();
  
  if (!token.is_filled()) {
    parse_string.pos = start_pos;
    throw FailedParsingExeption();
  }

  return token;
}

Token Rule::GetNonTerm(ParseString& parse_string) {
  return GetStr(parse_string, false);
}

Token Rule::GetTerm(ParseString& parse_string) {
  Token token("", true);

  parse_string.SkipSpaces();
  
  int start_pos = parse_string.pos;

  if (parse_string.HasCurr() && parse_string.Curr() == '\'') {
    parse_string.Next();
    token = GetStr(parse_string, true);

    parse_string.SkipSpaces();
    if (parse_string.HasCurr() && parse_string.Curr() != '\'') {
      parse_string.pos = start_pos;
      throw FailedParsingExeption();
    }
    parse_string.Next();
  } else {
    parse_string.pos = start_pos;
    throw FailedParsingExeption();
  }

  return token;
}

Token Rule::GetWord(ParseString& parse_string) {
  int start_pos = parse_string.pos;
  
  try {
    return GetNonTerm(parse_string);
  } catch(const FailedParsingExeption& e) {
    //could not get non-term then try Term
  }
  
  parse_string.pos = start_pos;
  return GetTerm(parse_string);
}

vector<Token> Rule::GetTokenSeq(ParseString& parse_string) {
  vector<Token> seq = {};

  seq.push_back(GetWord(parse_string));

  try{
    while (true) {
      seq.push_back(GetWord(parse_string));
    }
  }
  catch(const FailedParsingExeption& e) {
    //could not read more words;
  }
  
  return seq;
}

Token Rule::GetLhs(ParseString& parse_string) {
  return GetNonTerm(parse_string);
}

vector<TokenSeq> Rule::GetRhs(ParseString& parse_string) {
  vector<TokenSeq> rhs = {};

  rhs.push_back(GetTokenSeq(parse_string));
  parse_string.SkipSpaces();

  while (parse_string.HasCurr() && parse_string.Curr() == '|') {
    parse_string.Next();
    rhs.push_back(GetTokenSeq(parse_string));
    parse_string.SkipSpaces();
  }

  return rhs;
}

void Rule::CheckDelimeter(ParseString& parse_string) {
  parse_string.SkipSpaces();
  if (!parse_string.HasCurr() || parse_string.Curr() != ':') {
    throw FailedParsingExeption();
  }
  parse_string.Next();
}

void Rule::CheckEnding(ParseString& parse_string) {
  parse_string.SkipSpaces();
  if (!parse_string.HasCurr() || parse_string.Curr() != ';') {
    throw FailedParsingExeption();
  }
  if (parse_string.HasNext()) {
    parse_string.Next();
  }
}

vector<Rule> Rule::ReadRuleLine(ParseString& parse_string) {
  vector<Rule> rules = {};

  Token lhs = GetLhs(parse_string);
  
  CheckDelimeter(parse_string);

  for (const TokenSeq& rhs: GetRhs(parse_string)) {
    rules.push_back({lhs, rhs});
  }
  
  CheckEnding(parse_string);

  return rules;
}

const Token& Rule::GetLhs() const { return lhs_; }
const TokenSeq& Rule::GetRhs() const { return rhs_; }
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