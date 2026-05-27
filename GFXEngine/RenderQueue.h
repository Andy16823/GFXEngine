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
			void append(RenderQueue&& other);
			void addRenderTask(RenderTask task);
			void sort();
			void execute(Graphics::Renderer& renderer, Graphics::Camera& camera, uint32_t imageIndex);
		};
	}
}
