
#include	"BufferManager.h"
#include    "VulkanManager.h"

#include    "Maths.h"

BufferManager::BufferManager(VulkanManager* pVulkanManager)
: m_pVulkanManager(pVulkanManager)
{

}

BufferManager::~BufferManager()
{
    VkDevice* pDevice = &m_pVulkanManager->m_device;

    vkDestroyDescriptorSetLayout(*pDevice, m_descriptorSetLayout, nullptr);

    vkDestroyBuffer(*pDevice, m_indexBuffer, nullptr);
    vkFreeMemory(*pDevice, m_indexBufferMemory, nullptr);
    vkDestroyBuffer(*pDevice, m_vertexBuffer, nullptr);
    vkFreeMemory(*pDevice, m_vertexBufferMemory, nullptr);
}

void BufferManager::CreateBuffers() 
{
    CreateVertexBuffer();
    CreateIndexBuffer();
    CreateUniformBuffers();
    CreateDescriptorPool();
    CreateDescriptorSets();
}

void BufferManager::CleanupUniformBuffers(size_t swapChainImagesSize)
{
    VkDevice* pDevice = &m_pVulkanManager->m_device;

    for (size_t i = 0; i < swapChainImagesSize; i++) {
        vkDestroyBuffer(*pDevice, m_uniformBuffers[i], nullptr);
        vkFreeMemory(*pDevice, m_uniformBuffersMemory[i], nullptr);
    }

    vkDestroyDescriptorPool(*pDevice, m_descriptorPool, nullptr);
}

void BufferManager::CreateDescriptorSetLayout() {
    VkDevice* pDevice = &m_pVulkanManager->m_device;

    VkDescriptorSetLayoutBinding uboLayoutBinding{};
    uboLayoutBinding.binding = 0;
    uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    uboLayoutBinding.descriptorCount = 1;
    //What shader stage the descriptor is referenced
    uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    uboLayoutBinding.pImmutableSamplers = nullptr;

    VkDescriptorSetLayoutCreateInfo layoutInfo{};
    layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layoutInfo.bindingCount = 1;
    layoutInfo.pBindings = &uboLayoutBinding;

    if (vkCreateDescriptorSetLayout(*pDevice, &layoutInfo, nullptr, &m_descriptorSetLayout) != VK_SUCCESS) {
        throw std::runtime_error("failed to create descriptor set layout!");
    }
}

void BufferManager::CreateDescriptorPool() 
{
    VkDevice* pDevice = &m_pVulkanManager->m_device;
    size_t swapChainImagesSize = m_pVulkanManager->m_swapChainImages.size();

    VkDescriptorPoolSize poolSize{};
    poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    poolSize.descriptorCount = static_cast<uint32_t>(swapChainImagesSize);

    VkDescriptorPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.poolSizeCount = 1;
    poolInfo.pPoolSizes = &poolSize;
    poolInfo.maxSets = static_cast<uint32_t>(swapChainImagesSize);
    poolInfo.flags = 0;

    if (vkCreateDescriptorPool(*pDevice, &poolInfo, nullptr, &m_descriptorPool) != VK_SUCCESS) {
        throw std::runtime_error("failed to create descriptor pool!");
    }
}

void BufferManager::CreateDescriptorSets()
{
    VkDevice* pDevice = &m_pVulkanManager->m_device;
    size_t swapChainImagesSize = m_pVulkanManager->m_swapChainImages.size();

    std::vector<VkDescriptorSetLayout> layouts(swapChainImagesSize, m_descriptorSetLayout);
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

        VkWriteDescriptorSet descriptorWrite{};
        descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrite.dstSet = m_descriptorSets[i];
        descriptorWrite.dstBinding = 0;
        descriptorWrite.dstArrayElement = 0;
        descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorWrite.descriptorCount = 1;
        descriptorWrite.pBufferInfo = &bufferInfo;
        descriptorWrite.pImageInfo = nullptr;
        descriptorWrite.pTexelBufferView = nullptr;

        vkUpdateDescriptorSets(*pDevice, 1, &descriptorWrite, 0, nullptr);
    }
}


