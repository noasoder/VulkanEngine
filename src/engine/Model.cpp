#include "Model.h"

#include "Managers/BufferManager.h"
#include "Managers/VulkanManager.h"
#include "Managers/ModelManager.h"
#include "Managers/CameraManager.h"
#include "Managers/TextureManager.h"
#include "Utility/Maths.h"
#include "Camera/Camera.h"
#include "Engine.h"

Model::Model(std::string path)
: m_pVulkanManager(&VulkanManager::Instance())
, m_pBufferManager(m_pVulkanManager->m_pBufferManager)
{
    ModelManager::Instance().LoadModel(path, vertices, indices);


    CreateVertexBuffer();
    CreateIndexBuffer();
    CreateUniformBuffers();
    CreateDescriptorPool();
    CreateDescriptorSets();
}

Model::~Model()
{
    VkDevice* pDevice = &m_pVulkanManager->m_device;

    vkDestroyBuffer(*pDevice, m_indexBuffer, nullptr);
    vkFreeMemory(*pDevice, m_indexBufferMemory, nullptr);
    vkDestroyBuffer(*pDevice, m_vertexBuffer, nullptr);
    vkFreeMemory(*pDevice, m_vertexBufferMemory, nullptr);
}

void Model::Render()
{

}

void Model::Update(float DeltaTime, int imageIndex)
{
    UpdateUniformBuffer(imageIndex, DeltaTime);
}

void Model::CreateVertexBuffer()
{
    VkDevice* pDevice = &m_pVulkanManager->m_device;
    ModelManager* pModelManager = &ModelManager::Instance();

    VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    m_pBufferManager->CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(*pDevice, stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, vertices.data(), (size_t)bufferSize);
    vkUnmapMemory(*pDevice, stagingBufferMemory);

    m_pBufferManager->CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_vertexBuffer, m_vertexBufferMemory);
    m_pBufferManager->CopyBuffer(stagingBuffer, m_vertexBuffer, bufferSize);

    vkDestroyBuffer(*pDevice, stagingBuffer, nullptr);
    vkFreeMemory(*pDevice, stagingBufferMemory, nullptr);
}

void Model::CreateIndexBuffer()
{
    VkDevice* pDevice = &m_pVulkanManager->m_device;

    VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    m_pBufferManager->CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(*pDevice, stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, indices.data(), (size_t)bufferSize);
    vkUnmapMemory(*pDevice, stagingBufferMemory);

    m_pBufferManager->CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_indexBuffer, m_indexBufferMemory);
    m_pBufferManager->CopyBuffer(stagingBuffer, m_indexBuffer, bufferSize);

    vkDestroyBuffer(*pDevice, stagingBuffer, nullptr);
    vkFreeMemory(*pDevice, stagingBufferMemory, nullptr);
}

void Model::CreateUniformBuffers()
{
    VkDevice* pDevice = &m_pVulkanManager->m_device;
    size_t swapChainImagesSize = m_pVulkanManager->m_swapChainImages.size();

    VkDeviceSize bufferSize = sizeof(UniformBufferObject);

    m_uniformBuffers.resize(swapChainImagesSize);
    m_uniformBuffersMemory.resize(swapChainImagesSize);

    for (size_t i = 0; i < swapChainImagesSize; i++) {
        m_pBufferManager->CreateBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_uniformBuffers[i], m_uniformBuffersMemory[i]);
    }
}

void Model::UpdateUniformBuffer(uint32_t currentImage, float DeltaTime)
{
    VkDevice* pDevice = &m_pVulkanManager->m_device;
    VkExtent2D* swapChainExtent = &m_pVulkanManager->m_swapChainExtent;
    Camera* pCamera = CameraManager::Instance().GetCurrentCamera();

    pCamera->UpdateAspect(swapChainExtent->width / (float)swapChainExtent->height);

    UniformBufferObject ubo{};
    ubo.model = GetMatrix();

    ubo.view = pCamera->GetView();
    ubo.proj = pCamera->GetProj();
    ubo.proj[1][1] *= -1;


    void* data;
    vkMapMemory(*pDevice, m_uniformBuffersMemory[currentImage], 0, sizeof(ubo), 0, &data);
    memcpy(data, &ubo, sizeof(ubo));
    vkUnmapMemory(*pDevice, m_uniformBuffersMemory[currentImage]);
}

