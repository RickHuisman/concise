#include "gtest/gtest.h"
#include "syntax/lexer.h"

TEST(lexer, lex_numbers) {
  auto source = "2 10 3.33";

  std::vector<Token> expect{
    Token(TokenType::number, "2"),
    Token(TokenType::number, "10"),
    Token(TokenType::number, ".33"),
  };

  Lexer lexer(source);
  auto tokens = lexer.lex();

  EXPECT_TRUE(expect == expect);
}

TEST(lexer, lex_strings) {
  auto source = R"("Hello" "," "World!")";

  std::vector<Token> expect{
      Token(TokenType::string, "Hello"),
      Token(TokenType::string, ","),
      Token(TokenType::string, "World!"),
  };

  Lexer lexer(source);
  auto tokens = lexer.lex();

  ASSERT_EQ(expect, expect);
}
