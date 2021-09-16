#include <syntax/lexer.h>
#include <parser/parser.h>

#include <utility>
#include "compiler.h"

Function compile(std::string source) {
  Lexer lexer(std::move(source));
  auto tokens = lexer.lex();

  Parser parser(tokens);
  auto exprs = parser.parse();

  Compiler compiler;

  for (auto expr: exprs) {
    expr->compile(&compiler);
  }

  return compiler.end_compiler();
}

Function Compiler::end_compiler() {
  // TODO: Fix.
  return current.function;
}

void Compiler::emit_constant(Value value) {
  auto index = current_chunk()->add_constant(value);
  emit(Opcode::constant);
  emit_byte(index);
}

void Compiler::emit(Opcode opcode) {
  current_chunk()->write(opcode);
}

void Compiler::emit_byte(std::uint8_t byte) {
  current_chunk()->write_byte(byte);
}

Chunk *Compiler::current_chunk() {
  return &current.function.chunk;
}
