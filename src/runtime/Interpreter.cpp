#include "peechi/runtime/Interpreter.hpp"
#include "peechi/diagnostics/PeechiError.hpp"

#include <cmath>

namespace peechi::runtime
{

    using lexer::TokenType;

    Interpreter::Interpreter(std::ostream &out) : out_(out) {}

    void Interpreter::interpret(const std::vector<ast::StmtPtr> &statements)
    {
        try
        {
            executeBlock(statements);
        }
        catch (const BreakSignal &)
        {
            throw diagnostics::PeechiError("execução", "break só pode ser usado dentro de loop");
        }
    }

    void Interpreter::execute(const ast::Stmt &stmt)
    {
        if (const auto *s = dynamic_cast<const ast::PrintStmt *>(&stmt))
        {
            for (std::size_t i = 0; i < s->arguments.size(); ++i)
            {
                if (i > 0)
                    out_ << ' ';
                out_ << evaluate(*s->arguments[i]).toString();
            }
            out_ << '\n';
            return;
        }

        if (const auto *s = dynamic_cast<const ast::ExpressionStmt *>(&stmt))
        {
            (void)evaluate(*s->expression);
            return;
        }

        if (const auto *s = dynamic_cast<const ast::AssignStmt *>(&stmt))
        {
            environment_.assign(s->name, evaluate(*s->value));
            return;
        }

        if (const auto *s = dynamic_cast<const ast::BlockStmt *>(&stmt))
        {
            executeBlock(s->statements);
            return;
        }

        if (const auto *s = dynamic_cast<const ast::IfStmt *>(&stmt))
        {
            if (evaluate(*s->condition).isTruthy())
            {
                execute(*s->thenBranch);
            }
            else if (s->elseBranch)
            {
                execute(*s->elseBranch);
            }
            return;
        }

        if (const auto *s = dynamic_cast<const ast::WhileStmt *>(&stmt))
        {
            while (evaluate(*s->condition).isTruthy())
            {
                try
                {
                    execute(*s->body);
                }
                catch (const BreakSignal &)
                {
                    break;
                }
            }
            return;
        }

        if (const auto *s = dynamic_cast<const ast::LoopStmt *>(&stmt))
        {
            while (true)
            {
                try
                {
                    execute(*s->body);
                }
                catch (const BreakSignal &)
                {
                    break;
                }
            }
            return;
        }

        if (dynamic_cast<const ast::BreakStmt *>(&stmt))
        {
            throw BreakSignal{};
        }

        throw diagnostics::PeechiError("execução", "instrução desconhecida");
    }

    void Interpreter::executeBlock(const std::vector<ast::StmtPtr> &statements)
    {
        for (const auto &statement : statements)
        {
            execute(*statement);
        }
    }

    Value Interpreter::evaluate(const ast::Expr &expr)
    {
        if (const auto *e = dynamic_cast<const ast::LiteralExpr *>(&expr))
            return evaluateLiteral(*e);
        if (const auto *e = dynamic_cast<const ast::VariableExpr *>(&expr))
            return evaluateVariable(*e);
        if (const auto *e = dynamic_cast<const ast::UnaryExpr *>(&expr))
            return evaluateUnary(*e);
        if (const auto *e = dynamic_cast<const ast::BinaryExpr *>(&expr))
            return evaluateBinary(*e);

        throw diagnostics::PeechiError("execução", "expressão desconhecida");
    }

    Value Interpreter::evaluateLiteral(const ast::LiteralExpr &expr)
    {
        return expr.value;
    }

    Value Interpreter::evaluateVariable(const ast::VariableExpr &expr)
    {
        return environment_.get(expr.name);
    }

    Value Interpreter::evaluateUnary(const ast::UnaryExpr &expr)
    {
        Value right = evaluate(*expr.right);

        if (expr.op.type == TokenType::Minus)
        {
            requireNumber(right, expr.op);
            return Value(-right.asNumber());
        }

        throw diagnostics::PeechiError("execução", "operador unário desconhecido", expr.op.line, expr.op.column);
    }

    Value Interpreter::evaluateBinary(const ast::BinaryExpr &expr)
    {
        Value left = evaluate(*expr.left);
        Value right = evaluate(*expr.right);

        switch (expr.op.type)
        {
        case TokenType::Plus:
            if (left.isNumber() && right.isNumber())
            {
                return Value(left.asNumber() + right.asNumber());
            }
            if (left.isString() && right.isString())
            {
                return Value(left.asString() + right.asString());
            }
            throw diagnostics::PeechiError("execução", "operador + só aceita número + número ou texto + texto nesta versão", expr.op.line, expr.op.column);

        case TokenType::Minus:
            requireNumbers(left, right, expr.op);
            return Value(left.asNumber() - right.asNumber());

        case TokenType::Star:
            requireNumbers(left, right, expr.op);
            return Value(left.asNumber() * right.asNumber());

        case TokenType::Slash:
            requireNumbers(left, right, expr.op);
            if (right.asNumber() == 0.0)
            {
                throw diagnostics::PeechiError("execução", "divisão por zero", expr.op.line, expr.op.column);
            }
            return Value(left.asNumber() / right.asNumber());

        case TokenType::Greater:
            requireNumbers(left, right, expr.op);
            return Value(left.asNumber() > right.asNumber());

        case TokenType::GreaterEqual:
            requireNumbers(left, right, expr.op);
            return Value(left.asNumber() >= right.asNumber());

        case TokenType::Less:
            requireNumbers(left, right, expr.op);
            return Value(left.asNumber() < right.asNumber());

        case TokenType::LessEqual:
            requireNumbers(left, right, expr.op);
            return Value(left.asNumber() <= right.asNumber());

        case TokenType::EqualEqual:
            return Value(left == right);

        case TokenType::BangEqual:
            return Value(left != right);

        default:
            break;
        }

        throw diagnostics::PeechiError("execução", "operador binário desconhecido", expr.op.line, expr.op.column);
    }

    void Interpreter::requireNumber(const Value &value, const lexer::Token &op)
    {
        if (!value.isNumber())
        {
            throw diagnostics::PeechiError("execução", "operador '" + op.lexeme + "' precisa de número", op.line, op.column);
        }
    }

    void Interpreter::requireNumbers(const Value &left, const Value &right, const lexer::Token &op)
    {
        if (!left.isNumber() || !right.isNumber())
        {
            throw diagnostics::PeechiError("execução", "operador '" + op.lexeme + "' precisa de dois números", op.line, op.column);
        }
    }

} // namespace peechi::runtime
