#pragma once
#include "RenderContext.h"
#include "RenderQueue.h"

namespace GFXEngine
{
	namespace Graphics
	{
		/// <summary>
		/// Renderable is an interface that any object that can be rendered must implement. 
		/// It defines a method to build render tasks
		/// </summary>
		class IRenderable {
		public:
			virtual ~IRenderable() = default;
			virtual void preRender(RenderContext& context) {};
			virtual void buildRenderTasks(RenderContext& context, RenderQueue& renderQueue) = 0;
			virtual void postRender(RenderContext& context) {};
		};
	}
}