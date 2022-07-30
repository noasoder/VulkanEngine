#include "ShaderDataLoader.h"

#include "Core.h"
#include <string>
#include <iostream>
#include <filesystem>
#include "FileReader.h"
#include "EnumNames.h"

ShaderDataLoader::ShaderData::ShaderData(nlohmann::ordered_json data)
{
    json = data;
    vkPolygonMode = data.value("VkPolygonMode", 0);
    vkCullModeFlagBits = data.value("VkCullModeFlagBits", 2);
    lineWidth = data.value("LineWidth", 1.0f);
}

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
    ImGui::Begin("Shaders", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    
    for (auto pair = data->begin(); pair != data->end(); ++pair)
    {
        int* currentEntry = &pair->second.vkPolygonMode;
        nlohmann::ordered_json& j = pair->second.json;
        auto name = pair->first.c_str();
        
        if (ImGui::TreeNodeEx(name))
        {
            ImGui::Indent();
            auto shaderName = j.value("Name", "shader");
            ImGui::Text("Name: %s", shaderName.c_str());

            ShaderDataEntryCombo<VkCullModeFlagBits>(j, pair->second.vkCullModeFlagBits, name, STRF(VkCullModeFlagBits), VkCullModeFlagBits_Str, VkCullModeFlagBits_All);
            ShaderDataEntryCombo<VkPolygonMode>(j, pair->second.vkPolygonMode, name, STRF(VkPolygonMode), VkPolygonMode_Str, VkPolygonMode_All);

            if (ImGui::DragFloat("LineWidth", &pair->second.lineWidth, 0.1f, 0.0f, 10.0f))
            {
                UpdateAndSaveJson(j, pair->second.lineWidth, name, "LineWidth");
            }

            ImGui::Unindent();
            ImGui::TreePop();
        }
    }
    ImGui::End();
}

std::map<std::string, ShaderDataLoader::ShaderData>* ShaderDataLoader::FindAllShaders()
{
    auto path = File::AssetPath("ShaderData");
    auto shaders = new std::map<std::string, ShaderData>();
    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        auto name = entry.path().filename().string();
        auto read = File::ReadFile(ShaderDataFolder(name));
        auto j = json::parse(read);
        shaders->insert(std::pair(name, ShaderData(j)));
    }
    return shaders;
}

std::string ShaderDataLoader::ShaderDataFolder(std::string fileName)
{
    return File::AssetPath("ShaderData/" + fileName);
}

void ShaderDataLoader::SaveShaderData(std::string name, nlohmann::ordered_json j)
{
    File::WriteFile(ShaderDataFolder(name), j.dump(1, 0x09), true);
}