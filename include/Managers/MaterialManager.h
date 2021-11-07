#pragma once
#include "Utility/Singleton.h"
#include <vector>
#include <string>
#include "Material.h"

class MaterialManager : public Singleton<MaterialManager>
{
public:

	MaterialManager();
	~MaterialManager();

	void CreateNewMaterial(MaterialCreateDesc& createDesc);
	void RecreatePipelines();

	void DestroyPipelines();

	std::vector<Material*> m_pMaterials;

private:
};