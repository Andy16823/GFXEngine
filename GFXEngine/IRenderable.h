#pragma once
#include "RenderContext.h"
#include "RenderQueue.h"

namespace GFXEngine
{
	namespace Graphics
	{
		class IRenderable {
		public:
			
			//************************************
			// Method:    ~IRenderable
			// FullName:  GFXEngine::Graphics::IRenderable::~IRenderable
			// Access:    virtual public 
			// Returns:   
			// Qualifier:
			//************************************
			virtual ~IRenderable() = default;
			
			//************************************
			// Method:    buildRenderTasks
			// FullName:  GFXEngine::Graphics::IRenderable::buildRenderTasks
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: RenderContext & context
			// Parameter: RenderQueue & renderQueue
			//************************************
			virtual void buildRenderTasks(RenderContext& context, RenderQueue& renderQueue) = 0;
		};
	}
}