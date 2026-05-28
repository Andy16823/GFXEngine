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
			virtual void buildRenderTasks(RenderContext& context, RenderQueue& renderQueue) = 0;
		};
	}
}