#include "ShaderDataLoader.h"

#include "Core.h"
#include <string>
#include <iostream>
#include <filesystem>
#include "FileReader.h"

ShaderDataLoader::ShaderDataLoader()
{
    data = FindAllShaders();
}

ShaderDataLoader::~ShaderDataLoader()
{
    delete data;
}

void ShaderDataLoader::Update()
{
    for (auto pair = data->begin(); pair != data->end(); ++pair)
    {
        auto json = pair->second;
        ImGui::Begin(pair->first.c_str());
        
        ImGui::End();
    }
}

std::map<std::string, json*>* ShaderDataLoader::FindAllShaders()
{
    auto path = File::AssetPath("ShaderData");
    auto shaders = new std::map<std::string, json*>();
    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        auto name = entry.path().filename().string();
        auto shaderDataPath = "ShaderData/" + entry.path().filename().string();
        auto read = File::ReadFile(File::AssetPath(shaderDataPath));
        auto j = json::parse(read);
        shaders->insert(std::pair(name, &j));
    }
    return shaders;
}