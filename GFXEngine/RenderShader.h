#pragma once
#include <vector>
#include "LibGFX.h"

namespace GFXEngine
{
	namespace Graphics {
		struct RenderShader
		{
		public:
			std::vector<char> vertCode;
			std::vector<char> fragCode;

		public:
			//************************************
			// Method:    fromFiles
			// FullName:  GFXEngine::Graphics::RenderShader::fromFiles
			// Access:    public static 
			// Returns:   GFXEngine::Graphics::RenderShader
			// Qualifier:
			// Parameter: const char * vertPath
			// Parameter: const char * fragPath
			//************************************
			static RenderShader fromFiles(const char* vertPath, const char* fragPath);
			
			//************************************
			// Method:    fromFiles
			// FullName:  GFXEngine::Graphics::RenderShader::fromFiles
			// Access:    public static 
			// Returns:   GFXEngine::Graphics::RenderShader
			// Qualifier:
			// Parameter: const std::string & vertPath
			// Parameter: const std::string & fragPath
			//************************************
			static RenderShader fromFiles(const std::string& vertPath, const std::string& fragPath) {
				return fromFiles(vertPath.c_str(), fragPath.c_str());
			}
		};
	}
}
