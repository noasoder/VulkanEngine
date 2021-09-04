#pragma once

#include "Vulkan.h"

#include <vector>

class Application;
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

	Application* m_pApplication;
	VulkanManager* m_pVulkanManager;
};