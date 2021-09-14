#ifndef CONCISE_VM_H
#define CONCISE_VM_H

#include "chunk.h"

class VM {
private:
  std::vector<Value> stack;
  Chunk chunk;
  std::uint8_t ip;

  std::uint8_t read_byte();

public:
  void interpret(Chunk chunk); // TODO: Return interpret result.
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
};

#endif //CONCISE_VM_H