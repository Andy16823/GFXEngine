#pragma once
#include "Renderer.h"
#include "Functional"
#include "Camera.h"
#include "Pipeline.h"

namespace GFXEngine {
	namespace Graphics {

		/// <summary>
		/// Abstract base class representing a 3D model composed of one or more meshes and materials.
		/// </summary>
		class MeshModel {
		public:
			MeshModel() = default;
			virtual ~MeshModel() = default;

			MeshModel(const MeshModel&) = delete;
			MeshModel& operator=(const MeshModel&) = delete;
			MeshModel(MeshModel&&) = default;
			MeshModel& operator=(MeshModel&&) = default;

			virtual void init(Renderer& renderer) = 0;
			virtual void draw(Renderer& renderer, uint32_t imageIndex, VkPipelineLayout pipelineLayout, std::function<void(Renderer& renderer, VkPipelineLayout pipelineLayout, uint32_t imageIndex, uint32_t meshIndex)> callback) const = 0;
			virtual void destroy(Renderer& renderer) = 0;
		};
	}
}