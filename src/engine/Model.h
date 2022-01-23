#pragma once

#include "Core.h"

#include <vector>
#include <string>

#include "Transform.h"
#include "Vertex.h"
#include "Material.h"

class BufferManager;

class Model : public Transform
{
public:
	Model(std::string path);
	~Model();

	void Render();
	void Update(float DeltaTime, int imageIndex);

#ifdef VULKAN
	void CreateVertexBuffer();
	void CreateIndexBuffer();

	void CreateUniformBuffers();
	void UpdateUniformBuffer(uint32_t currentImage, float DeltaTime);
	void CleanupUniformBuffers(size_t swapChainImagesSize);

	void CreateDescriptorPool();
	void CreateDescriptorSets();

	VkBuffer m_vertexBuffer;
	VkDeviceMemory m_vertexBufferMemory;
	VkBuffer m_indexBuffer;
	VkDeviceMemory m_indexBufferMemory;

	std::vector<VkBuffer> m_uniformBuffers;
	std::vector<VkDeviceMemory> m_uniformBuffersMemory;

	VkDescriptorSetLayout m_descriptorSetLayout;
	VkDescriptorPool m_descriptorPool;
	std::vector<VkDescriptorSet> m_descriptorSets;

	VkCommandPool m_commandPool;
	std::vector<VkCommandBuffer> m_commandBuffers;
#endif // VULKAN

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
private:

	BufferManager* m_pBufferManager;

	struct UniformBufferObject {
		alignas(16) glm::mat4 model;
		alignas(16) glm::mat4 view;
		alignas(16) glm::mat4 proj;
	};

	//Material& m_material;
};