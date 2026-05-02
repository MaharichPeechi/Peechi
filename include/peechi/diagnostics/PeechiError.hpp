#pragma once

#include <exception>
#include <string>

namespace peechi::diagnostics
{

    class PeechiError : public std::exception
    {
    public:
        PeechiError(std::string phase, std::string message, int line = 0, int column = 0);

        const char *what() const noexcept override;

        const std::string &phase() const noexcept;
        const std::string &message() const noexcept;
        int line() const noexcept;
        int column() const noexcept;
        std::string format() const;

    private:
        std::string phase_;
        std::string message_;
        int line_;
        int column_;
        std::string cached_;
    };

} // namespace peechi::diagnostics
