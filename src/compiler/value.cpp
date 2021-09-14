#include "value.h"

Value operator+(const Value &a, const Value &b) {
  // TODO: Throw exception.
  return std::get<double>(a) + std::get<double>(b);
}

Value operator-(const Value &a, const Value &b) {
  // TODO: Throw exception.
  return std::get<double>(a) - std::get<double>(b);
}

Value operator/(const Value &a, const Value &b) {
  // TODO: Throw exception.
  return std::get<double>(a) / std::get<double>(b);
}

Value operator*(const Value &a, const Value &b) {
  // TODO: Throw exception.
  return std::get<double>(a) * std::get<double>(b);
}
