#include "Vulkan.h"
#include "Model.h"
#include <vector>

class Material
{
public:
	Material();
	~Material();

	VkPipeline GetPipeline() { return m_pGraphicsPipeline; };
	void AddModel(Model* model) { m_pModels.push_back(model); };

	std::vector<Model*> m_pModels;

private:
	VkPipeline m_pGraphicsPipeline;
};