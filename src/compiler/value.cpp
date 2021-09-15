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

std::ostream &operator<<(std::ostream &os, const Value &value) {
  std::visit([&os, &value](auto &&arg) {
    using T = std::decay_t<decltype(arg)>;
    if constexpr (std::is_same_v<T, double>) {
      os << std::get<double>(value);
    }
    if constexpr(std::is_same_v<T, bool>) {
      os << std::get<bool>(value);
    }
    // TODO: Throw exception.
  }, value);

  return os;
}
