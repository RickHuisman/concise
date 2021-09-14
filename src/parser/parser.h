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
  product,     // * / %
  prefix,      // any operator in prefix position
  call         // infix () []
};

class Parser {
  std::vector<Token> tokens;

  typedef Expr *(Parser::*PrefixParseFn)(Token token);

  typedef Expr *(Parser::*InfixParseFn)(Expr *left, Token token);

  struct Parselet { // TODO: Rename?
    PrefixParseFn prefix;
    InfixParseFn infix;
    int precedence;
  };

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

  std::map<TokenType, Parselet> rules {
      {TokenType::number, { &Parser::int_, NULL, Precedence::none }},
      {TokenType::semicolon, { NULL, NULL, Precedence::none }},
      {TokenType::identifier, { &Parser::parse_ident,    NULL, Precedence::none }},
//      {TokenType::plus, { NULL,    &Parser::binary, Precedence::TERM }}, // TOKEN_INT
  };

public:
  Parser(std::vector<Token> tks) {
    std::reverse(tks.begin(), tks.end());

    tokens = tks;
  }

  std::vector<Expr*> parse();

  Expr *parse_ident(Token token);
};

#endif //CONCISE_PARSER_H