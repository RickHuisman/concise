#ifndef CONCISE_OPCODE_H
#define CONCISE_OPCODE_H

#include <cstdint>

enum class Opcode : std::uint8_t {
  return_,
  constant,
  add,
  subtract,
  multiply,
  divide,
};

#endif //CONCISE_OPCODE_H