#ifndef CONCISE_LEXER_H
#define CONCISE_LEXER_H

#include <string>

using std::string;

enum class TokenType {
  left_paren,
  right_paren,
  left_brace,
  right_brace,

  comma,
  dot,
  minus,
  plus,
  semicolon,
  slash,
  star,

  bang,
  bang_equal,
  equal,
  equal_equal,
  greater,
  greater_equal,
  less,
  less_equal,

  identifier,
  string,
  number,

  let,

  error,
  eof,
};

class Token {
public:
  TokenType token_type;
  string source;

  Token(TokenType token_type, string source)
      : token_type(token_type), source(source) {}
};

bool operator==(const Token &a, const Token &b);

class Lexer {
  int current;

  std::string source;

  Token scan_token();

  static TokenType identifier_type_from_str(std::string identifier);

  Token identifier();

  Token number();

  Token make_token(TokenType token_type);

  void skip_whitespace();

  char match(char expected);

  char advance();

  char peek_next();

  char peek();

  bool is_at_end();

public:
  explicit Lexer(std::string source) : source(source), current(0) {}

  std::vector<Token> lex();
};

#endif //CONCISE_LEXER_H
