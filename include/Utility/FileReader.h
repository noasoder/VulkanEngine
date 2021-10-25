#pragma once
#include "Vulkan.h"
#include <vector>
#include <string>
#include <ios>
#include <fstream>

namespace File
{
    const std::vector<char> ReadFile(const std::string& filename) {
        std::ifstream file(filename, std::ios::ate | std::ios::binary);

        if (!file.is_open()) {
            //std::cout << "File[" << filename << "] could not be opened :(" << std::endl;
            printf("File[%s] could not be opened :(", filename.c_str());
            throw std::runtime_error("failed to open file!");
        }

        size_t fileSize = (size_t)file.tellg();
        std::vector<char> buffer(fileSize);

        if (ENABLE_VALIDATION_LAYERS) {
            //std::cout << "Size of file [" << filename << "]: " << fileSize << "" << std::endl;
            printf("Size of file [%s]: %i", filename.c_str(), (int)fileSize);
        }

        file.seekg(0);
        file.read(buffer.data(), fileSize);
        file.close();
        return buffer;
    }
}
