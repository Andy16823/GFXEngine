#ifndef FRAMECONTEXT_H
#define FRAMECONTEXT_H

#include <glm/glm.hpp>
#include <vector>
#include "Renderer.h"
#include "LibGFX.h"

namespace GFXEngine::Graphics {

struct FrameData {
    float deltaTime = 0;
    float time = 0;
};

class FrameContext {
private:
    std::vector<LibGFX::Buffer> m_buffers;
    std::vector<VkDescriptorSet> m_descriptorSets;
    float m_deltaTime = 0;
    float m_time = 0;

public:
    void init(Renderer& renderer);
    void update(Renderer& renderer, uint32_t imageIndex);
    void dispose(Renderer& renderer);
public:
    void setDeltaTime(float value) { m_deltaTime = value; }
    void setTime(float value) { m_time = value; }
};



}

#endif // FRAMECONTEXT_H

