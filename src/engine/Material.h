#pragma once 
#include "Core.h"
#include "Managers/VulkanManager.h"
#include "Shader.h"
#include <vector>
#include <string>

class Model;
struct MaterialCreateDesc
{
	std::string shaderName;
};
class Material : public Shader
{
public:

	Material(MaterialCreateDesc& createDesc);
	~Material();

	void RecreatePipeline();
	void DeletePipeline();
	void AddModel(Model* model) 
	{ 
		m_pModels.push_back(model);
#ifdef VULKAN
		VulkanManager::UpdateCommandBuffers();
#endif // VULKAN
	};

	std::vector<Model*> m_pModels;

private:
	MaterialCreateDesc m_createDesc;

	void CreatePipeline(MaterialCreateDesc& createDesc);
};