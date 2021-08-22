#pragma once

#include "Vulkan.h"
#include <stdexcept>
#include <vector>

class VulkanManager;

class BufferManager
{
public:
	BufferManager(VulkanManager* pVulkanManager);
	~BufferManager();

	void CleanupUniformBuffers(size_t swapChainImagesSize);

	void CreateDescriptorSetLayout();
	void CreateBuffers();
	void CreateUniformBuffers();
	void UpdateUniformBuffer(uint32_t currentImage, float DeltaTime);
	void CreateDescriptorPool();
	void CreateDescriptorSets();

	VkDescriptorSetLayout m_descriptorSetLayout;
	VkDescriptorPool m_descriptorPool;
	std::vector<VkDescriptorSet> m_descriptorSets;

	VkBuffer m_vertexBuffer;
	VkDeviceMemory m_vertexBufferMemory;
	VkBuffer m_indexBuffer;
	VkDeviceMemory m_indexBufferMemory;

	std::vector<VkBuffer> m_uniformBuffers;
	std::vector<VkDeviceMemory> m_uniformBuffersMemory;
private:
	void CreateVertexBuffer();
	void CreateIndexBuffer();
	void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);


	VulkanManager* m_pVulkanManager;


	struct UniformBufferObject {
		alignas(16) glm::mat4 model;
		alignas(16) glm::mat4 view;
		alignas(16) glm::mat4 proj;
	};

	float m_rotation = 0.0f;
};