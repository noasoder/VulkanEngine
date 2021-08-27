#include "Model.h"

#include "Managers/BufferManager.h"
#include "Managers/VulkanManager.h"
#include "Managers/ModelManager.h"
#include "Managers/CameraManager.h"
#include "Managers/TextureManager.h"
#include "Utility/Maths.h"
#include "Camera/Camera.h"
#include "Application.h"

Model::Model(Application* pApplication, std::string path)
: m_pVulkanManager(pApplication->m_pVulkanManager)
, m_pApplication(pApplication->m_pVulkanManager->m_pApplication)
, m_pBufferManager(pApplication->m_pVulkanManager->m_pBufferManager)
, m_pModelManager(pApplication->m_pVulkanManager->m_pModelManager)
{
    m_pModelManager->LoadModel(path, vertices, indices);

    CreateDescriptorSets();
}

Model::~Model()
{
    VkDevice* pDevice = &m_pVulkanManager->m_device;

    vkDestroyDescriptorSetLayout(*pDevice, m_pBufferManager->m_descriptorSetLayout, nullptr);

    vkDestroyBuffer(*pDevice, m_indexBuffer, nullptr);
    vkFreeMemory(*pDevice, m_indexBufferMemory, nullptr);
    vkDestroyBuffer(*pDevice, m_vertexBuffer, nullptr);
    vkFreeMemory(*pDevice, m_vertexBufferMemory, nullptr);
}

void Model::Render()
{

}

void Model::CreateVertexBuffer()
{
    VkDevice* pDevice = &m_pVulkanManager->m_device;
    ModelManager* pModelManager = m_pVulkanManager->m_pModelManager;

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
    Camera* pCamera = m_pApplication->m_pCameraManager->GetCurrentCamera();

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

void Model::CreateCommandBuffers() {
    m_commandBuffers.resize(m_pVulkanManager->m_swapChainFramebuffers.size());

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = m_commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = (uint32_t)m_commandBuffers.size();

    if (vkAllocateCommandBuffers(m_pVulkanManager->m_device, &allocInfo, m_commandBuffers.data()) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate command buffers");
    }

    for (size_t i = 0; i < m_commandBuffers.size(); i++)
    {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = 0;
        beginInfo.pInheritanceInfo = nullptr;

        if (vkBeginCommandBuffer(m_commandBuffers[i], &beginInfo) != VK_SUCCESS) {
            throw std::runtime_error("failed to begin recording command buffer!");
        }

        std::array<VkClearValue, 2> clearValues{};
        clearValues[0].color = { {0.0f, 0.0f, 0.0f, 1.0f} };
        clearValues[1].depthStencil = { 1.0f, 0 };

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = m_pVulkanManager->m_renderPass;
        renderPassInfo.framebuffer = m_pVulkanManager->m_swapChainFramebuffers[i];
        renderPassInfo.renderArea.offset = { 0, 0 };
        renderPassInfo.renderArea.extent = m_pVulkanManager->m_swapChainExtent;
        renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
        renderPassInfo.pClearValues = clearValues.data();


        vkCmdBeginRenderPass(m_commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
        vkCmdBindPipeline(m_commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, m_pVulkanManager->m_graphicsPipeline);

        VkBuffer vertexBuffers[] = { m_vertexBuffer };
        VkDeviceSize offsets[] = { 0 };
        vkCmdBindVertexBuffers(m_commandBuffers[i], 0, 2, vertexBuffers, offsets);

        vkCmdBindIndexBuffer(m_commandBuffers[i], m_indexBuffer, 0, VK_INDEX_TYPE_UINT32);

        vkCmdBindDescriptorSets(m_commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, m_pVulkanManager->m_pipelineLayout, 0, 1, &m_descriptorSets[i], 0, nullptr);

        vkCmdDrawIndexed(m_commandBuffers[i], static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);

        vkCmdEndRenderPass(m_commandBuffers[i]);

        if (vkEndCommandBuffer(m_commandBuffers[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to record command buffer!");
        }
    }
}