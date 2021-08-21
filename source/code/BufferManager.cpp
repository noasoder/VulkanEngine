
#include	"BufferManager.h"
#include    "VulkanManager.h"

BufferManager::BufferManager(VulkanManager* pVulkanManager)
: m_pVulkanManager(pVulkanManager)
{

    CreateVertexBuffer();
    CreateIndexBuffer();
}

BufferManager::~BufferManager()
{
    VkDevice* pDevice = &m_pVulkanManager->m_device;

    vkDestroyBuffer(*pDevice, m_indexBuffer, nullptr);
    vkFreeMemory(*pDevice, m_indexBufferMemory, nullptr);
    vkDestroyBuffer(*pDevice, m_vertexBuffer, nullptr);
    vkFreeMemory(*pDevice, m_vertexBufferMemory, nullptr);
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

void BufferManager::CreateIndexBuffer() {
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
