#include "peechi/core/SourceFile.hpp"
#include "peechi/diagnostics/PeechiError.hpp"

#include <fstream>
#include <sstream>

namespace peechi::core
{

    std::string readFileToString(const std::string &path)
    {
        std::ifstream file(path, std::ios::in | std::ios::binary);
        if (!file)
        {
            throw diagnostics::PeechiError("arquivo", "não foi possível abrir o arquivo: " + path);
        }

        std::ostringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

} // namespace peechi::core
