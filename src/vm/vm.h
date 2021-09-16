#ifndef CONCISE_VM_H
#define CONCISE_VM_H

#include "compiler/chunk.h"

class VM {
private:
  std::ostream *output; // TODO: Fix.

  std::vector<Value> stack;
  Chunk chunk;
  std::uint8_t ip;

  std::uint8_t read_byte();

public:
  void interpret(std::string source); // TODO: Return interpret result.

  void interpret_with_output(std::string source, std::stringstream *buffer); // TODO: Return interpret result.

  void run();

  Chunk current_chunk();

  Value read_constant();

  void constant();

  void push(Value value);

  Value pop();

  void add();

  void subtract();

  void multiply();

  void divide();

  void negate();

  void not_();

  void equal();

  void greater();

  void less();

  void print();
};

#endif //CONCISE_VM_H
