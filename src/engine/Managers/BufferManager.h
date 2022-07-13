#pragma once

#include "Core.h"

#ifdef VULKAN

#include <vector>

class BufferManager
{
public:
	BufferManager();
	~BufferManager();

	void CreateDescriptorSetLayout();

	void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

	VkDescriptorSetLayout m_descriptorSetLayout;

private:

};
#endif // VULKAN