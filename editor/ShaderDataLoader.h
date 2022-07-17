#pragma once

#include "json.hpp"
#include "imgui.h"

class ShaderDataLoader
{
public:
	ShaderDataLoader();
	~ShaderDataLoader();

	void Update();

private:
	std::map<std::string, nlohmann::json>* FindAllShaders();
	std::map<std::string, nlohmann::json>* data = nullptr;
};

