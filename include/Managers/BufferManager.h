#pragma once

#include "Vulkan.h"

#include <vector>

class Engine;
class VulkanManager;

class BufferManager
{
public:
	BufferManager(VulkanManager* pVulkanManager);
	~BufferManager();

	void CreateDescriptorSetLayout();

	void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

	VkDescriptorSetLayout m_descriptorSetLayout;

private:

	Engine* m_pEngine;
	VulkanManager* m_pVulkanManager;
};