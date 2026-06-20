#pragma once
#include "Renderer.h"
#include "RenderTask.h"
#include <vector>
#include <algorithm>
#include <ostream>
#include <iostream>
#include "Camera.h"

namespace GFXEngine
{
	namespace Graphics
	{
		class RenderQueue
		{
		private:
			std::vector<RenderTask> m_tasks;

		public:
			//************************************
			// Method:    append
			// FullName:  GFXEngine::Graphics::RenderQueue::append
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: RenderQueue & & other
			//************************************
			void append(RenderQueue&& other);
			
			//************************************
			// Method:    addRenderTask
			// FullName:  GFXEngine::Graphics::RenderQueue::addRenderTask
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: RenderTask task
			//************************************
			void addRenderTask(RenderTask task);
			
			//************************************
			// Method:    sort
			// FullName:  GFXEngine::Graphics::RenderQueue::sort
			// Access:    public 
			// Returns:   void
			// Qualifier:
			//************************************
			void sort();
			
			//************************************
			// Method:    execute
			// FullName:  GFXEngine::Graphics::RenderQueue::execute
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Graphics::Renderer & renderer
			// Parameter: Graphics::Camera & camera
			// Parameter: uint32_t imageIndex
			//************************************
			void execute(Graphics::Renderer& renderer, Graphics::Camera& camera, uint32_t imageIndex);
		};
	}
}
