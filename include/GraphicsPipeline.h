#pragma once
#include "Vulkan.h"
#include <vector>
#include <stdexcept>

class GraphicsPipeline
{
public:
	GraphicsPipeline();
	~GraphicsPipeline();

	void CreateGraphicsPipeline();
	VkShaderModule CreateShaderModule(const std::vector<char>& code);
private:

};