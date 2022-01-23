#ifndef VULKAN_MANAGER_H
#define VULKAN_MANAGER_H

#include "Core.h"

#ifdef VULKAN

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <array>
#include <map>
#include <optional>
#include <set>
#include <fstream>

class BufferManager;
class TextureManager;
class Engine;
class GraphicsPipeline;

const std::string MODEL_ROOM_PATH = "../bin/Assets/Models/viking_room.obj";
//const std::string TEXTURE_PATH = "../bin/Assets/Textures/viking_room.png";
const std::string TEXTURE_PATH = "../bin/Assets/Textures/DefaultTex.png";

const std::string MODEL_CUBE_OBJ_PATH = "../bin/Assets/Models/Primitives/Cube.obj";
const std::string MODEL_CUBE_FBX_PATH = "../bin/Assets/Models/Primitives/Cube.fbx";
const std::string MODEL_ICOSPHERE_FBX_PATH = "../bin/Assets/Models/Primitives/Icosphere.fbx";
const std::string TEXTURE_CUBE_PATH = "../bin/Assets/Textures/Texture.png";

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value();
    }
};
struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

namespace VulkanManager
{
    void Init();
    void Destroy();

    void Cleanup();
    void DrawFrame(float DeltaTime);

    void CreateInstance();
    void SetupDebugMessenger();
    void CreateSurface();

    void CreateRenderPass();

    void CreateFramebuffers();
    void CreateCommandPool();
    void CreateCommandBuffers();
    void UpdateCommandBuffers();

    VkCommandBuffer BeginSingleTimeCommands();
    void EndSingleTimeCommands(VkCommandBuffer commandBuffer);
    void CreateSyncObjects();
    void CreateLogicalDevice();
    void CreateImageViews();
    VkImageView CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);

    void CleanupSwapChain();
    void CreateSwapChain();
    void RecreateSwapChain();


    void PickPhysicalDevice();
    VkSampleCountFlagBits GetMaxUsableSampleCount();
    bool IsDeviceSuitable(VkPhysicalDevice device);
    bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
    int RateDeviceSuitability(VkPhysicalDevice device);
    QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
    SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    std::vector<const char*> GetRequiredExtensions();
    uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

    //Get
    VkDevice* GetDevice();
    VkExtent2D* GetSwapChainExtent();
    std::vector<VkImage> GetSwapChainImages();
    VkFormat* GetSwapChainImageFormat();
    VkCommandPool* GetCommandPool();
    BufferManager* GetBufferManager();
    TextureManager* GetTextureManager();
    VkPipelineLayout* GetPipelineLayout();
    VkPhysicalDevice* GetPhysicalDevice();
    VkRenderPass* GetRenderPass();
    VkSampleCountFlagBits* GetMSAASamples();
    //Set
    void SetFrameBufferResized(bool state);

}
#endif // VULKAN

#endif // !VULKAN_MANAGER_H