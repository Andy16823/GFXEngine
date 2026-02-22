#pragma once
#include "Renderer.h"
#include "Functional"
#include "Camera.h"

namespace GFXEngine {
	namespace Graphics {
		class MeshModel {
		public:
			MeshModel() = default;
			virtual ~MeshModel() = default;

			MeshModel(const MeshModel&) = delete;
			MeshModel& operator=(const MeshModel&) = delete;
			MeshModel(MeshModel&&) = default;
			MeshModel& operator=(MeshModel&&) = default;

			virtual void init(Renderer& renderer) = 0;
			virtual void draw(Renderer& renderer, Camera& camera, uint32_t imageIndex, std::function<void(Renderer& renderer, Camera& camera, uint32_t imageIndex)> callback) const = 0;
			virtual void destroy(Renderer& renderer) = 0;
		};
	}
}