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
		public:
			StaticMeshModel(const std::string& filePath);
			void init(Renderer& renderer) override;
			void destroy(Renderer& renderer) override;

			const Mesh& getMesh(size_t index) const override { return m_meshes.at(index); }
			const Material& getMeshMaterial(size_t index) const override { return m_materials.at(index % m_materials.size()); }
			size_t getMeshCount() const override { return m_meshes.size(); }

		private:
			std::vector<UnlitMaterial> m_materials;
			std::vector<Mesh> m_meshes;

			void loadFromFile(const std::string& filePath);
		};
	}
}
