#pragma once

#include <vector>
#include <string>

#include "Transform.h"
#include "Utility/Vertex.h"

class VulkanManager;
class BufferManager;
class Application;
class ModelManager;

class Model : public Transform
{
public:
	Model(Application* pApplication, std::string path);
	~Model();

	void Render();

	void CreateVertexBuffer();
	void CreateIndexBuffer();

	void CreateUniformBuffers();
	void UpdateUniformBuffer(uint32_t currentImage, float DeltaTime);
	void CleanupUniformBuffers(size_t swapChainImagesSize);

	void CreateDescriptorSets();

	void CreateCommandBuffers();

	VkBuffer m_vertexBuffer;
	VkDeviceMemory m_vertexBufferMemory;
	VkBuffer m_indexBuffer;
	VkDeviceMemory m_indexBufferMemory;

	std::vector<VkBuffer> m_uniformBuffers;
	std::vector<VkDeviceMemory> m_uniformBuffersMemory;

	VkDescriptorSetLayout m_descriptorSetLayout;
	VkDescriptorPool m_descriptorPool;
	std::vector<VkDescriptorSet> m_descriptorSets;

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	VkCommandPool m_commandPool;
	std::vector<VkCommandBuffer> m_commandBuffers;
private:

	Application* m_pApplication;
	VulkanManager* m_pVulkanManager;
	BufferManager* m_pBufferManager;
	ModelManager* m_pModelManager;


	struct UniformBufferObject {
		alignas(16) glm::mat4 model;
		alignas(16) glm::mat4 view;
		alignas(16) glm::mat4 proj;
	};
};