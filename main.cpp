#include <iostream>
#include <vector>
#include "syntax/lexer.h"

int main() {
  auto source = "let x = 10;";

  Lexer lexer;
  auto tokens = lexer.lex(source);
  for (const auto& tk : tokens) {
    std::cout << tk.source << "\n";
  }

  return 0;
}