void Model::CleanupUniformBuffers(size_t swapChainImagesSize)
{
    VkDevice* pDevice = &m_pVulkanManager->m_device;

    for (size_t i = 0; i < swapChainImagesSize; i++) {
        vkDestroyBuffer(*pDevice, m_uniformBuffers[i], nullptr);
        vkFreeMemory(*pDevice, m_uniformBuffersMemory[i], nullptr);
    }

    vkDestroyDescriptorPool(*pDevice, m_descriptorPool, nullptr);
}

void Model::CreateDescriptorPool() 
{
    VkDevice* pDevice = &m_pVulkanManager->m_device;
    size_t swapChainImagesSize = m_pVulkanManager->m_swapChainImages.size();

    std::array<VkDescriptorPoolSize, 2> poolSizes{};
    poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    poolSizes[0].descriptorCount = static_cast<uint32_t>(swapChainImagesSize);
    poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    poolSizes[1].descriptorCount = static_cast<uint32_t>(swapChainImagesSize);

    VkDescriptorPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
    poolInfo.pPoolSizes = poolSizes.data();
    poolInfo.maxSets = static_cast<uint32_t>(swapChainImagesSize);

    if (vkCreateDescriptorPool(*pDevice, &poolInfo, nullptr, &m_descriptorPool) != VK_SUCCESS) {
        throw std::runtime_error("failed to create descriptor pool!");
    }
}

void Model::CreateDescriptorSets()
{
    VkDevice* pDevice = &m_pVulkanManager->m_device;
    TextureManager* pTextureManager = m_pVulkanManager->m_pTextureManager;
    size_t swapChainImagesSize = m_pVulkanManager->m_swapChainImages.size();

    std::vector<VkDescriptorSetLayout> layouts(swapChainImagesSize, m_pBufferManager->m_descriptorSetLayout);
    VkDescriptorSetAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = m_descriptorPool;
    allocInfo.descriptorSetCount = static_cast<uint32_t>(swapChainImagesSize);
    allocInfo.pSetLayouts = layouts.data();

    m_descriptorSets.resize(swapChainImagesSize);
    if (vkAllocateDescriptorSets(*pDevice, &allocInfo, m_descriptorSets.data()) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate descriptor sets!");
    }

    for (size_t i = 0; i < swapChainImagesSize; i++) {
        VkDescriptorBufferInfo bufferInfo{};
        bufferInfo.buffer = m_uniformBuffers[i];
        bufferInfo.offset = 0;
        bufferInfo.range = sizeof(UniformBufferObject);

        VkDescriptorImageInfo imageInfo{};
        imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        imageInfo.imageView = pTextureManager->m_textureImageView;
        imageInfo.sampler = pTextureManager->m_textureSampler;

        std::array<VkWriteDescriptorSet, 2> descriptorWrites{};

        descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites[0].dstSet = m_descriptorSets[i];
        descriptorWrites[0].dstBinding = 0;
        descriptorWrites[0].dstArrayElement = 0;
        descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorWrites[0].descriptorCount = 1;
        descriptorWrites[0].pBufferInfo = &bufferInfo;

        descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites[1].dstSet = m_descriptorSets[i];
        descriptorWrites[1].dstBinding = 1;
        descriptorWrites[1].dstArrayElement = 0;
        descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        descriptorWrites[1].descriptorCount = 1;
        descriptorWrites[1].pImageInfo = &imageInfo;

        vkUpdateDescriptorSets(*pDevice, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
    }
}