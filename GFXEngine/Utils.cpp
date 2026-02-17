#include "Utils.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdexcept>

LibGFX::ImageData GFXEngine::Utils::loadImage(const std::string& filePath)
{
	int texWidth, texHeight, texChannels;
	stbi_uc* pixels = stbi_load(filePath.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
	if (!pixels) {
		throw std::runtime_error("Failed to load texture image!");
	}
	LibGFX::ImageData imageData;
	imageData.pixels = pixels;
	imageData.width = static_cast<uint32_t>(texWidth);
	imageData.height = static_cast<uint32_t>(texHeight);
	imageData.format = VK_FORMAT_R8G8B8A8_UNORM;
	return imageData;
}
