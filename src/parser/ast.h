#ifndef CONCISE_AST_H
#define CONCISE_AST_H

#include <string>
#include <compiler/compiler.h>

using Identifier = std::string;

class Expr {
public:
  Expr() = default;

  virtual void compile(Compiler *compiler) = 0;
};

enum class BinaryOperator {
  subtract,
  add,
  divide,
  multiply,
  equal,
  bang_equal,
  greater_than,
  greater_than_equal,
  less_than,
  less_than_equal,
};

class BinaryExpr : public Expr {
public:
  explicit BinaryExpr(Expr *left, BinaryOperator op, Expr *right)
      : Expr(),
        left_(left),
        op_(op),
        right_(right) {}

  void compile(Compiler *compiler);

  Expr *left() const { return left_; }

  BinaryOperator op() const { return op_; }

  Expr *right() const { return right_; }

private:
  Expr *left_;
  BinaryOperator op_;
  Expr *right_;
};

struct LetAssignExpr : Expr {
  explicit LetAssignExpr(std::string str, Expr *ex) : Expr() { // TODO: Naming.
    ident = str;
    initializer = ex;
  }

  Identifier ident;
  Expr *initializer;

  void compile(Compiler *compiler);
};

struct LetSetExpr : Expr {
  explicit LetSetExpr(std::string str, Expr *ex) : Expr() { // TODO: Naming.
    ident = str;
    expr = ex;
  }

  Identifier ident;
  Expr *expr;

  void compile(Compiler *compiler);
};

struct LetGetExpr : Expr {
  explicit LetGetExpr(std::string str) : Expr() { // TODO: Naming.
    ident = str;
  }

  Identifier ident;

  void compile(Compiler *compiler);
};

struct PrintExpr : Expr {
  explicit PrintExpr(Expr *ex) : Expr() {
    expr = ex;
  }

  Expr *expr;

  void compile(Compiler *compiler);
};

struct NumberExpr : Expr { // TODO: Create a Literal interface.
  explicit NumberExpr(double v) {
    value = v;
  };

  double value;

  void compile(Compiler *compiler);
};

#endif //CONCISE_AST_H
