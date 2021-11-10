#pragma once 
#include "Vulkan.h"
#include "Managers/VulkanManager.h"
#include "GraphicsPipeline.h"
#include <vector>
#include <string>

class Model;
struct MaterialCreateDesc
{
	std::string shaderName;
};
class Material : public GraphicsPipeline
{
public:

	Material(MaterialCreateDesc& createDesc);
	~Material();

	void RecreatePipeline();
	void DeletePipeline();
	void AddModel(Model* model) 
	{ 
		m_pModels.push_back(model); 
		VulkanManager::UpdateCommandBuffers();
	};

	std::vector<Model*> m_pModels;

private:
	MaterialCreateDesc m_createDesc;

	void CreatePipeline(MaterialCreateDesc& createDesc);
};