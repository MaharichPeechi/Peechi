#include "peechi/cli/Cli.hpp"

#include <string>
#include <vector>

int main(int argc, char **argv)
{
    std::vector<std::string> args;
    for (int i = 1; i < argc; ++i)
    {
        args.emplace_back(argv[i]);
    }

    peechi::cli::Cli cli;
    return cli.run(args);
}
