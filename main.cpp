#include <iostream>
#include <vector>
#include "syntax/lexer.h"
#include "vm/chunk.h"

int main() {
  Chunk chunk;
//  chunk.write(Opcode::return_);
//  chunk.write(Opcode::constant);
//  chunk.write(Opcode::multiply);
  chunk.write(Opcode::constant);
  auto index = chunk.add_constant(10.0);
  chunk.write_byte(index);

  std::cout << "test";

//  auto source = "let x = 10;";
//
//  Lexer lexer;
//  auto tokens = lexer.lex(source);
//  for (const auto& tk : tokens) {
//    std::cout << tk.source << "\n";
//  }

  return 0;
}
