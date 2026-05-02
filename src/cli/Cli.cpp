#include "peechi/cli/Cli.hpp"
#include "peechi/core/SourceFile.hpp"
#include "peechi/core/Version.hpp"
#include "peechi/diagnostics/PeechiError.hpp"
#include "peechi/lexer/Lexer.hpp"
#include "peechi/parser/Parser.hpp"
#include "peechi/runtime/Interpreter.hpp"

#include <iostream>

namespace peechi::cli
{

    int Cli::run(const std::vector<std::string> &args)
    {
        if (args.empty() || args[0] == "--help" || args[0] == "-h")
        {
            printHelp();
            return 0;
        }

        if (args[0] == "--version" || args[0] == "-v")
        {
            printVersion();
            return 0;
        }

        return runFile(args[0]);
    }

    int Cli::runFile(const std::string &path)
    {
        try
        {
            std::string source = core::readFileToString(path);
            lexer::Lexer lexer(source);
            auto tokens = lexer.tokenize();

            parser::Parser parser(std::move(tokens));
            auto statements = parser.parse();

            runtime::Interpreter interpreter(std::cout);
            interpreter.interpret(statements);
            return 0;
        }
        catch (const diagnostics::PeechiError &error)
        {
            std::cerr << error.format() << '\n';
            return 1;
        }
        catch (const std::exception &error)
        {
            std::cerr << "Erro Peechi [interno]: " << error.what() << '\n';
            return 1;
        }
    }

    void Cli::printHelp() const
    {
        std::cout << peechi::PEECHI_NAME << " " << peechi::PEECHI_VERSION << "\n";
        std::cout << "Uso:\n";
        std::cout << "  peechi arquivo.pee\n";
        std::cout << "  peechi --version\n";
        std::cout << "  peechi --help\n";
    }

    void Cli::printVersion() const
    {
        std::cout << peechi::PEECHI_NAME << " " << peechi::PEECHI_VERSION << '\n';
    }

} // namespace peechi::cli
