#pragma once

#include <string>
#include <variant>

namespace peechi::runtime
{

    class Value
    {
    public:
        using Storage = std::variant<std::monostate, double, std::string, bool>;

        Value();
        explicit Value(double number);
        explicit Value(std::string text);
        explicit Value(bool boolean);

        bool isNull() const;
        bool isNumber() const;
        bool isString() const;
        bool isBool() const;

        double asNumber() const;
        const std::string &asString() const;
        bool asBool() const;

        bool isTruthy() const;
        std::string toString() const;
        std::string typeName() const;

        friend bool operator==(const Value &a, const Value &b);
        friend bool operator!=(const Value &a, const Value &b);

    private:
        Storage storage_;
    };

} // namespace peechi::runtime
