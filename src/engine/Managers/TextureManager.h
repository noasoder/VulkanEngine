#pragma once

#include "Core.h"

#ifdef VULKAN

#include <vector>

class BufferManager;

class TextureManager
{
public :
	TextureManager(BufferManager* pBufferManager);
	~TextureManager();

	void CreateDepthResources();
	void CreateColorResources();
	VkFormat FindDepthFormat();
	VkFormat FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
	bool HasStencilComponent(VkFormat format) {
		return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;
	}

	void CreateTextureImage();
	void CreateTextureImageView();
	void CreateTextureSampler();
	void CreateImage(uint32_t width, uint32_t height, VkSampleCountFlagBits samples, VkFormat format, VkImageTiling tiling,
					VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
	
	void TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);

	void CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

	VkImage m_depthImage;
	VkDeviceMemory m_depthImageMemory;

	VkImageView m_textureImageView;
	VkImageView m_depthImageView;

	VkImage colorImage;
	VkDeviceMemory colorImageMemory;
	VkImageView colorImageView;

	VkSampler m_textureSampler;

private:
	BufferManager* m_pBufferManager;

	VkImage m_textureImage;
	VkDeviceMemory m_textureImageMemory;
};

#endif // VULKAN