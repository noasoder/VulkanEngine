#pragma once

#include <vector>
#include <string>
#include <ios>
#include <fstream>

namespace File
{
    const std::vector<char> ReadFile(const std::string& filename);
    const bool WriteFile(const std::string& filename, std::string text, bool clearFile);
    const std::string AssetPath(std::string);
}
