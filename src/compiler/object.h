#ifndef CONCISE_OBJECT_H
#define CONCISE_OBJECT_H

#include "chunk.h"

enum class FunctionType {
  Closure,
  Function,
  Script,
};

struct Function {
  std::string name;
  Chunk chunk;
  std::uint8_t arity = 0;

  Function() {} // TODO: Init chunk
};

#endif //CONCISE_OBJECT_H
