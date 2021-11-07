
#include "Managers/MaterialManager.h"
#include "Managers/VulkanManager.h"
#include "Material.h"

MaterialManager::MaterialManager()
{

}

MaterialManager::~MaterialManager()
{

}

void MaterialManager::CreateNewMaterial(MaterialCreateDesc& createDesc)
{
	Material* newMaterial = new Material(createDesc);

	 m_pMaterials.push_back(newMaterial);
}

void MaterialManager::RecreatePipelines()
{
	for(Material* mat : m_pMaterials)
	{
		mat->RecreatePipeline();
	}
}

void MaterialManager::DestroyPipelines()
{
	for (Material* mat : m_pMaterials)
	{
		vkDestroyPipeline(VulkanManager::Instance().m_device, mat->GetPipeline(), nullptr);
	}
}