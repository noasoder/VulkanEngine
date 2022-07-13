
#include "Managers/MaterialManager.h"
#include "Managers/VulkanManager.h"
#include "Material.h"

std::vector<Material*> m_pMaterials;

namespace MaterialManager 
{
	void Init()
	{
	
	}
	
	void Destroy()
	{
	
	}
	
	void CreateNewMaterial(MaterialCreateDesc& createDesc)
	{
		Material* newMaterial = new Material(createDesc);
	
		 m_pMaterials.push_back(newMaterial);
	}
	
	void RecreatePipelines()
	{
		for(Material* mat : m_pMaterials)
		{
			mat->RecreatePipeline();
		}
	}
	
	void DestroyPipelines()
	{
		for (Material* mat : m_pMaterials)
		{
			//vkDestroyPipeline(*VulkanManager::GetDevice(), mat->GetPipeline(), nullptr);
		}
	}
	
	std::vector<Material*> GetMaterials()
	{
		return m_pMaterials;
	}
}