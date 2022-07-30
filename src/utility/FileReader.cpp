#include "FileReader.h"

namespace File
{
    std::string assetPath = "";

    const std::vector<char> ReadFile(const std::string& filename) 
    {
        std::ifstream file(filename, std::ios::ate | std::ios::binary);

        if (!file.is_open()) 
        {
            printf("File[%s] could not be opened :(", filename.c_str());
            throw std::runtime_error("failed to open file!");
        }

        size_t fileSize = (size_t)file.tellg();
        std::vector<char> buffer(fileSize);

#ifdef ENABLE_VALIDATION_LAYERS
        printf("Size of file [%s]: %i\n", filename.c_str(), (int)fileSize);
#endif // ENABLE_VALIDATION_LAYERS

        file.seekg(0);
        file.read(buffer.data(), fileSize);
        file.close();
        return buffer;
    }

    const bool WriteFile(const std::string& filename, std::string text, bool clearFile)
    {
        std::ofstream file(filename, clearFile ? std::ios::trunc : std::ios::app | std::ios::out | std::ios::binary);

        if (!file.is_open())
        {
            printf("File[%s] could not be opened :(", filename.c_str());
            return false;
        }

        file << text.c_str();
        file.close();
        return true;
    }

    /// <summary>
    /// Add the location of the asset folder to a path
    /// </summary>
    /// <param name="path"> that is a child of the "Assets" folder</param>
    /// <returns>the input with the path to the "Assets" folder prepended</returns>
    const std::string AssetPath(std::string path)
    {
        if (!assetPath.empty())
        {
            return assetPath + path;
        }

        assetPath = "../bin/Assets/";
        return assetPath + path;
    }
}
