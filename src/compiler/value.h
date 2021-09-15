#ifndef CONCISE_VALUE_H
#define CONCISE_VALUE_H

#include <variant>
#include <iostream>

using Value = std::variant<double, bool>;

Value operator+(const Value &a, const Value &b);

Value operator-(const Value &a, const Value &b);

Value operator*(const Value &a, const Value &b);

Value operator/(const Value &a, const Value &b);

std::ostream& operator<<(std::ostream& os, const Value & value);

#endif //CONCISE_VALUE_H
