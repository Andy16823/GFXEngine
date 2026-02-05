#pragma once
#include <vector>
#include "LibGFX.h"

namespace GFXEngine
{
	namespace Graphics {
		struct RenderShader
		{
		private:
			
		public:
			std::vector<char> vertCode;
			std::vector<char> fragCode;
			static RenderShader fromFiles(const char* vertPath, const char* fragPath);
		};
	}
}
