#include "chunk.h"

void Chunk::write(Opcode opcode) {
  code.push_back(static_cast<const unsigned char>(opcode)); // TODO: Works?
}

void Chunk::write_byte(std::uint8_t byte) {
  code.push_back(byte);
}

std::uint8_t Chunk::add_constant(Value value) {
  constants.push_back(value);
  return constants.size() - 1;
}

Value Chunk::read_constant(std::uint8_t index) {
  return constants[index];
}

std::vector<std::uint8_t> Chunk::get_code() {
  return code;
}

std::vector<Value> Chunk::get_constants() {
  return constants;
}
