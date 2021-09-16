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

Value operator-(const Value& a) {
  return -std::get<double>(a);
}

Value operator!(const Value& a) {
  return !std::get<bool>(a);
}

std::ostream &operator<<(std::ostream &os, const Value &value) {
  std::visit([&os, &value](auto &&arg) {
    using T = std::decay_t<decltype(arg)>;
    if constexpr (std::is_same_v<T, double>) {
      os << std::get<double>(value);
    }
    if constexpr(std::is_same_v<T, bool>) {
      if (std::get<bool>(value)) {
        os << "true";
      } else {
        os << "false";
      }
    }
    if constexpr(std::is_same_v<T, std::string>) {
      os << std::get<std::string>(value);
    }
    // TODO: Throw exception.
  }, value);

  return os;
}
