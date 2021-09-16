#include <iostream>
#include "ast.h"

void UnaryExpr::compile(Compiler *compiler) {
  expr_->compile(compiler);
  compiler->emit(Opcode::negate);
}

void BinaryExpr::compile(Compiler *compiler) {
  left_->compile(compiler);
  right_->compile(compiler);

  if (op_ == BinaryOperator::subtract) compiler->emit(Opcode::subtract);
  if (op_ == BinaryOperator::add) compiler->emit(Opcode::add);
  if (op_ == BinaryOperator::divide) compiler->emit(Opcode::divide);
  if (op_ == BinaryOperator::multiply) compiler->emit(Opcode::multiply);
  // TODO: Add more binary operators.
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
