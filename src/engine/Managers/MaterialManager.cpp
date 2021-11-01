
#include "Managers/MaterialManager.h"
#include "GraphicsPipeline.h"
#include "Material.h"

MaterialManager::MaterialManager()
{
	m_pGraphicsPipeline = new GraphicsPipeline();
}

MaterialManager::~MaterialManager()
{
	delete m_pGraphicsPipeline;
}

void MaterialManager::CreateNewMaterial(Material::MaterialCreateDesc& createDesc)
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