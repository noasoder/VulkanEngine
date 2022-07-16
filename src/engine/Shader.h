#pragma once

#include "Core.h"
#include <vector>
#include <stdexcept>
#include <string>

struct ShaderCreateDesc
{
	std::string vertexShaderPath;
	std::string fragmentShaderPath;
};

struct ShaderData
{
	ShaderData();
};

class Shader
{
public:

	Shader();
	~Shader();

	void CreateShader(std::string shaderDataName);

#ifdef VULKAN
	static VkShaderModule CreateShaderModule(const std::vector<char>& code);

	VkPipeline GetPipeline() { return m_Shader; };
	
private:
	VkPipeline m_Shader;
#endif // VULKAN
};