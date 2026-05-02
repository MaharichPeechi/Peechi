#include "peechi/parser/Parser.hpp"
#include "peechi/diagnostics/PeechiError.hpp"

#include <cstdlib>

namespace peechi::parser
{

    using lexer::TokenType;

    Parser::Parser(std::vector<lexer::Token> tokens) : tokens_(std::move(tokens)) {}

    std::vector<ast::StmtPtr> Parser::parse()
    {
        std::vector<ast::StmtPtr> statements;
        while (!isAtEnd())
        {
            statements.push_back(declaration());
        }
        return statements;
    }

    ast::StmtPtr Parser::declaration()
    {
        return statement();
    }

    ast::StmtPtr Parser::statement()
    {
        if (match({TokenType::Print}))
            return printStatement();
        if (match({TokenType::If}))
            return ifStatement();
        if (match({TokenType::While}))
            return whileStatement();
        if (match({TokenType::Loop}))
            return loopStatement();
        if (match({TokenType::Break}))
            return breakStatement();
        if (check(TokenType::Identifier) && checkNext(TokenType::Equal))
            return assignmentStatement();

        auto expr = expression();
        return std::make_unique<ast::ExpressionStmt>(std::move(expr));
    }

    ast::StmtPtr Parser::printStatement()
    {
        consume(TokenType::LeftParen, "esperado '(' depois de print");

        std::vector<ast::ExprPtr> arguments;
        if (!check(TokenType::RightParen))
        {
            do
            {
                arguments.push_back(expression());
            } while (match({TokenType::Comma}));
        }

        consume(TokenType::RightParen, "esperado ')' depois dos argumentos de print");
        return std::make_unique<ast::PrintStmt>(std::move(arguments));
    }

    ast::StmtPtr Parser::assignmentStatement()
    {
        lexer::Token name = advance();
        consume(TokenType::Equal, "esperado '=' na atribuição");
        auto value = expression();
        return std::make_unique<ast::AssignStmt>(std::move(name), std::move(value));
    }

    ast::StmtPtr Parser::ifStatement()
    {
        auto condition = expression();
        auto thenBranch = blockStatement();

        ast::StmtPtr elseBranch;
        if (match({TokenType::Else}))
        {
            elseBranch = blockStatement();
        }

        return std::make_unique<ast::IfStmt>(std::move(condition), std::move(thenBranch), std::move(elseBranch));
    }

    ast::StmtPtr Parser::whileStatement()
    {
        auto condition = expression();
        auto body = blockStatement();
        return std::make_unique<ast::WhileStmt>(std::move(condition), std::move(body));
    }

    ast::StmtPtr Parser::loopStatement()
    {
        auto body = blockStatement();
        return std::make_unique<ast::LoopStmt>(std::move(body));
    }

    ast::StmtPtr Parser::breakStatement()
    {
        return std::make_unique<ast::BreakStmt>(previous());
    }

    ast::StmtPtr Parser::blockStatement()
    {
        consume(TokenType::LeftBrace, "esperado '{' para iniciar bloco");
        return std::make_unique<ast::BlockStmt>(blockBody());
    }

    std::vector<ast::StmtPtr> Parser::blockBody()
    {
        std::vector<ast::StmtPtr> statements;

        while (!check(TokenType::RightBrace) && !isAtEnd())
        {
            statements.push_back(declaration());
        }

        consume(TokenType::RightBrace, "esperado '}' para fechar bloco");
        return statements;
    }

    ast::ExprPtr Parser::expression()
    {
        return equality();
    }

    ast::ExprPtr Parser::equality()
    {
        auto expr = comparison();

        while (match({TokenType::BangEqual, TokenType::EqualEqual}))
        {
            lexer::Token op = previous();
            auto right = comparison();
            expr = std::make_unique<ast::BinaryExpr>(std::move(expr), std::move(op), std::move(right));
        }

        return expr;
    }

    ast::ExprPtr Parser::comparison()
    {
        auto expr = term();

        while (match({TokenType::Greater, TokenType::GreaterEqual, TokenType::Less, TokenType::LessEqual}))
        {
            lexer::Token op = previous();
            auto right = term();
            expr = std::make_unique<ast::BinaryExpr>(std::move(expr), std::move(op), std::move(right));
        }

        return expr;
    }

    ast::ExprPtr Parser::term()
    {
        auto expr = factor();

        while (match({TokenType::Plus, TokenType::Minus}))
        {
            lexer::Token op = previous();
            auto right = factor();
            expr = std::make_unique<ast::BinaryExpr>(std::move(expr), std::move(op), std::move(right));
        }

        return expr;
    }

    ast::ExprPtr Parser::factor()
    {
        auto expr = unary();

        while (match({TokenType::Star, TokenType::Slash}))
        {
            lexer::Token op = previous();
            auto right = unary();
            expr = std::make_unique<ast::BinaryExpr>(std::move(expr), std::move(op), std::move(right));
        }

        return expr;
    }

    ast::ExprPtr Parser::unary()
    {
        if (match({TokenType::Minus}))
        {
            lexer::Token op = previous();
            auto right = unary();
            return std::make_unique<ast::UnaryExpr>(std::move(op), std::move(right));
        }

        return primary();
    }

    ast::ExprPtr Parser::primary()
    {
        if (match({TokenType::False}))
            return std::make_unique<ast::LiteralExpr>(runtime::Value(false));
        if (match({TokenType::True}))
            return std::make_unique<ast::LiteralExpr>(runtime::Value(true));

        if (match({TokenType::Number}))
        {
            double value = std::strtod(previous().lexeme.c_str(), nullptr);
            return std::make_unique<ast::LiteralExpr>(runtime::Value(value));
        }

        if (match({TokenType::String}))
        {
            return std::make_unique<ast::LiteralExpr>(runtime::Value(previous().lexeme));
        }

        if (match({TokenType::Identifier}))
        {
            return std::make_unique<ast::VariableExpr>(previous());
        }

        const auto &token = peek();
        throw diagnostics::PeechiError("sintaxe", "expressão esperada, encontrei '" + token.lexeme + "'", token.line, token.column);
    }

    bool Parser::match(std::initializer_list<TokenType> types)
    {
        for (TokenType type : types)
        {
            if (check(type))
            {
                advance();
                return true;
            }
        }
        return false;
    }

    bool Parser::check(TokenType type) const
    {
        if (isAtEnd())
            return false;
        return peek().type == type;
    }

    bool Parser::checkNext(TokenType type) const
    {
        if (current_ + 1 >= tokens_.size())
            return false;
        return tokens_[current_ + 1].type == type;
    }

    const lexer::Token &Parser::advance()
    {
        if (!isAtEnd())
            current_++;
        return previous();
    }

    bool Parser::isAtEnd() const
    {
        return peek().type == TokenType::EndOfFile;
    }

    const lexer::Token &Parser::peek() const
    {
        return tokens_[current_];
    }

    const lexer::Token &Parser::previous() const
    {
        return tokens_[current_ - 1];
    }

    const lexer::Token &Parser::consume(TokenType type, const std::string &message)
    {
        if (check(type))
            return advance();

        const auto &token = peek();
        throw diagnostics::PeechiError("sintaxe", message + ", encontrei '" + token.lexeme + "'", token.line, token.column);
    }

} // namespace peechi::parser
