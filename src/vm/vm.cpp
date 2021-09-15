#include <iostream>
#include <sstream>
#include <compiler/compiler.h>
#include "vm.h"

void VM::interpret(std::string source) {
  // TODO: Use interpret_with_output.
  auto fun = compile(source);

  output = &std::cout;

  chunk = fun.chunk;
  ip = 0;
  run();
}

void VM::interpret_with_output(std::string source, std::stringstream *buffer) {
  auto fun = compile(source);

  output = buffer;

  chunk = fun.chunk;
  ip = 0;
  run();
}

void VM::run() {
  while (ip < current_chunk().get_code().size()) {
    switch (static_cast<Opcode>(read_byte())) {
      case Opcode::return_:
        std::cout << "return_\n";
        break;
      case Opcode::constant:
        constant();
        break;
      case Opcode::add:
        add();
        break;
      case Opcode::subtract:
        subtract();
        break;
      case Opcode::multiply:
        multiply();
        break;
      case Opcode::divide:
        divide();
        break;
      case Opcode::print:
        print();
        break;
    }
  }
}

void VM::constant() {
  push(read_constant());
}

void VM::add() {
  auto b = pop();
  auto a = pop();
  push(a + b);
}

void VM::subtract() {
  auto b = pop();
  auto a = pop();
  push(a - b);
}

void VM::multiply() {
  auto b = pop();
  auto a = pop();
  push(a * b);
}

void VM::divide() {
  auto b = pop();
  auto a = pop();
  push(a / b);
}

void VM::print() {
  auto popped = pop();
  *output << popped;
}

void VM::push(Value value) {
  stack.push_back(value);
}

Value VM::pop() {
  auto popped = stack.back();
  stack.pop_back();
  return popped; // TODO: Pop back?
}

Value VM::read_constant() {
  auto index = read_byte();
  return current_chunk().read_constant(index);
}

std::uint8_t VM::read_byte() {
  auto byte = current_chunk().get_code()[ip];
  ip = ip + 1;
  return byte;
}

Chunk VM::current_chunk() {
  return chunk;
}
