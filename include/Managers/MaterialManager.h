#pragma once
#include "Material.h"
#include "Utility/Singleton.h"
#include <vector>

class MaterialManager : public Singleton<MaterialManager>
{
public:
	MaterialManager();
	~MaterialManager();

	void CreateNewMaterial() {};

	std::vector<Material*> m_pMaterials;
private:
};