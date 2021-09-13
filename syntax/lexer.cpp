#include "lexer.h"
#include <vector>

using std::vector;
using std::string;

vector<Token> Lexer::lex(string s) {
  source = s;

  vector<Token> tokens;
  while (!is_at_end()) {
    Token token = scan_token();
    tokens.push_back(token);
  }

  return tokens;
}

Token Lexer::scan_token() {
  skip_whitespace();

  if (is_at_end()) return make_token(TokenType::eof);

  auto c = advance();

  if (isalpha(c)) return identifier();
  if (isdigit(c)) return number();

  switch (c) {
    case '(':
      return make_token(TokenType::left_paren);
    case ')':
      return make_token(TokenType::right_paren);
    case '{':
      return make_token(TokenType::left_brace);
    case '}':
      return make_token(TokenType::right_brace);
    case ';':
      return make_token(TokenType::semicolon);
    case ',':
      return make_token(TokenType::comma);
    case '.':
      return make_token(TokenType::dot);
    case '-':
      return make_token(TokenType::minus);
    case '+':
      return make_token(TokenType::plus);
    case '/':
      return make_token(TokenType::slash);
    case '*':
      return make_token(TokenType::star);
    case '!':
      return make_token(match('=') ? TokenType::bang_equal : TokenType::bang);
    case '=':
      return make_token(match('=') ? TokenType::equal_equal : TokenType::equal);
    case '<':
      return make_token(match('=') ? TokenType::less_equal : TokenType::less);
    case '>':
      return make_token(match('=') ? TokenType::greater_equal : TokenType::greater);
      // case '"': String(), TODO
  }

  return make_token(TokenType::error);
}

TokenType Lexer::identifier_type_from_str(string source) {
  if (source == "let") {
    return TokenType::let;
  }

  return TokenType::identifier;
}

Token Lexer::identifier() {
  int start = current - 1;
  while (isalpha(peek()) || isdigit(peek())) advance();

  string identifier = source.substr(start, current - start);
  TokenType ident_type = identifier_type_from_str(identifier);

  Token token(ident_type, identifier);
  return token;
}

Token Lexer::number() {
  int start = current - 1;
  while (isdigit(peek())) advance();

  // Look for a fractional part.
  if (peek() == '.' && isdigit(peek_next())) {
    // Consume the ".".
    advance();

    while (isdigit(peek())) advance();
  }

  auto token_source = source.substr(start, current - start);
  Token token(TokenType::number, token_source);
  return token;
}

Token Lexer::make_token(TokenType token_type) {
  Token token(token_type, string(1, source[current]));
  return token;
}

void Lexer::skip_whitespace() {
  for (;;) {
    if (isspace(peek())) {
      advance();
    } else return;
  }
}

char Lexer::match(char expected) {
  if (is_at_end()) return false;
  if (source[current] != expected) return false;

  advance();
  return true;
}

char Lexer::advance() {
  current += 1;
  return source[current - 1];
}

char Lexer::peek_next() {
  return is_at_end() ? '\0' : source[current + 1];
}

char Lexer::peek() {
  return is_at_end() ? '\0' : source[current];
}

bool Lexer::is_at_end() {
  return source[current] == '\0';
}