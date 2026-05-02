#include "peechi/runtime/Environment.hpp"
#include "peechi/diagnostics/PeechiError.hpp"

#include <utility>

namespace peechi::runtime
{

    void Environment::assign(const lexer::Token &name, Value value)
    {
        values_[name.lexeme] = std::move(value);
    }

    Value Environment::get(const lexer::Token &name) const
    {
        auto it = values_.find(name.lexeme);
        if (it == values_.end())
        {
            throw diagnostics::PeechiError("execução", "variável não definida: " + name.lexeme, name.line, name.column);
        }
        return it->second;
    }

    bool Environment::exists(const std::string &name) const
    {
        return values_.find(name) != values_.end();
    }

} // namespace peechi::runtime
