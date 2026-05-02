#include "peechi/ast/Expr.hpp"

#include <utility>

namespace peechi::ast
{

    Expr::~Expr() = default;

    LiteralExpr::LiteralExpr(runtime::Value value) : value(std::move(value)) {}
    VariableExpr::VariableExpr(lexer::Token name) : name(std::move(name)) {}
    UnaryExpr::UnaryExpr(lexer::Token op, ExprPtr right) : op(std::move(op)), right(std::move(right)) {}
    BinaryExpr::BinaryExpr(ExprPtr left, lexer::Token op, ExprPtr right)
        : left(std::move(left)), op(std::move(op)), right(std::move(right)) {}

} // namespace peechi::ast
