#include "Vulkan.h"
#include <vector>
#include <string>

class Model;
class Material
{
public:
	struct MaterialCreateDesc
	{
		std::string shaderName;
	};

	Material(MaterialCreateDesc& createDesc);
	~Material();

	VkPipeline* GetPipeline() { return m_pGraphicsPipeline; };
	void RecreatePipeline();
	void AddModel(Model* model) { m_pModels.push_back(model); };

	std::vector<Model*> m_pModels;
private:
	VkPipeline* m_pGraphicsPipeline;
	MaterialCreateDesc m_createDesc;

	void CreatePipeline(MaterialCreateDesc& createDesc);
};