#include "peechi/diagnostics/PeechiError.hpp"

#include <sstream>
#include <utility>

namespace peechi::diagnostics
{

    PeechiError::PeechiError(std::string phase, std::string message, int line, int column)
        : phase_(std::move(phase)), message_(std::move(message)), line_(line), column_(column)
    {
        cached_ = format();
    }

    const char *PeechiError::what() const noexcept
    {
        return cached_.c_str();
    }

    const std::string &PeechiError::phase() const noexcept
    {
        return phase_;
    }

    const std::string &PeechiError::message() const noexcept
    {
        return message_;
    }

    int PeechiError::line() const noexcept
    {
        return line_;
    }

    int PeechiError::column() const noexcept
    {
        return column_;
    }

    std::string PeechiError::format() const
    {
        std::ostringstream out;
        out << "Erro Peechi [" << phase_ << "]: " << message_;
        if (line_ > 0)
        {
            out << "\nLinha: " << line_;
            if (column_ > 0)
            {
                out << ", coluna: " << column_;
            }
        }
        return out.str();
    }

} // namespace peechi::diagnostics
