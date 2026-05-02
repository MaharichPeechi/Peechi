#include "peechi/runtime/Value.hpp"
#include "peechi/diagnostics/PeechiError.hpp"

#include <cmath>
#include <iomanip>
#include <sstream>
#include <utility>

namespace peechi::runtime
{

    Value::Value() : storage_(std::monostate{}) {}
    Value::Value(double number) : storage_(number) {}
    Value::Value(std::string text) : storage_(std::move(text)) {}
    Value::Value(bool boolean) : storage_(boolean) {}

    bool Value::isNull() const { return std::holds_alternative<std::monostate>(storage_); }
    bool Value::isNumber() const { return std::holds_alternative<double>(storage_); }
    bool Value::isString() const { return std::holds_alternative<std::string>(storage_); }
    bool Value::isBool() const { return std::holds_alternative<bool>(storage_); }

    double Value::asNumber() const
    {
        if (!isNumber())
        {
            throw diagnostics::PeechiError("execução", "valor não é número");
        }
        return std::get<double>(storage_);
    }

    const std::string &Value::asString() const
    {
        if (!isString())
        {
            throw diagnostics::PeechiError("execução", "valor não é texto");
        }
        return std::get<std::string>(storage_);
    }

    bool Value::asBool() const
    {
        if (!isBool())
        {
            throw diagnostics::PeechiError("execução", "valor não é booleano");
        }
        return std::get<bool>(storage_);
    }

    bool Value::isTruthy() const
    {
        if (isNull())
            return false;
        if (isBool())
            return asBool();
        if (isNumber())
            return asNumber() != 0.0;
        if (isString())
            return !asString().empty();
        return true;
    }

    std::string Value::toString() const
    {
        if (isNull())
            return "null";
        if (isBool())
            return asBool() ? "true" : "false";
        if (isString())
            return asString();

        double n = asNumber();
        if (std::isfinite(n) && std::floor(n) == n)
        {
            std::ostringstream out;
            out << static_cast<long long>(n);
            return out.str();
        }

        std::ostringstream out;
        out << std::setprecision(15) << n;
        return out.str();
    }

    std::string Value::typeName() const
    {
        if (isNull())
            return "null";
        if (isNumber())
            return "number";
        if (isString())
            return "string";
        if (isBool())
            return "boolean";
        return "unknown";
    }

    bool operator==(const Value &a, const Value &b)
    {
        return a.storage_ == b.storage_;
    }

    bool operator!=(const Value &a, const Value &b)
    {
        return !(a == b);
    }

} // namespace peechi::runtime
