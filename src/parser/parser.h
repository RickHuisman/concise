#ifndef CONCISE_PARSER_H
#define CONCISE_PARSER_H

#include <vector>
#include <map>
#include "../syntax/lexer.h"
#include "ast.h"

enum Precedence : int {
  none,
  assignment,  // =
  record,      // ,
  logical,     // and or
  not_,        // not
  is,          // is
  equality,    // == !=
  comparison,  // < > <= >=
  range,       // .. ...
  term,        // + -
  factor,     // * / %
  prefix,      // any operator in prefix position
  call         // infix () []
};

class Parser {
  std::vector<Token> tokens;

  Expr *declaration();

  Expr *declare_let();

  Expr *int_(Token token);

  Token consume();

  Token consume(TokenType token_type, const string &message);

  bool match(TokenType token_type);

  bool check(TokenType token_type);

  TokenType peek_type();

  bool has_next();

  Expr *expr_statement();

  Expr *expression();

  Expr *parse_precedence(int precedence);

  typedef Expr *(Parser::*PrefixParseFn)(Token token);

  typedef Expr *(Parser::*InfixParseFn)(Expr *left, Token token);

  struct Parselet { // TODO: Rename?
    PrefixParseFn prefix;
    InfixParseFn infix;
    int precedence;
  };

  std::map<TokenType, Parselet> rules{
      {TokenType::minus,         {NULL, &Parser::binary,      Precedence::term}},
      {TokenType::plus,          {NULL, &Parser::binary,      Precedence::term}},
      {TokenType::slash,         {NULL, &Parser::binary,      Precedence::factor}},
      {TokenType::star,          {NULL, &Parser::binary,      Precedence::factor}},
      {TokenType::equal,         {NULL, &Parser::binary,      Precedence::none}},
      {TokenType::bang_equal,    {NULL, &Parser::binary,      Precedence::none}},
      {TokenType::greater,       {NULL, &Parser::binary,      Precedence::none}},
      {TokenType::greater_equal, {NULL, &Parser::binary,      Precedence::none}},
      {TokenType::less,          {NULL, &Parser::binary,      Precedence::none}},
      {TokenType::less_equal,    {NULL, &Parser::binary,      Precedence::none}},
      {TokenType::number,        {&Parser::int_,        NULL, Precedence::none}},
      {TokenType::semicolon,     {NULL,                 NULL, Precedence::none}},
      {TokenType::identifier,    {&Parser::parse_ident, NULL, Precedence::none}},
  };

public:
  Parser(std::vector<Token> tks) {
    std::reverse(tks.begin(), tks.end());

    tokens = tks;
  }

  std::vector<Expr *> parse();

  Expr *parse_ident(Token token);

  Expr *parse_print();

  Expr *binary(Expr *left, Token token);
};

#endif //CONCISE_PARSER_H