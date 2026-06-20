#pragma once
#include <vulkan/vulkan.h>
#include <unordered_map>

namespace GFXEngine {
	namespace Graphics {
		using GraphicResources = std::unordered_map<unsigned int, VkDescriptorSet>;
	}
}