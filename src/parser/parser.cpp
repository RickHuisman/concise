#include <iostream>
#include <vector>
#include "parser.h"

std::vector<Expr*> Parser::parse() {
  std::vector<Expr*> exprs;

  while (has_next()) {
    if (check(TokenType::eof)) {  // TODO Hacky fix.
      consume();
    } else {
      exprs.push_back(declaration());
    }
  }

  return exprs;
}

Expr* Parser::declaration() {
  switch (peek_type()) {
    case TokenType::let:
      consume();
      return declare_let();
    default: return expr_statement();
  }
}

Expr* Parser::declare_let() {
  auto ident = consume(TokenType::identifier, "Expect identifier.");
  consume(TokenType::equal, "Expect '=' after identifier.");

  // TODO Initializer var with null e.g. var x;.
  auto initializer = expr_statement();
  return new LetAssignExpr(ident.source, initializer);
}

Expr* Parser::expr_statement() {
  auto expr = expression();
  consume(TokenType::semicolon, "Expect ';' after expression.");
  return expr;
}

Expr* Parser::expression() {
  return parse_precedence(Precedence::assignment);
}

Expr* Parser::parse_precedence(int precedence) {
  auto token = consume();
  auto prefix = rules[token.token_type].prefix;

  if (prefix == nullptr) {
    std::cout << "Unexpected token '" << token.source << "'";
    std::exit(EXIT_FAILURE);
  }

  auto left = (this->*prefix)(token);

  while (precedence <= rules[peek_type()].precedence) {
    token = consume();
    auto infix = rules[token.token_type].infix;
    left = (this->*infix)(left, token);
  }

  return left;
}

Expr* Parser::int_(Token token) {
  auto value = atoi(token.source.c_str());
  return new IntExpr(value);
}

Expr* Parser::parse_ident(Token token) {
  auto ident = token.source;

  // Set let.
  if (match(TokenType::equal)) {
    auto expr = expression();
    return new LetSetExpr(ident, expr);
  }

  // Get let.
  return new LetGetExpr(ident);
}

Token Parser::consume(TokenType token_type, const string &message) {
  if (check(token_type)) {
    return consume();
  }

  std::cout << message;
  std::exit(EXIT_FAILURE);
}

Token Parser::consume() {
  auto popped = tokens.back();
  tokens.pop_back();
  return popped;
}

bool Parser::match(TokenType token_type) {
  if (!check(token_type)) {
    return false;
  }

  consume();
  return true;
}

bool Parser::check(TokenType token_type) {
  return peek_type() == token_type;
}

TokenType Parser::peek_type() {
  return has_next() ? tokens.back().token_type : TokenType::eof;
}

bool Parser::has_next() {
  return !tokens.empty();
}
