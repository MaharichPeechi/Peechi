#pragma once

#include "peechi/ast/Expr.hpp"
#include "peechi/lexer/Token.hpp"

#include <memory>
#include <string>
#include <vector>

namespace peechi::ast
{

    struct Stmt
    {
        virtual ~Stmt();
    };

    using StmtPtr = std::unique_ptr<Stmt>;

    struct PrintStmt final : Stmt
    {
        explicit PrintStmt(std::vector<ExprPtr> arguments);
        std::vector<ExprPtr> arguments;
    };

    struct ExpressionStmt final : Stmt
    {
        explicit ExpressionStmt(ExprPtr expression);
        ExprPtr expression;
    };

    struct AssignStmt final : Stmt
    {
        AssignStmt(lexer::Token name, ExprPtr value);
        lexer::Token name;
        ExprPtr value;
    };

    struct BlockStmt final : Stmt
    {
        explicit BlockStmt(std::vector<StmtPtr> statements);
        std::vector<StmtPtr> statements;
    };

    struct IfStmt final : Stmt
    {
        IfStmt(ExprPtr condition, StmtPtr thenBranch, StmtPtr elseBranch);
        ExprPtr condition;
        StmtPtr thenBranch;
        StmtPtr elseBranch;
    };

    struct WhileStmt final : Stmt
    {
        WhileStmt(ExprPtr condition, StmtPtr body);
        ExprPtr condition;
        StmtPtr body;
    };

    struct LoopStmt final : Stmt
    {
        explicit LoopStmt(StmtPtr body);
        StmtPtr body;
    };

    struct BreakStmt final : Stmt
    {
        explicit BreakStmt(lexer::Token keyword);
        lexer::Token keyword;
    };

} // namespace peechi::ast
