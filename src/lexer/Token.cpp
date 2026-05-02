#include "peechi/lexer/Token.hpp"

namespace peechi::lexer
{

    std::string tokenTypeName(TokenType type)
    {
        switch (type)
        {
        case TokenType::LeftParen:
            return "(";
        case TokenType::RightParen:
            return ")";
        case TokenType::LeftBrace:
            return "{";
        case TokenType::RightBrace:
            return "}";
        case TokenType::Comma:
            return ",";
        case TokenType::Plus:
            return "+";
        case TokenType::Minus:
            return "-";
        case TokenType::Star:
            return "*";
        case TokenType::Slash:
            return "/";
        case TokenType::Equal:
            return "=";
        case TokenType::EqualEqual:
            return "==";
        case TokenType::BangEqual:
            return "!=";
        case TokenType::Greater:
            return ">";
        case TokenType::GreaterEqual:
            return ">=";
        case TokenType::Less:
            return "<";
        case TokenType::LessEqual:
            return "<=";
        case TokenType::Identifier:
            return "identificador";
        case TokenType::String:
            return "texto";
        case TokenType::Number:
            return "número";
        case TokenType::True:
            return "true";
        case TokenType::False:
            return "false";
        case TokenType::If:
            return "if";
        case TokenType::Else:
            return "else";
        case TokenType::While:
            return "while";
        case TokenType::Loop:
            return "loop";
        case TokenType::Break:
            return "break";
        case TokenType::Print:
            return "print";
        case TokenType::EndOfFile:
            return "fim do arquivo";
        }
        return "token desconhecido";
    }

} // namespace peechi::lexer
