#include <iostream>
#include <vector>
#include <sstream>
#include "syntax/lexer.h"
#include "compiler/chunk.h"
#include "vm/vm.h"
#include "parser/parser.h"
#include "compiler/compiler.h"

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

  // auto source = "print true != false;";
  auto source = "print \"test\";";

  // Lexer lexer(source);
  // auto tokens = lexer.lex();

  // for (auto tk : tokens) {
  //   if (tk.token_type == TokenType::equal_equal) {
  //     std::cout << "works" << std::endl;
  //   }

  // }

  VM vm;
  vm.interpret(source);

  return 0;
}
