#include <iostream>
#include <vector>
#include "parser.h"

std::vector<Expr *> Parser::parse() {
  std::vector<Expr *> exprs;

  while (has_next()) {
    if (check(TokenType::eof)) {  // TODO Hacky fix.
      consume();
    } else {
      exprs.push_back(declaration());
    }
  }

  return exprs;
}

Expr *Parser::declaration() {
  if (match(TokenType::let)) return declare_let();
  if (match(TokenType::print)) return parse_print();

  return expr_statement();
}

Expr *Parser::declare_let() {
  auto ident = consume(TokenType::identifier, "Expect identifier.");
  consume(TokenType::equal, "Expect '=' after identifier.");

  // TODO Initializer var with null e.g. var x;.
  auto initializer = expr_statement();
  return new LetAssignExpr(ident.source, initializer);
}

Expr *Parser::parse_print() {
  auto expr = expr_statement();
  return new PrintExpr(expr);
}

Expr *Parser::expr_statement() {
  auto expr = expression();
  consume(TokenType::semicolon, "Expect ';' after expression.");
  return expr;
}

Expr *Parser::expression() {
  return parse_precedence(Precedence::assignment);
}

Expr *Parser::parse_precedence(int precedence) {
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

Expr *Parser::unary(Token token) {
  auto expr = expression();

  UnaryOperator op;
  if (token.token_type == TokenType::minus) op = UnaryOperator::negate;
  if (token.token_type == TokenType::bang) op = UnaryOperator::not_;

  return new UnaryExpr(op, expr);
}

Expr *Parser::binary(Expr *left, Token token) {
  Expr *right = parse_precedence(
      rules[token.token_type].precedence + 1
  );

  BinaryOperator op;
  if (token.token_type == TokenType::minus) op = BinaryOperator::subtract;
  if (token.token_type == TokenType::plus) op = BinaryOperator::add;
  if (token.token_type == TokenType::slash) op = BinaryOperator::divide;
  if (token.token_type == TokenType::star) op = BinaryOperator::multiply;
  if (token.token_type == TokenType::equal_equal) op = BinaryOperator::equal;
  if (token.token_type == TokenType::bang_equal) op = BinaryOperator::bang_equal;
  if (token.token_type == TokenType::greater) op = BinaryOperator::greater_than;
  if (token.token_type == TokenType::greater_equal) op = BinaryOperator::greater_than_equal;
  if (token.token_type == TokenType::less) op = BinaryOperator::less_than;
  if (token.token_type == TokenType::less_equal) op = BinaryOperator::less_than_equal;

  return new BinaryExpr(left, op, right);
}

Expr *Parser::int_(Token token) {
  auto value = std::stod(token.source.c_str());
  return new LiteralExpr(value);
}

Expr *Parser::string_(Token token) {
  return new LiteralExpr(token.source);
}

Expr *Parser::literal(Token token) {
  if (token.token_type == TokenType::true_) return new LiteralExpr(true);
  if (token.token_type == TokenType::false_) return new LiteralExpr(false);
  // TODO: Throw exception.
}

Expr *Parser::parse_ident(Token token) {
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
