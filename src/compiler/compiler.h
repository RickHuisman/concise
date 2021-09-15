#ifndef CONCISE_COMPILER_H
#define CONCISE_COMPILER_H

#include <string>
#include <vector>
#include <optional>
#include "object.h"

struct Local {
  std::string name;
  uint8_t depth; // TODO: uint8_t?
  bool initialized;
  uint8_t slot; // TODO: uint8_t
};

struct Locals {
  std::vector<Local> locals;
  std::uint8_t scope_depth = 0; // TODO: uint8_t
};

struct CompilerInstance {
  CompilerInstance(FunctionType function_type)
      : function(Function()), function_type(function_type) {};

  Function function;
  FunctionType function_type;
  Locals locals;
  std::optional<CompilerInstance *> enclosing;
};

class Compiler {
  CompilerInstance current;
  // TODO: Errors.

public:
  Compiler() : current(CompilerInstance(FunctionType::Script)) {}

  Function end_compiler();

  void emit_constant(Value value);

  void emit(Opcode opcode);

  void emit_byte(uint8_t byte);

  Chunk * current_chunk();
};

Function compile(std::string source);

#endif //CONCISE_COMPILER_H
