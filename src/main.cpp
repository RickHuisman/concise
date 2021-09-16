#include <iostream>
#include <vector>
#include <sstream>
#include "syntax/lexer.h"
#include "compiler/chunk.h"
#include "vm/vm.h"
#include "parser/parser.h"
#include "compiler/compiler.h"

class com;

int main() {
//  Chunk chunk;
//
//  chunk.write(Opcode::constant);
//  auto index = chunk.add_constant(10.0);
//  chunk.write_byte(index);
//
//  chunk.write(Opcode::constant);
//  auto index2 = chunk.add_constant(10.0);
//  chunk.write_byte(index2);
//
//  chunk.write(Opcode::add);
//
//  VM vm;
//  vm.interpret(chunk);

//  auto tk1 = Token(TokenType::semicolon, ";");
//  auto tk2 = Token(TokenType::identifier, ";");
//
//  if (tk1 == tk2) {
//    std::cout << "equal";
//  } else {
//    std::cout << "not equal";
//  }

//  auto source = "let x = 10;";
//
//  Lexer lexer;
//  auto tokens = lexer.lex(source);

  auto source = "print true;";

  VM vm;

  std::stringstream buffer;
  vm.interpret_with_output(source, &buffer);

  std::cout << buffer.rdbuf();

  return 0;
}
