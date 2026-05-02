#include "peechi/ast/Stmt.hpp"

#include <utility>

namespace peechi::ast
{

    Stmt::~Stmt() = default;

    PrintStmt::PrintStmt(std::vector<ExprPtr> arguments) : arguments(std::move(arguments)) {}
    ExpressionStmt::ExpressionStmt(ExprPtr expression) : expression(std::move(expression)) {}
    AssignStmt::AssignStmt(lexer::Token name, ExprPtr value) : name(std::move(name)), value(std::move(value)) {}
    BlockStmt::BlockStmt(std::vector<StmtPtr> statements) : statements(std::move(statements)) {}
    IfStmt::IfStmt(ExprPtr condition, StmtPtr thenBranch, StmtPtr elseBranch)
        : condition(std::move(condition)), thenBranch(std::move(thenBranch)), elseBranch(std::move(elseBranch)) {}
    WhileStmt::WhileStmt(ExprPtr condition, StmtPtr body)
        : condition(std::move(condition)), body(std::move(body)) {}
    LoopStmt::LoopStmt(StmtPtr body) : body(std::move(body)) {}
    BreakStmt::BreakStmt(lexer::Token keyword) : keyword(std::move(keyword)) {}

} // namespace peechi::ast
