#include "ComputeShader.h"
#include "Managers/VulkanManager.h"

ComputeShader::ComputeShader()
{

}

ComputeShader::~ComputeShader()
{

}


void ComputeShader::Update()
{
	int numVecs = 256;
	int groupcount = ((numVecs) / 256) + 1;


}

void ComputeShader::BuildComputeCommandBuffer()
{
	vkQueueWaitIdle(compute.queue);

	VkCommandBufferBeginInfo cmdBufferBeginInfo{};
	cmdBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

	vkBeginCommandBuffer(compute.commandBuffer, &cmdBufferBeginInfo);

	vkCmdBindPipeline(compute.commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, compute.pipelines[compute.pipelineIndex]);
	vkCmdBindDescriptorSets(compute.commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, compute.pipelineLayout, 0, 1, &compute.descriptorSet, 0, 0);

	vkCmdDispatch(compute.commandBuffer, 1, 1, 1);

	vkEndCommandBuffer(compute.commandBuffer);
}

VkBufferMemoryBarrier buffer_barrier(VkBuffer buffer, uint32_t queue)
{
	VkBufferMemoryBarrier barrier{};
	barrier.buffer = buffer;
	barrier.size = VK_WHOLE_SIZE;
	barrier.srcQueueFamilyIndex = queue;
	barrier.dstQueueFamilyIndex = queue;
	barrier.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
	barrier.pNext = nullptr;

	return barrier;
}
