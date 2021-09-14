#ifndef CONCISE_AST_H
#define CONCISE_AST_H

#include <string>

using Identifier = std::string;

class Expr {
};

struct LetAssignExpr : Expr {
  explicit LetAssignExpr(std::string str, Expr *ex) : Expr() { // TODO: Naming.
    ident = str;
    initializer = ex;
  }

  Identifier ident;
  Expr* initializer;
};

struct LetSetExpr : Expr {
  explicit LetSetExpr(std::string str, Expr *ex) : Expr() { // TODO: Naming.
    ident = str;
    expr = ex;
  }

  Identifier ident;
  Expr* expr;
};

struct LetGetExpr : Expr {
  explicit LetGetExpr(std::string str) : Expr() { // TODO: Naming.
    ident = str;
  }

  Identifier ident;
};

struct IntExpr : Expr { // TODO: Create a Literal interface.
  explicit IntExpr(int v) {
    value = v;
  };

  int value;
};

#endif //CONCISE_AST_H
