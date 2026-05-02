#pragma once

#include <string>
#include <vector>

namespace peechi::cli
{

    class Cli
    {
    public:
        int run(const std::vector<std::string> &args);

    private:
        int runFile(const std::string &path);
        void printHelp() const;
        void printVersion() const;
    };

} // namespace peechi::cli
