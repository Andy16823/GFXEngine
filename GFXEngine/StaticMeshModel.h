#pragma once
#include "Mesh.h"
#include "UnlitMaterial.h"
#include "MeshModel.h"
#include <vector>
#include "GeometryPipeline.h"

namespace GFXEngine {
	namespace Graphics {

		/// <summary>
		/// StaticMeshModel is a concrete implementation of the MeshModel interface for rendering static 3D models loaded from files.
		/// </summary>
		class StaticMeshModel : public MeshModel {
		private:
			std::vector<UnlitMaterial> m_materials;
			std::vector<Mesh> m_meshes;
		public:
			void loadFromFile(const std::string& filePath, const GeometryPipeline& pipeline);
			void init(Renderer& renderer) override;
			void draw(Renderer& renderer, Camera& camera, uint32_t imageIndex, std::function<void(Renderer& renderer, Camera& camera, uint32_t imageIndex, const LibGFX::Pipeline& pipeline, uint32_t meshIndex)> callback) const override;
			void destroy(Renderer& renderer) override;
		};
	}
}
