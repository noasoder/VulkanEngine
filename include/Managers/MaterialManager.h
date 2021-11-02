#pragma once
#include "Utility/Singleton.h"
#include <vector>
#include <string>
#include "Material.h"

class GraphicsPipeline;

class MaterialManager : public Singleton<MaterialManager>
{
public:

	MaterialManager();
	~MaterialManager();

	void CreateNewMaterial(MaterialCreateDesc& createDesc);
	void RecreatePipelines();

	std::vector<Material*> m_pMaterials;

	GraphicsPipeline* m_pGraphicsPipeline;

private:
};