void BufferManager::CreateVertexBuffer() 
{
    VkDevice* pDevice = &m_pVulkanManager->m_device;

    VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(*pDevice, stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, vertices.data(), (size_t)bufferSize);
    vkUnmapMemory(*pDevice, stagingBufferMemory);

    CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_vertexBuffer, m_vertexBufferMemory);
    CopyBuffer(stagingBuffer, m_vertexBuffer, bufferSize);

    vkDestroyBuffer(*pDevice, stagingBuffer, nullptr);
    vkFreeMemory(*pDevice, stagingBufferMemory, nullptr);
}

void BufferManager::CreateIndexBuffer() 
{
    VkDevice* pDevice = &m_pVulkanManager->m_device;

    VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(*pDevice, stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, indices.data(), (size_t)bufferSize);
    vkUnmapMemory(*pDevice, stagingBufferMemory);

    CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_indexBuffer, m_indexBufferMemory);
    CopyBuffer(stagingBuffer, m_indexBuffer, bufferSize);

    vkDestroyBuffer(*pDevice, stagingBuffer, nullptr);
    vkFreeMemory(*pDevice, stagingBufferMemory, nullptr);
}

void BufferManager::CreateUniformBuffers()
{
    VkDevice* pDevice = &m_pVulkanManager->m_device;
    size_t swapChainImagesSize = m_pVulkanManager->m_swapChainImages.size();

    VkDeviceSize bufferSize = sizeof(UniformBufferObject);

    m_uniformBuffers.resize(swapChainImagesSize);
    m_uniformBuffersMemory.resize(swapChainImagesSize);

    for (size_t i = 0; i < swapChainImagesSize; i++) {
        CreateBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_uniformBuffers[i], m_uniformBuffersMemory[i]);
    }
}

void BufferManager::UpdateUniformBuffer(uint32_t currentImage, float DeltaTime)
{
    VkDevice* pDevice = &m_pVulkanManager->m_device;
    VkExtent2D* swapChainExtent = &m_pVulkanManager->m_swapChainExtent;

    if (m_rotation > TWO_PI)
        m_rotation -= TWO_PI;
    else
        m_rotation += DeltaTime;

    UniformBufferObject ubo{};
    ubo.model = glm::rotate(glm::mat4(1.0f), m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.proj = glm::perspective(glm::radians(45.0f), swapChainExtent->width / (float)swapChainExtent->height, 0.1f, 10.0f);
    ubo.proj[1][1] *= -1;

    void* data;
    vkMapMemory(*pDevice, m_uniformBuffersMemory[currentImage], 0, sizeof(ubo), 0, &data);
    memcpy(data, &ubo, sizeof(ubo));
    vkUnmapMemory(*pDevice, m_uniformBuffersMemory[currentImage]);
}

void BufferManager::CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory) 
{
    VkDevice* pDevice = &m_pVulkanManager->m_device;

    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    bufferInfo.flags = 0;

    if (vkCreateBuffer(*pDevice, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to create vertex buffer!");
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(*pDevice, buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = m_pVulkanManager->FindMemoryType(memRequirements.memoryTypeBits, properties);

    if (vkAllocateMemory(*pDevice, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate vertex buffer memory!");
    }
    vkBindBufferMemory(*pDevice, buffer, bufferMemory, 0);
}


void BufferManager::CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) 
{
    VkDevice* pDevice = &m_pVulkanManager->m_device;
    VkCommandPool* pCommandPool = &m_pVulkanManager->m_commandPool;
    VkQueue* pGraphicsQueue = &m_pVulkanManager->m_graphicsQueue;

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = *pCommandPool;
    allocInfo.commandBufferCount = 1;

    VkCommandBuffer commandBuffer;
    vkAllocateCommandBuffers(*pDevice, &allocInfo, &commandBuffer);

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(commandBuffer, &beginInfo);

    VkBufferCopy copyRegion{};
    copyRegion.srcOffset = 0;
    copyRegion.dstOffset = 0;
    copyRegion.size = size;

    vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);
    vkEndCommandBuffer(commandBuffer);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    vkQueueSubmit(*pGraphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(*pGraphicsQueue);

    vkFreeCommandBuffers(*pDevice, *pCommandPool, 1, &commandBuffer);
}
