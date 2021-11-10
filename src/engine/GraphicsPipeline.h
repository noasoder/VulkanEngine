#pragma once
#include "Vulkan.h"
#include <vector>
#include <stdexcept>
#include <string>

class GraphicsPipeline
{
public:
	struct PipelineCreateDesc
	{
		std::string vertexShaderPath;
		std::string fragmentShaderPath;
	};

	GraphicsPipeline();
	~GraphicsPipeline();

	void CreateGraphicsPipeline(PipelineCreateDesc& pipelineCreateDesc);
	VkShaderModule CreateShaderModule(const std::vector<char>& code);

	VkPipeline GetPipeline() { return m_graphicsPipeline; };
	
private:
	VkPipeline m_graphicsPipeline;
};