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

  Expr *int_(Token token); // TODO: Rename.

  Expr *string_(Token token); // TODO: Rename.

  Expr *literal(Token token);

  Token consume();

  Token consume(TokenType token_type, const std::string &message);

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
      {TokenType::minus,         {&Parser::unary, &Parser::binary, Precedence::term}},
      {TokenType::plus,          {NULL,           &Parser::binary, Precedence::term}},
      {TokenType::slash,         {NULL,           &Parser::binary, Precedence::factor}},
      {TokenType::star,          {NULL,           &Parser::binary, Precedence::factor}},
      {TokenType::equal,         {NULL,           &Parser::binary, Precedence::none}},
      {TokenType::equal_equal,   {NULL,           &Parser::binary, Precedence::equality}},
      {TokenType::bang,          {&Parser::unary, NULL,            Precedence::term}},
      {TokenType::bang_equal,    {NULL,           &Parser::binary, Precedence::comparison}},
      {TokenType::greater,       {NULL,           &Parser::binary, Precedence::comparison}},
      {TokenType::greater_equal, {NULL,           &Parser::binary, Precedence::comparison}},
      {TokenType::less,          {NULL,           &Parser::binary, Precedence::comparison}},
      {TokenType::less_equal,    {NULL,           &Parser::binary, Precedence::comparison}},
      {TokenType::semicolon,     {NULL,                 NULL,      Precedence::none}},
      {TokenType::identifier,    {&Parser::parse_ident, NULL,      Precedence::none}},
      {TokenType::true_,         {&Parser::literal,     NULL,      Precedence::none}},
      {TokenType::false_,        {&Parser::literal,     NULL,      Precedence::none}},
      {TokenType::number,        {&Parser::int_,        NULL,      Precedence::none}},
      {TokenType::string,        {&Parser::string_,     NULL,      Precedence::none}},
  };

public:
  Parser(std::vector<Token> tks) {
    std::reverse(tks.begin(), tks.end());

    tokens = tks;
  }

  std::vector<Expr *> parse();

  Expr *parse_ident(Token token);

  Expr *parse_print();

  Expr *unary(Token token);

  Expr *binary(Expr *left, Token token);
};

#endif //CONCISE_PARSER_H
