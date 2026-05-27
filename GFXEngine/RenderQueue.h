#pragma once
#include "Renderer.h"
#include "RenderTask.h"
#include <vector>
#include <algorithm>
#include <ostream>
#include <iostream>

namespace GFXEngine
{
	namespace Graphics
	{
		class RenderQueue
		{
		private:
			std::vector<RenderTask> m_tasks;

		public:
			void addRenderTask(RenderTask task)
			{
				m_tasks.push_back(std::move(task));
			}

			void sort() {
				std::sort(m_tasks.begin(), m_tasks.end(), [](const RenderTask& a, const RenderTask& b) {
					return a.sortingKey < b.sortingKey;
					});
			}

			void execute(Graphics::Renderer& renderer, Graphics::Camera& camera, uint32_t imageIndex);
		};
	}
}
