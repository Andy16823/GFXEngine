#include "FrameContext.h"

void GFXEngine::Graphics::FrameContext::init(Renderer &renderer)
{
    size_t numImages = renderer.getSwapchainImageCount();
    m_buffers.reserve(numImages);
    m_descriptorSets.reserve(numImages);

    VkDeviceSize bufferSize = sizeof(GFXEngine::Graphics::FrameData);

    for(size_t i = 0; i < numImages; i++) {
        LibGFX::Buffer buffer = renderer.createBuffer(
            bufferSize,
            VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

        VkDescriptorSet descriptorSet = renderer.allocateUniformBufferDescriptorSet(buffer, 0, renderer.getUniformBufferLayout());
        m_buffers.push_back(buffer);
        m_descriptorSets.push_back(descriptorSet);
    }
}

void GFXEngine::Graphics::FrameContext::update(Renderer &renderer, uint32_t imageIndex)
{
    FrameData data = {
        .deltaTime = m_deltaTime,
        .time = m_time
    };
    renderer.updateBuffer(m_buffers[imageIndex], &data, 1);
}

void GFXEngine::Graphics::FrameContext::dispose(Renderer &renderer)
{
    for (auto& descriptorSet : m_descriptorSets) {
        renderer.freeUniformBufferDescriptorSet(descriptorSet);
    }
    m_descriptorSets.clear();

    for(auto& buffer : m_buffers) {
        renderer.destroyBuffer(buffer);
    }
    m_buffers.clear();
}

