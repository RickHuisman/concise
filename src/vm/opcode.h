#ifndef CONCISE_OPCODE_H
#define CONCISE_OPCODE_H

#include <cstdint>

enum class Opcode : std::uint8_t {
  return_,
  constant,
  add,
  subtract,
  multiply,
  equal,
  greater,
  less,
  divide,
  negate,
  not_,
  print,
};

#endif //CONCISE_OPCODE_H
