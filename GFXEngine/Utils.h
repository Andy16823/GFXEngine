#pragma once
#include <string>
#include "DataTypes.h"
#include "Imaging.h"

// TODO: Move image loading in an own class. For now , this is a simple utility function to load an image from disk and return the pixel data along with the image dimensions and format. In the future, we can expand this to support more formats, error handling, and caching of loaded images if needed.
namespace GFXEngine {
	class Utils
	{
	public:
		static LibGFX::ImageData loadImage(const std::string& filePath);
	};
}
