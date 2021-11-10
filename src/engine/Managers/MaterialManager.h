#ifndef MATERIAL_MANAGER_H
#define MATERIAL_MANAGER_H

#include <vector>
#include <string>
#include "Material.h"

namespace MaterialManager
{
	void Init();
	void Destroy();

	void CreateNewMaterial(MaterialCreateDesc& createDesc);
	void RecreatePipelines();

	void DestroyPipelines();
	std::vector<Material*> GetMaterials();
}

#endif // !MATERIAL_MANAGER_H