#pragma once

#include "peechi/ast/Stmt.hpp"
#include "peechi/lexer/Token.hpp"

#include <initializer_list>
#include <vector>

namespace peechi::parser
{

    class Parser
    {
    public:
        explicit Parser(std::vector<lexer::Token> tokens);

        std::vector<ast::StmtPtr> parse();

    private:
        ast::StmtPtr declaration();
        ast::StmtPtr statement();
        ast::StmtPtr printStatement();
        ast::StmtPtr assignmentStatement();
        ast::StmtPtr ifStatement();
        ast::StmtPtr whileStatement();
        ast::StmtPtr loopStatement();
        ast::StmtPtr breakStatement();
        ast::StmtPtr blockStatement();
        std::vector<ast::StmtPtr> blockBody();

        ast::ExprPtr expression();
        ast::ExprPtr equality();
        ast::ExprPtr comparison();
        ast::ExprPtr term();
        ast::ExprPtr factor();
        ast::ExprPtr unary();
        ast::ExprPtr primary();

        bool match(std::initializer_list<lexer::TokenType> types);
        bool check(lexer::TokenType type) const;
        bool checkNext(lexer::TokenType type) const;
        const lexer::Token &advance();
        bool isAtEnd() const;
        const lexer::Token &peek() const;
        const lexer::Token &previous() const;
        const lexer::Token &consume(lexer::TokenType type, const std::string &message);

        std::vector<lexer::Token> tokens_;
        std::size_t current_ = 0;
    };

} // namespace peechi::parser
