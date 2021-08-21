#pragma once

#include "Vulkan.h"
#include <stdexcept>

class VulkanManager;

class BufferManager
{
public:
	BufferManager(VulkanManager* pVulkanManager);
	~BufferManager();

	void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	void CreateVertexBuffer();
	void CreateIndexBuffer();

	VkBuffer m_vertexBuffer;
	VkDeviceMemory m_vertexBufferMemory;
	VkBuffer m_indexBuffer;
	VkDeviceMemory m_indexBufferMemory;
private:
	VulkanManager* m_pVulkanManager;

};