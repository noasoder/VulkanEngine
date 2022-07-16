#pragma once

#include <vector>
#include <string>
#include <ios>
#include <fstream>

namespace File
{
    const std::vector<char> ReadFile(const std::string& filename);
    const std::string AssetPath(std::string);
}
