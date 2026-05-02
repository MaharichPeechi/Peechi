#include "peechi/lexer/Lexer.hpp"
#include "peechi/diagnostics/PeechiError.hpp"

#include <cctype>
#include <unordered_map>
#include <utility>

namespace peechi::lexer
{

    Lexer::Lexer(std::string source) : source_(std::move(source)) {}

    std::vector<Token> Lexer::tokenize()
    {
        while (!isAtEnd())
        {
            start_ = current_;
            startLine_ = line_;
            startColumn_ = column_;
            scanToken();
        }

        tokens_.push_back(Token{TokenType::EndOfFile, "", line_, column_});
        return tokens_;
    }

    bool Lexer::isAtEnd() const
    {
        return current_ >= source_.size();
    }

    char Lexer::advance()
    {
        char c = source_[current_++];
        if (c == '\n')
        {
            line_++;
            column_ = 1;
        }
        else
        {
            column_++;
        }
        return c;
    }

    char Lexer::peek() const
    {
        if (isAtEnd())
            return '\0';
        return source_[current_];
    }

    char Lexer::peekNext() const
    {
        if (current_ + 1 >= source_.size())
            return '\0';
        return source_[current_ + 1];
    }

    bool Lexer::match(char expected)
    {
        if (isAtEnd())
            return false;
        if (source_[current_] != expected)
            return false;
        advance();
        return true;
    }

    void Lexer::addToken(TokenType type)
    {
        addToken(type, source_.substr(start_, current_ - start_));
    }

    void Lexer::addToken(TokenType type, std::string lexeme)
    {
        tokens_.push_back(Token{type, std::move(lexeme), startLine_, startColumn_});
    }

    void Lexer::scanToken()
    {
        char c = advance();

        switch (c)
        {
        case '(':
            addToken(TokenType::LeftParen);
            break;
        case ')':
            addToken(TokenType::RightParen);
            break;
        case '{':
            addToken(TokenType::LeftBrace);
            break;
        case '}':
            addToken(TokenType::RightBrace);
            break;
        case ',':
            addToken(TokenType::Comma);
            break;
        case '+':
            addToken(TokenType::Plus);
            break;
        case '-':
            addToken(TokenType::Minus);
            break;
        case '*':
            addToken(TokenType::Star);
            break;
        case '/':
            if (match('/'))
            {
                skipLineComment();
            }
            else
            {
                addToken(TokenType::Slash);
            }
            break;
        case '=':
            addToken(match('=') ? TokenType::EqualEqual : TokenType::Equal);
            break;
        case '!':
            if (match('='))
            {
                addToken(TokenType::BangEqual);
            }
            else
            {
                throw diagnostics::PeechiError("léxico", "use != para diferença; ! sozinho ainda não existe", startLine_, startColumn_);
            }
            break;
        case '>':
            addToken(match('=') ? TokenType::GreaterEqual : TokenType::Greater);
            break;
        case '<':
            addToken(match('=') ? TokenType::LessEqual : TokenType::Less);
            break;
        case ' ':
        case '\r':
        case '\t':
        case '\n':
            break;
        case '"':
        case '\'':
            scanString(c);
            break;
        default:
            if (std::isdigit(static_cast<unsigned char>(c)))
            {
                scanNumber();
            }
            else if (isAlpha(c))
            {
                scanIdentifier();
            }
            else
            {
                throw diagnostics::PeechiError("léxico", std::string("caractere inesperado: ") + c, startLine_, startColumn_);
            }
            break;
        }
    }

    void Lexer::scanString(char quote)
    {
        while (peek() != quote && !isAtEnd())
        {
            advance();
        }

        if (isAtEnd())
        {
            throw diagnostics::PeechiError("léxico", "texto sem fechamento de aspas", startLine_, startColumn_);
        }

        advance();
        std::string value = source_.substr(start_ + 1, current_ - start_ - 2);
        addToken(TokenType::String, value);
    }

    void Lexer::scanNumber()
    {
        while (std::isdigit(static_cast<unsigned char>(peek())))
        {
            advance();
        }

        if (peek() == '.' && std::isdigit(static_cast<unsigned char>(peekNext())))
        {
            advance();
            while (std::isdigit(static_cast<unsigned char>(peek())))
            {
                advance();
            }
        }

        addToken(TokenType::Number);
    }

    void Lexer::scanIdentifier()
    {
        while (isAlphaNumeric(peek()))
        {
            advance();
        }

        std::string text = source_.substr(start_, current_ - start_);

        static const std::unordered_map<std::string, TokenType> keywords = {
            {"true", TokenType::True},
            {"false", TokenType::False},
            {"if", TokenType::If},
            {"else", TokenType::Else},
            {"while", TokenType::While},
            {"loop", TokenType::Loop},
            {"break", TokenType::Break},
            {"print", TokenType::Print},
        };

        auto it = keywords.find(text);
        if (it != keywords.end())
        {
            addToken(it->second, text);
        }
        else
        {
            addToken(TokenType::Identifier, text);
        }
    }

    void Lexer::skipLineComment()
    {
        while (peek() != '\n' && !isAtEnd())
        {
            advance();
        }
    }

    bool Lexer::isAlpha(char c)
    {
        return std::isalpha(static_cast<unsigned char>(c)) || c == '_';
    }

    bool Lexer::isAlphaNumeric(char c)
    {
        return isAlpha(c) || std::isdigit(static_cast<unsigned char>(c));
    }

} // namespace peechi::lexer
