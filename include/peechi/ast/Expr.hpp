#pragma once

#include "peechi/lexer/Token.hpp"
#include "peechi/runtime/Value.hpp"

#include <memory>
#include <string>

namespace peechi::ast
{

    struct Expr
    {
        virtual ~Expr();
    };

    using ExprPtr = std::unique_ptr<Expr>;

    struct LiteralExpr final : Expr
    {
        explicit LiteralExpr(runtime::Value value);
        runtime::Value value;
    };

    struct VariableExpr final : Expr
    {
        explicit VariableExpr(lexer::Token name);
        lexer::Token name;
    };

    struct UnaryExpr final : Expr
    {
        UnaryExpr(lexer::Token op, ExprPtr right);
        lexer::Token op;
        ExprPtr right;
    };

    struct BinaryExpr final : Expr
    {
        BinaryExpr(ExprPtr left, lexer::Token op, ExprPtr right);
        ExprPtr left;
        lexer::Token op;
        ExprPtr right;
    };

} // namespace peechi::ast
