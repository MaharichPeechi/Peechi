#pragma once

#include "peechi/lexer/Token.hpp"

#include <string>
#include <vector>

namespace peechi::lexer
{

    class Lexer
    {
    public:
        explicit Lexer(std::string source);

        std::vector<Token> tokenize();

    private:
        bool isAtEnd() const;
        char advance();
        char peek() const;
        char peekNext() const;
        bool match(char expected);

        void addToken(TokenType type);
        void addToken(TokenType type, std::string lexeme);

        void scanToken();
        void scanString(char quote);
        void scanNumber();
        void scanIdentifier();
        void skipLineComment();

        static bool isAlpha(char c);
        static bool isAlphaNumeric(char c);

        std::string source_;
        std::vector<Token> tokens_;
        std::size_t start_ = 0;
        std::size_t current_ = 0;
        int line_ = 1;
        int column_ = 1;
        int startLine_ = 1;
        int startColumn_ = 1;
    };

} // namespace peechi::lexer
