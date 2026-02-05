#include "RenderShader.h"

using namespace GFXEngine::Graphics;

RenderShader GFXEngine::Graphics::RenderShader::fromFiles(const char* vertPath, const char* fragPath)
{
	RenderShader shader = {};
	shader.vertCode = LibGFX::GFX::readFile(vertPath);
	shader.fragCode = LibGFX::GFX::readFile(fragPath);
	return shader;
}
