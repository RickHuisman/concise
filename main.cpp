#include <iostream>
#include <vector>
#include "syntax/lexer.h"
#include "vm/chunk.h"
#include "vm/vm.h"

int main() {
  Chunk chunk;

  chunk.write(Opcode::constant);
  auto index = chunk.add_constant(10.0);
  chunk.write_byte(index);

  chunk.write(Opcode::constant);
  auto index2 = chunk.add_constant(10.0);
  chunk.write_byte(index2);

  chunk.write(Opcode::add);

  VM vm;
  vm.interpret(chunk);

//  std::cout << "test";

//  auto source = "let x = 10;";
//
//  Lexer lexer;
//  auto tokens = lexer.lex(source);
//  for (const auto& tk : tokens) {
//    std::cout << tk.source << "\n";
//  }

  return 0;
}
