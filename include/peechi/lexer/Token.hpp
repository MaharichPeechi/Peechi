#pragma once

#include <string>

namespace peechi::lexer
{

    enum class TokenType
    {
        LeftParen,
        RightParen,
        LeftBrace,
        RightBrace,
        Comma,

        Plus,
        Minus,
        Star,
        Slash,

        Equal,
        EqualEqual,
        BangEqual,
        Greater,
        GreaterEqual,
        Less,
        LessEqual,

        Identifier,
        String,
        Number,

        True,
        False,

        If,
        Else,
        While,
        Loop,
        Break,
        Print,

        EndOfFile
    };

    struct Token
    {
        TokenType type;
        std::string lexeme;
        int line;
        int column;
    };

    std::string tokenTypeName(TokenType type);

} // namespace peechi::lexer
