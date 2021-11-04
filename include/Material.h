#pragma once 
#include "Vulkan.h"
#include "Managers/VulkanManager.h"
#include <vector>
#include <string>

class Model;
struct MaterialCreateDesc
{
	std::string shaderName;
};
class Material
{
public:

	Material(MaterialCreateDesc& createDesc);
	~Material();

	VkPipeline GetPipeline() { return m_graphicsPipeline; };
	void RecreatePipeline();
	void DeletePipeline();
	void AddModel(Model* model) 
	{ 
		m_pModels.push_back(model); 
		VulkanManager::Instance().UpdateCommandBuffers();
	};

	std::vector<Model*> m_pModels;
	VkPipeline m_graphicsPipeline;

private:
	MaterialCreateDesc m_createDesc;

	void CreatePipeline(MaterialCreateDesc& createDesc);
};