#pragma once

#include "peechi/ast/Stmt.hpp"
#include "peechi/runtime/Environment.hpp"

#include <ostream>
#include <vector>

namespace peechi::runtime
{

    class Interpreter
    {
    public:
        explicit Interpreter(std::ostream &out);

        void interpret(const std::vector<ast::StmtPtr> &statements);

    private:
        struct BreakSignal
        {
        };

        void execute(const ast::Stmt &stmt);
        void executeBlock(const std::vector<ast::StmtPtr> &statements);

        Value evaluate(const ast::Expr &expr);
        Value evaluateLiteral(const ast::LiteralExpr &expr);
        Value evaluateVariable(const ast::VariableExpr &expr);
        Value evaluateUnary(const ast::UnaryExpr &expr);
        Value evaluateBinary(const ast::BinaryExpr &expr);

        static void requireNumber(const Value &value, const lexer::Token &op);
        static void requireNumbers(const Value &left, const Value &right, const lexer::Token &op);

        std::ostream &out_;
        Environment environment_;
    };

} // namespace peechi::runtime
