#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <filesystem>
#include "json.hpp"
#include "imgui.h"
#include "vulkan/vulkan.h"

class ShaderDataLoader
{
public:
	ShaderDataLoader();
	~ShaderDataLoader();

	void Update();

private:

	struct ShaderData {
		nlohmann::ordered_json json;
		int vkPolygonMode;
		int vkCullModeFlagBits;
        float lineWidth;

		ShaderData(nlohmann::ordered_json data);
	};

	static void SaveShaderData(std::string name, nlohmann::ordered_json j);
	static std::string ShaderDataFolder(std::string fileName);

	std::map<std::string, ShaderData>* FindAllShaders();
	std::map<std::string, ShaderData>* data = nullptr;

    template <typename EnumType>
    void ShaderDataEntryCombo(nlohmann::ordered_json& j, int& storedEntryValue, const char* fileName, const char* entryName, const char* enumStrings[], std::vector<EnumType> allEnumValues)
    {
        if (ImGui::BeginCombo(entryName, enumStrings[storedEntryValue]))
        {
            for (auto e : allEnumValues)
            {
                bool isSelected = (storedEntryValue == e);
                if (ImGui::Selectable(enumStrings[e], isSelected))
                {
                    printf("Selected: %s\n", enumStrings[e]);
                    storedEntryValue = e;
                    nlohmann::ordered_json newValue = {
                        {entryName, storedEntryValue}
                    };
                    j.update(newValue, false);
                    ShaderDataLoader::SaveShaderData(fileName, j);
                }
                if (isSelected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }
    }

    void ShaderDataEntryFloat(nlohmann::ordered_json& j, float& storedEntryValue, const char* fileName, const char* entryName)
    {

    }

    void UpdateAndSaveJson(nlohmann::ordered_json& j, float& storedEntryValue, const char* fileName, const char* entryName)
    {
        nlohmann::ordered_json newValue = {
            {entryName, storedEntryValue}
        };
        j.update(newValue, false);
        ShaderDataLoader::SaveShaderData(fileName, j);
    }
};

