#include <iostream>
#include "ast.h"

void UnaryExpr::compile(Compiler *compiler) {
  expr_->compile(compiler);

  if (op_ == UnaryOperator::negate) compiler->emit(Opcode::negate);
  if (op_ == UnaryOperator::not_) compiler->emit(Opcode::not_);
}

void BinaryExpr::compile(Compiler *compiler) {
  left_->compile(compiler);
  right_->compile(compiler);

  if (op_ == BinaryOperator::subtract) compiler->emit(Opcode::subtract);
  if (op_ == BinaryOperator::add) compiler->emit(Opcode::add);
  if (op_ == BinaryOperator::divide) compiler->emit(Opcode::divide);
  if (op_ == BinaryOperator::multiply) compiler->emit(Opcode::multiply);
  if (op_ == BinaryOperator::equal) compiler->emit(Opcode::equal);
  if (op_ == BinaryOperator::bang_equal) {
    compiler->emit(Opcode::equal);
    compiler->emit(Opcode::not_);
  }
  if (op_ == BinaryOperator::greater_than) compiler->emit(Opcode::greater);
  if (op_ == BinaryOperator::greater_than_equal) {
    compiler->emit(Opcode::less);
    compiler->emit(Opcode::not_);
  }
  if (op_ == BinaryOperator::less_than) compiler->emit(Opcode::less);
  if (op_ == BinaryOperator::less_than_equal) {
    compiler->emit(Opcode::greater);
    compiler->emit(Opcode::not_);
  }
}

void LetAssignExpr::compile(Compiler *compiler) {
  std::cout << "let assign\n";
}

void LetSetExpr::compile(Compiler *compiler) {
  std::cout << "let set\n";
}

void LetGetExpr::compile(Compiler *compiler) {
  std::cout << "let get\n";
}

void PrintExpr::compile(Compiler *compiler) {
  expr->compile(compiler);
  compiler->emit(Opcode::print);
}

void LiteralExpr::compile(Compiler *compiler) {
  compiler->emit_constant(value);
}
