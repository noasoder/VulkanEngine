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

class Shader
{
public:

	Shader();
	~Shader();

	void CreateShader(ShaderCreateDesc& ShaderCreateDesc);

#ifdef VULKAN
	VkShaderModule CreateShaderModule(const std::vector<char>& code);

	VkPipeline GetPipeline() { return m_Shader; };
	
private:
	VkPipeline m_Shader;
#endif // VULKAN
};