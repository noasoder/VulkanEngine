#pragma once
#include "Utility/Singleton.h"
#include <vector>
#include <string>

class GraphicsPipeline;
class Material;

class MaterialManager : public Singleton<MaterialManager>
{
public:

	MaterialManager();
	~MaterialManager();

	void CreateNewMaterial(Material::MaterialCreateDesc& createDesc);
	void RecreatePipelines();

	std::vector<Material*> m_pMaterials;

	GraphicsPipeline* m_pGraphicsPipeline;

private:
};