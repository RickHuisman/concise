#ifndef CONCISE_CHUNK_H
#define CONCISE_CHUNK_H

#include <vector>
#include "../compiler/value.h"
#include "opcode.h"

class Chunk {
  std::vector<std::uint8_t> code;
  std::vector<Value> constants;

public:
  void write(Opcode opcode);

  void write_byte(std::uint8_t byte);

  std::uint8_t add_constant(Value value);
};

#endif //CONCISE_CHUNK_H
