#pragma once

#include "peechi/runtime/Value.hpp"
#include "peechi/lexer/Token.hpp"

#include <string>
#include <unordered_map>

namespace peechi::runtime
{

    class Environment
    {
    public:
        void assign(const lexer::Token &name, Value value);
        Value get(const lexer::Token &name) const;
        bool exists(const std::string &name) const;

    private:
        std::unordered_map<std::string, Value> values_;
    };

} // namespace peechi::runtime
