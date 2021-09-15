#ifndef CONCISE_CHUNK_H
#define CONCISE_CHUNK_H

#include <vector>
#include <compiler/value.h>
#include "vm/opcode.h"

class Chunk {
  std::vector<std::uint8_t> code;
  std::vector<Value> constants;

public:
  void write(Opcode opcode);

  void write_byte(std::uint8_t byte);

  std::uint8_t add_constant(Value value);

  std::vector<std::uint8_t> get_code();

  std::vector<Value> get_constants();

  Value read_constant(uint8_t index);
};

#endif //CONCISE_CHUNK_H
